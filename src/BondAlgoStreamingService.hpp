/**
 * BondAlgoStreamingService.hpp
 * This file defines Bond Algo Streaming service
 * and a Listener class to get data from 
 * BondPricingService
 * 
 * @ Zilun Shen <shenzilun@gmail.com>
 */

#ifndef BONDALGOSTREAMINGSERVCE_HPP
#define BONDALGOSTREAMINGSERVCE_HPP

#include "framework/streamingservice.hpp"
#include "framework/products.hpp"
#include "BasicService.hpp"
#include "BasicListener.hpp"
#include "utility.hpp"
#include "BondPricingService.hpp"

class AlgoStream{
public:
	AlgoStream() = default;
	AlgoStream(const PriceStream<Bond>& _pstr);
	const PriceStream<Bond>& GetPriceStream() const;
	const Bond& GetProduct() const;
private:
	const PriceStream<Bond>* pstr;
	Bond prod;
};

class BondAlgoStreamingService : //public StreamingService<Bond>,
	public virtual BasicService<std::string, AlgoStream>
{
public:
	void PublishPrice(const PriceStream<Bond>& priceStream);
};

class BondAlgoStreamingListener : public BasicListener<Price<Bond>>
{
public:
	BondAlgoStreamingListener(BondPricingService &prcsrv,
			BondAlgoStreamingService &algostrsrv);
	void ProcessAdd(Price<Bond> &data) override;
private:
	BondAlgoStreamingService *algostrsrv_ptr;
};

#endif
