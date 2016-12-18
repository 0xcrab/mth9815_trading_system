#include "BondRiskService.hpp"
#include "utility.hpp"

void BondRiskService::AddPosition(Position<Bond> &position)
{
	auto risk = PV01<Bond>( position.GetProduct(),
								   BondPV01(position.GetProduct().GetProductId()),
								   position.GetAggregatePosition());
	cur_risk.push_back(risk); 
	OnMessage(risk);
}

BondRiskListener::BondRiskListener(BondPositionService &possrv,
		BondRiskService &risksrv)
{
	possrv.AddListener(this);
	risksrv_ptr = &risksrv;
}

double BondRiskService::GetBucketedRisk(const BucketedSector<Bond> &sector) const
{
	double pv01 = 0;
	auto bond_list = sector.GetProducts();
	for(auto & i : bond_list){
		pv01 += BondPV01(i.GetProductId());
	}
	return pv01;
}

void BondRiskListener::ProcessAdd(Position<Bond> &data)
{
	risksrv_ptr->AddPosition(data);
}

