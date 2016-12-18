/**
 * BondAlgoEcutionService.hpp
 * This file defines Bond Algo Excution service
 * and a Listener class to get data from 
 * BondMarketdataService
 * 
 * @ Zilun Shen <shenzilun@gmail.com>
 */

#ifndef BONDALGOEXCUTIONSERVICE_HPP
#define BONDALGOEXCUTIONSERVICE_HPP

#include "framework/executionservice.hpp"
#include "BondMarketdataService.hpp"
#include "BasicService.hpp"
#include "BasicListener.hpp"
#include <string>

class AlgoExecution : public ExecutionOrder<Bond>{
public:

	AlgoExecution() = default;
	AlgoExecution(const string& bondid, PricingSide _side, double _price, double quantity);
	// Get the product
	//const Bond& GetProduct() const;
private:
	//ExecutionOrder<Bond> exeorder;
	static size_t AlgoExe_cnt;
};

class BondAlgoExcutionService : public BasicService<std::string, AlgoExecution>
{
public:
	BondAlgoExcutionService();
	void AddOrderBook(OrderBook<Bond> orderbook);
};

class BondAlgoExcutionListener : public BasicListener<OrderBook<Bond>>
{
public:
	BondAlgoExcutionListener(BondMarketdataService &mktsrv,
			BondAlgoExcutionService &algoexsrv);
	void ProcessAdd(OrderBook<Bond> &data) override;
private:
	BondAlgoExcutionService *algoexsrv_ptr;
};


#endif
