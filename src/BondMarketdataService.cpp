#include "BondMarketdataService.hpp"
#include <vector>
#include <deque>
#include <iostream>
using namespace std;

BondMarketdataConnector_File::BondMarketdataConnector_File(string file)
	: InputFileReader(file), srv_ptr(nullptr)
{
}

void BondMarketdataService::OnMessage(OrderBook<Bond>& data)
{

#ifdef DEBUG_PRINT_DEMO
	cout << "------------------------------------------------" << endl;
	cout << "Orderbook for " << data.GetProduct().GetProductId() << endl;
	cout << "\tBid: ";
	for(auto i : data.GetBidStack()){
		cout << i.GetPrice() << "(" << i.GetQuantity()/1000000 << "M)\t";
	}
	cout << "\n\tOffer: ";
	for(auto i : data.GetOfferStack()){
		cout << i.GetPrice() << "(" << i.GetQuantity()/1000000 << "M)\t";
	}
	cout << endl;
#endif
	BasicService::OnMessage(data);
}

void BondMarketdataConnector_File::Publish(const OrderBook<Bond> &data)
{
	// Do nothing
}

void BondMarketdataConnector_File::bindService(BondMarketdataService &mkt_srv)
{
	srv_ptr = &mkt_srv;
}

void BondMarketdataConnector_File::start()
{
	vector<string> record;
	if(srv_ptr != nullptr){
		while(getNextLine(record)){
			deque<string> q(record.begin(), record.end());
			vector<Order> bid, offer;
			auto prod = makeBond(q.front());
			q.pop_front();
			// Gen bid stack
			for(int i=0; i<5; i++){
				auto price = BondPrice_string2double(q.front());
				q.pop_front();
				auto volume = stoi(q.front());
				bid.push_back(Order(price, volume, BID));
				q.pop_front();
			}
			// Gen offer stack
			for(int i=0; i<5; i++){
				auto price = BondPrice_string2double(q.front());
				q.pop_front();
				auto volume = stoi(q.front());
				offer.push_back(Order(price, volume, OFFER));
				q.pop_front();
			}
			auto book = OrderBook<Bond>(prod, bid, offer);
			srv_ptr->OnMessage(book);
		}
	}
}

long BondMarketdataService::AggregateDepth(const string &productId, double price)
{
	auto orderbook = BasicService::GetData(productId);
	orderbook = BasicService::data_pool[productId];
	long vol = 0;
	for(auto i : orderbook.GetBidStack()){
		if(i.GetPrice() == price)
			vol += i.GetQuantity();
	}
	for(auto i : orderbook.GetOfferStack()){
		if(i.GetPrice() == price)
			vol += i.GetQuantity();
	}
	return vol;
}

BidOffer BondMarketdataService::GetBestBidOffer(const string &productId)
{
	auto orderbook = BasicService::GetData(productId);
	return BidOffer(orderbook.GetBidStack().front(),
					orderbook.GetOfferStack().front());
}

void BondMarketdataConnector_Demo::AddOrderBook(OrderBook<Bond> orderbook)
{
	srv_ptr->OnMessage(orderbook);
}

void BondMarketdataConnector_Demo::Publish(const OrderBook<Bond> &data)
{
	// Do nothing
}

void BondMarketdataConnector_Demo::bindService(BondMarketdataService &mkt_srv)
{
	srv_ptr = &mkt_srv;
}

