/**
 * BondTradeBookingService.hpp
 * Defines Bond Trade Service
 * 
 * Defines Bond Trade Connector that can read trade 
 * from file
 * 
 * @Zilun Shen <shenzilun@gmail.com>
 */
#ifndef BONDTRADEBOOKINGSERVICE_H
#define BONDTRADEBOOKINGSERVICE_H

#include "framework/products.hpp"
#include "framework/tradebookingservice.hpp"
#include <string>
#include <memory>
#include <vector>
#include <map>
#include "utility.hpp"

using std::vector;
using std::map;


class BondTradeBookingService : public TradeBookingService<Bond>{
public:
	BondTradeBookingService() = default;
	virtual ~BondTradeBookingService() = default;
	// Book the trade
	void BookTrade(const Trade<Bond>&) override;
	// Get data on our service given a key
	virtual Trade<Bond>& GetData(string key) override;

	// The callback that a Connector should invoke for any new or updated data
	virtual void OnMessage(Trade<Bond> &data) override;

	// Add a listener to the Service for callbacks on add, remove, and update events
	// for data to the Service.
	virtual void AddListener(ServiceListener<Trade<Bond>> *listener) override;

	// Get all listeners on the Service.
	virtual const vector<ServiceListener<Trade<Bond>>*>& GetListeners() const override;

private:
	vector<ServiceListener<Trade<Bond>>*> listeners;
	map<string, Trade<Bond>*> trades;
};

class BondTradeConnector_File : public Connector<Trade<Bond>>, 
	private InputFileReader{
public:
	BondTradeConnector_File(std::string file);
	virtual ~BondTradeConnector_File() = default;
	void bindService(BondTradeBookingService &_srv);
	void start();
	void Publish(Trade<Bond> &data) override;
private:
	BondTradeBookingService* srv_ptr;
};

#endif
