#include "BondPositionService.hpp"
#include <iostream>
#include <string>
#include "utility.hpp"

using namespace std;

void BondPositionService::AddTrade(const Trade<Bond> &trade)
{	
	auto key = trade.GetProduct().GetProductId();
	auto pos = data_pool.find(key);
	if(pos == data_pool.end()){
		Position<Bond> initpos(makeBond(key));
		initpos.AddPosition(trade);
		data_pool.insert({key, initpos});
		pos = data_pool.find(key);
	}
	pos->second.AddPosition(trade);
	
	cout << "\t Updating position ";
	cout << trade.GetProduct().GetProductId() << " " <<
		trade.GetSide() << " " << trade.GetQuantity() << endl;
	cout << "\t\t ===> Total position is "
		<< data_pool[trade.GetProduct().GetProductId()].GetAggregatePosition() << endl;

	OnMessage(pos->second);
}

BondPositionListener::BondPositionListener(BondTradeBookingService &tradesrv,
		BondPositionService &possrv)
{
	tradesrv.AddListener(this);
	possrv_prt = & possrv;
}

void BondPositionListener::AddPositionReceiver(BondPositionService& possrv)
{
	possrv_prt = &possrv;
}

void BondPositionListener::ProcessAdd(Trade<Bond> &data)
{
	possrv_prt->AddTrade(data);
}

