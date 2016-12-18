/**
 * BondEcutionService.hpp
 * This file defines Bond Excution service
 * and a Listener class to get data from 
 * BondAlgoExcutionService
 * 
 * @ Zilun Shen <shenzilun@gmail.com>
 */

#ifndef BONDEXECUTIONSERVICE_HPP
#define BONDEXECUTIONSERVICE_HPP

#include "framework/executionservice.hpp"
#include "BondAlgoExcutionService.hpp"
#include "BasicService.hpp"
#include "BasicListener.hpp"

class BondExecutionService : public ExecutionService<Bond>,
	public virtual BasicService<std::string, ExecutionOrder<Bond>>
{
public:
	BondExecutionService();
	void ExecuteOrder(const ExecutionOrder<Bond>& order, Market market) override;
};

class BondExecutionListener : public BasicListener<AlgoExecution>
{
public:
	BondExecutionListener(BondAlgoExcutionService &algosrv,
			BondExecutionService &exesrv);
	void ProcessAdd(AlgoExecution &data) override;
private:
	BondExecutionService *srv_ptr;
};

#endif
