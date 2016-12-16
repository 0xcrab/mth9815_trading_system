/**
 * BondPricingService.hpp
 * This file provides a Pricing Service for Bond
 * As well as a connector class that can load data 
 * from local file
 * 
 * @ Zilun Shen <shenzilun@gmail.com>
 */

#ifndef BONDPRICINGSERVICE_HPP
#define BONDPRICINGSERVICE_HPP

#include "framework/pricingservice.hpp"
#include "framework/products.hpp"
#include "framework/soa.hpp"
#include "BasicService.hpp"
#include "utility.hpp"
#include <string>

using std::string;

class BondPricingService : public PricingService<Bond>,
	public virtual BasicService<string, Price<Bond>>{
public:
	void OnMessage(Price<Bond>& data) override;
};
 
class BondPricingConnector_File : public Connector<Price<Bond>>,
								 private InputFileReader
{
public:
	BondPricingConnector_File(string file);
	virtual ~BondPricingConnector_File() = default;
	void bindService(BondPricingService &_srv);
	void start();
	void Publish(Price<Bond> &data) override;
private:
	BondPricingService* srv_ptr;
};

#endif
