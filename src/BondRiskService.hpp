/**
 * BondRiskService.hpp
 * Defines Bond Risk Service
 * and Bond Risk Listener that get data
 * from Bond Pricing Service
 * 
 * @Zilun Shen <shenzilun@gmail.com>
 */
#ifndef BONDRISKSERVICE_H
#define BONDRISKSERVICE_H

#include "framework/riskservice.hpp"
#include "BasicService.hpp"
#include "BasicListener.hpp"
#include "BondPositionService.hpp"
#include <vector>
#include <map>
#include <string>

class BondRiskService : public RiskService<Bond>, 
						public virtual BasicService<string, PV01<Bond>>
{
public:
	// Add a position that the service will risk
	void AddPosition(Position<Bond> &position) override;

	// Get the bucketed risk for the bucket sector
	double GetBucketedRisk(const BucketedSector<Bond> &sector) override;

	// Get risk for individual bond
	double GetRisk(const Bond & prod) override;
	
private:
	//std::vector<PV01<Bond>> cur_risk;
};

class BondRiskListener : public BasicListener<Position<Bond>>
{
public:
	BondRiskListener(BondPositionService &risksrv,
			BondRiskService &prcsrv);
	void ProcessAdd(Position<Bond> &data) override;
private:
	BondRiskService* risksrv_ptr;
};


#endif
