#include "BondPricingService.hpp"
#include <iostream>
using namespace std;

void BondPricingService::OnMessage(Price<Bond>& data) 
{
#ifdef DEBUG_PRINT_DEMO
	cout << data.GetProduct().GetProductId() << " " 
		<< data.GetMid() 
		<< endl;
#endif
	BasicService::OnMessage(data);
}

BondPricingConnector_File::BondPricingConnector_File(string file)
	: InputFileReader(file), srv_ptr(nullptr)
{
}

void BondPricingConnector_File::bindService(BondPricingService &_srv)
{
	srv_ptr = &_srv;
	return;
}

void BondPricingConnector_File::start()
{
	vector<string> record;
	if(srv_ptr != nullptr){
		while(getNextLine(record)){
			Price<Bond> price(makeBond(record[0]),
								BondPrice_string2double(record[1]),
								BondPrice_string2double(record[2]));
			srv_ptr->OnMessage(price);
		}
	}
}

void BondPricingConnector_File::Publish(const Price<Bond>& data){
}
