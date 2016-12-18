#include "BondAlgoStreamingService.hpp"
#include "framework/marketdataservice.hpp"
#include "utility.hpp"
#include <iostream>
using namespace std;

void BondAlgoStreamingService::PublishPrice(const PriceStream<Bond>& priceStream)
{
	AlgoStream tmp(priceStream);
	BasicService::OnMessage(tmp);
}

AlgoStream::AlgoStream(const PriceStream<Bond>& _pstr)
	:pstr(&_pstr)
{
	// TODO: need to be revised
	prod = makeBond("912828M72");
}

const Bond& AlgoStream::GetProduct() const
{
	// TODO: To be implemented
	return prod;
}


const PriceStream<Bond>& AlgoStream::GetPriceStream() const
{
	return *pstr;
}

BondAlgoStreamingListener::BondAlgoStreamingListener(BondPricingService &prcsrv,
		BondAlgoStreamingService &algostrsrv)
{
	prcsrv.AddListener(this);
	algostrsrv_ptr = &algostrsrv;
}

void BondAlgoStreamingListener::ProcessAdd(Price<Bond> &data)
{
	// Construct a PriceStream
	PriceStreamOrder bidorder(data.GetMid() - data.GetBidOfferSpread() * 0.5, 0, 0, BID);
	PriceStreamOrder offerorder(data.GetMid() + data.GetBidOfferSpread() * 0.5, 0, 0, OFFER);
	algostrsrv_ptr->PublishPrice({data.GetProduct(), bidorder, offerorder});
}

