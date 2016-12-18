#include "BondRiskService.hpp"
#include "utility.hpp"
#include <iostream>
using namespace std;

void BondRiskService::AddPosition(Position<Bond> &position)
{
	auto risk = PV01<Bond>( position.GetProduct(),
								   BondPV01(position.GetProduct().GetProductId()),
								   position.GetAggregatePosition());
	//cur_risk.push_back(risk); 
	OnMessage(risk);
}

BondRiskListener::BondRiskListener(BondPositionService &possrv,
		BondRiskService &risksrv)
{
	possrv.AddListener(this);
	risksrv_ptr = &risksrv;
}

double BondRiskService::GetBucketedRisk(const BucketedSector<Bond> &sector)
{
	double totalrisk = 0;
	auto bond_list = sector.GetProducts();
	for(auto & i : bond_list){
		auto& pv01 = GetData(i.GetProductId());
		totalrisk += pv01.GetPV01() * pv01.GetQuantity();
	}
	return totalrisk;
}

double BondRiskService::GetRisk(const Bond & prod)
{
	auto pv01 = GetData(prod.GetProductId());
	return pv01.GetPV01() * pv01.GetQuantity();
}

void BondRiskListener::ProcessAdd(Position<Bond> &data)
{
	risksrv_ptr->AddPosition(data);
}

