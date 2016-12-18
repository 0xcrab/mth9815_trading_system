/**
 * BondMarketDataService.hpp
 * This file provides a Marketdata Service for Bond
 * As well as a connector class that can load data 
 * from local file
 * 
 * @ Zilun Shen <shenzilun@gmail.com>
 */

#ifndef BONDMARKETDATASERVICE_HPP
#define BONDMARKETDATASERVICE_HPP

#include "framework/marketdataservice.hpp"
#include "framework/soa.hpp"
#include "utility.hpp"
#include "BasicService.hpp"
#include <vector>
#include <string>
using std::string;

class BondMarketdataService : public MarketDataService<Bond>,
	public virtual BasicService<std::string, OrderBook<Bond>>
{
public:
	void OnMessage(OrderBook<Bond>& data) override;

	// Get the best bid/offer order
	BidOffer GetBestBidOffer(const string &productId) override;

	// Aggregate the order book
	long AggregateDepth(const string &productId, double price) override;
};

// This class allow user to input orderbook. It can be use as 
// demo of AggregateDepth method above.
class BondMarketdataConnector_Demo : public Connector<OrderBook<Bond>>
{
public:
	void bindService(BondMarketdataService &mkt_srv);
	void Publish(const OrderBook<Bond> &data) override;
	void AddOrderBook(OrderBook<Bond> orderbook);
private:
	BondMarketdataService *srv_ptr;
};

class BondMarketdataConnector_File : public Connector<OrderBook<Bond>>,
	private InputFileReader
{
public:
	BondMarketdataConnector_File(string file);
	void bindService(BondMarketdataService &mkt_srv);
	void start();
	void Publish(const OrderBook<Bond> &data) override;
private:
	BondMarketdataService *srv_ptr;
};

#endif
