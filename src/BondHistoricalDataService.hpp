/**
 * BondHistoricalData.hpp
 * This file provides a Bond Historical Data class
 * that persist all events happened in this system.
 * It can write the events of each services to a local file.
 * 
 * The Listener classes have to be registered in order to 
 * get the log file of a service
 * 
 * @ Zilun Shen <shenzilun@gmail.com>
 */

#ifndef BONDHISTORICALDATASERVICE_HPP
#define BONDHISTORICALDATASERVICE_HPP

#include "framework/historicaldataservice.hpp"
#include "BasicService.hpp"
#include "BasicListener.hpp"
#include "BondPositionService.hpp"
#include "BondRiskService.hpp"
#include "BondExecutionService.hpp"
#include "BondExecutionService.hpp"
#include "BondInquiryService.hpp"
#include "BondStreamingService.hpp"
#include "utility.hpp"
#include <memory>
#include <map>
#include <vector>
#include <iostream>
#include <type_traits>
#include <typeinfo>
#include "config.hpp"

class HistoricalData{
public:
	// ctor for each type of listeners
	HistoricalData();
	HistoricalData(const string& str, double d);
	HistoricalData(PV01<Bond>& data);
	HistoricalData(Position<Bond>& data);
	HistoricalData(ExecutionOrder<Bond>& data);
	HistoricalData(PriceStream<Bond>& data);
	HistoricalData(Inquiry<Bond>& data);

	const std::vector<string>& GetContent() const;
private:
	std::vector<string> content;	
};

class BondHistoricalDataService : public HistoricalDataService<HistoricalData>,
	public BasicService<string, HistoricalData>
{
public:

	BondHistoricalDataService();

	void OnMessage(HistoricalData &data) override;

	// Persist data to a store
	void PersistData(string persistKey, const HistoricalData& data) override;
private:
	std::map<std::string, std::shared_ptr<OutputFileWriter>> file_writer_map;
};

// Because we need to do different work for different type of service, we need this template function
// Since I have finishied most part of this project, I dont't want to modify each service and 
// give them an interface to deal with the HistoricalData,
// although I know using a template function is not the best solution
template<typename S, typename T>
void DoTheLog(BondHistoricalDataService* histsrv_ptr, S *targetsrv_ptr, string srv_key, T &data){
	// If working on a risk service
	
	if(std::is_base_of<Service<string, PV01<Bond>>, S>::value){
		//Individual bond risk
		for(auto& i : CUSIPS_LIST){
			histsrv_ptr->PersistData( srv_key, HistoricalData(i, 
					dynamic_cast<RiskService<Bond>*>(targetsrv_ptr)->GetRisk(
						makeBond(i))));
		}
		// Buckted sector risk
		 
		// Define BucketedSectors that we are interested in, for which we
		// will record history data
		const std::vector<BucketedSector<Bond>> INTERESTED_BUCKETED_SECTOR_LIST{
			BucketedSector<Bond>({makeBond(BOND_YEAR_2), makeBond(BOND_YEAR_3)}, "FrontEnd"),
				BucketedSector<Bond>({makeBond(BOND_YEAR_5), makeBond(BOND_YEAR_7), makeBond(BOND_YEAR_10)}, "Belly"),
				BucketedSector<Bond>({makeBond(BOND_YEAR_30)}, "LongEnd")
		};
		for(auto& i : INTERESTED_BUCKETED_SECTOR_LIST){
			histsrv_ptr->PersistData( srv_key, HistoricalData( i.GetName(),
					dynamic_cast<RiskService<Bond>*>(targetsrv_ptr)->GetBucketedRisk(i)));
		}
		// Output an empty line
		histsrv_ptr->PersistData( srv_key, HistoricalData() );
	}
	// Other service
	else{
		//std::cout << "This is not risk service" << std::endl;
		histsrv_ptr->PersistData(srv_key, data);
	}
}

template<typename T>
class BondHistoricalDataListener : public BasicListener<T>
{
public:
	BondHistoricalDataListener(string _servicename, Service<string, T> &targetsrv, BondHistoricalDataService &histsrv)
		: srv_key(_servicename), targetsrv_ptr(&targetsrv), histsrv_ptr(&histsrv) 
	{ 
		targetsrv.AddListener(this); 
	}
	void ProcessAdd(T &data) override{ 
		//std::cout << "Process Add for Hist data" << std::endl;
		DoTheLog(histsrv_ptr, targetsrv_ptr, srv_key, data);
	}
private:
	string srv_key;
	BondHistoricalDataService *histsrv_ptr;
	Service<string, T> *targetsrv_ptr;
};


#endif
