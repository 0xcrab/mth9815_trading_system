/**
 * BondPositionService.hpp
 * This file defines BondPositionService service
 * and a Listener class to get trade data from 
 * BondTradeBookingService
 * 
 * @ Zilun Shen <shenzilun@gmail.com>
 */

#ifndef BONDPOSITIONSERVICE_HPP
#define BONDPOSITIONSERVICE_HPP

#include "BondTradeBookingService.hpp"
#include "framework/positionservice.hpp"
#include "BasicService.hpp"
#include "BasicListener.hpp"

class BondPositionService : public PositionService<Bond>, 
	public BasicService<string, Position<Bond>>{
public:
	BondPositionService() = default;
	virtual ~BondPositionService() = default;
	// Add a trade to the service
	virtual void AddTrade(const Trade<Bond> &trade) override;
};

class BondPositionListener : public BasicListener<Trade<Bond>> {
public:
	BondPositionListener(BondTradeBookingService &tradesrv,
			BondPositionService &possrv);
	virtual ~BondPositionListener() = default;
	virtual void ProcessAdd(Trade<Bond> &data) override;
	void AddPositionReceiver(BondPositionService& possrv);
private:
	BondPositionService* possrv_prt;
};

#endif
