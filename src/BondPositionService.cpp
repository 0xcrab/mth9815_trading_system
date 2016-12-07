#include "BondPositionService.hpp"
#include <iostream>
#include <string>

using namespace std;

void BondPositionService::AddTrade(const Trade<Bond> &trade)
{
	//cout << trade.GetProduct().GetProductId() << endl;
	//cout << " sadsf    " << data_pool["adsf"].GetProduct().GetProductId() << endl;
	data_pool[trade.GetProduct().GetProductId()].AddPosition(trade);
	
	cout << "\t====> ";
	cout << trade.GetProduct().GetProductId() << " " <<
		trade.GetSide() << " " << trade.GetQuantity() << endl;
}

void BondPositionService::ProcessAdd(Trade<Bond> &data)
{
	AddTrade(data);
}

