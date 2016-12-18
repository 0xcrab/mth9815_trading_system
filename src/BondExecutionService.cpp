#include "BondExecutionService.hpp"
#include <cstdlib>
#include <iostream>
using namespace std;

BondExecutionListener::BondExecutionListener(BondAlgoExcutionService &algosrv,
		BondExecutionService &exesrv)
{
	algosrv.AddListener(this);
	srv_ptr = &exesrv;
}

BondExecutionService::BondExecutionService()
{
}

void BondExecutionService::ExecuteOrder(const ExecutionOrder<Bond>& order, Market market)
{
#ifdef DEBUG_PRINT_DEMO
	cout << order.GetOrderId() << " " << order.GetPrice() << " " << order.GetVisibleQuantity() << " " << market << endl;
#endif
	auto tmp = order;
	BasicService::OnMessage(tmp);
}

void BondExecutionListener::ProcessAdd(AlgoExecution &data)
{
	// Put the order in a random market
	srv_ptr->ExecuteOrder(static_cast<ExecutionOrder<Bond>>(data), Market(rand()%3));
}

