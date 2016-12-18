#include "BondTradeBookingService.hpp"
#include <string>
#include <vector>
#include <iostream>
#include "utility.hpp"
#include "framework/tradebookingservice.hpp"
using namespace std;

void BondTradeBookingService::AddListener(ServiceListener<Trade<Bond>> *listener) 
{
	listeners.push_back(listener);
}

void BondTradeBookingService::BookTrade(const Trade<Bond>& trade) 
{
	cout << "\t---> Book Trade " << trade.GetTradeId() << 
		" for bond " << trade.GetProduct().GetProductId() << endl;
	for(auto&& i : listeners){
		i->ProcessAdd(const_cast<Trade<Bond>&>(trade));
	}
}

Trade<Bond>& BondTradeBookingService::GetData(string key) 
{
	return *trades[key];
}

void BondTradeBookingService::OnMessage(Trade<Bond> &data) 
{
	trades[data.GetTradeId()] = &data;
	BookTrade(data);
}

const vector<ServiceListener<Trade<Bond>>*>& BondTradeBookingService::GetListeners() const 
{
	return listeners;
}

BondTradeConnector_File::BondTradeConnector_File(std::string file)
	: InputFileReader(file), srv_ptr(nullptr)
{
}

void BondTradeConnector_File::bindService(BondTradeBookingService &_srv)
{
	srv_ptr = &_srv;
	return /* something */;
}

void BondTradeConnector_File::start()
{
	vector<string> record;
	if(srv_ptr != nullptr){
		while(getNextLine(record)){
			Side side;
			if(record[4] == "BUY") side = BUY;
			else	side = SELL;
			Trade<Bond> trade(makeBond(record[1]),
					record[0],
					record[2],
					stoi(record[3]),
					side);
			srv_ptr->OnMessage(trade);
		}
	}
}

void BondTradeConnector_File::Publish(const Trade<Bond> &data) 
{
}
