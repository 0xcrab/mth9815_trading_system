#include "BondAlgoExcutionService.hpp"
#include "utility.hpp"

size_t AlgoExecution::AlgoExe_cnt = 0;

AlgoExecution::AlgoExecution(const string& bondid, PricingSide _side, double _price, double quantity)
	: ExecutionOrder(makeBond(bondid), _side, "AlgoOrder #"+to_string(++AlgoExe_cnt), LIMIT,
			_price, quantity/2, quantity/2, "NULL", false)
{
	// This is a LIMIT ordre with half visible and half hidden
}

//const Bond& AlgoExecution::GetProduct() const
//{
	//// TODO: to be implemented
	//return Bond();
//}

BondAlgoExcutionService::BondAlgoExcutionService()
	: BasicService<string, AlgoExecution>([](const AlgoExecution& v){return v.GetOrderId();})
{
}

void BondAlgoExcutionService::AddOrderBook(OrderBook<Bond> orderbook)
{
	// Place a small order on both bid1 and offer1
	
	auto bid = AlgoExecution(
				orderbook.GetProduct().GetProductId(),
				orderbook.GetBidStack().front().GetSide(),
				orderbook.GetBidStack().front().GetPrice(),
				orderbook.GetBidStack().front().GetQuantity() / 1000);
	auto offer = AlgoExecution(
				orderbook.GetProduct().GetProductId(),
				orderbook.GetOfferStack().front().GetSide(),
				orderbook.GetOfferStack().front().GetPrice(),
				orderbook.GetOfferStack().front().GetQuantity() / 1000);
	BasicService::OnMessage(bid);
	BasicService::OnMessage(offer);
}

BondAlgoExcutionListener::BondAlgoExcutionListener(BondMarketdataService &mktsrv,
		BondAlgoExcutionService &algoexsrv)
{
	mktsrv.AddListener(this);
	algoexsrv_ptr = &algoexsrv;
}

void BondAlgoExcutionListener::ProcessAdd(OrderBook<Bond> &data)
{
	algoexsrv_ptr->AddOrderBook(data);
}

