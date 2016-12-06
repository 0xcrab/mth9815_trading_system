/**
 * BondPositionService.hpp
 * This file defines BondPositionService service
 * and a Listener class to get trade data from 
 * BondTradeBookingService
 * 
 * @ Zilun Shen <shenzilun@gmail.com>
 */

#include "BondTradeBookingService.hpp"
#include "framework/positionservice.hpp"
#include "BasicService.hpp"
#include "BasicListener.hpp"

class BondPositionService : public PositionService<Bond>, 
	public BasicService<string, Position<Bond>>,
	public BasicListener<Trade<Bond>>{
public:
	BondPositionService() = default;
	virtual ~BondPositionService() = default;
	// Add a trade to the service
	virtual void AddTrade(const Trade<Bond> &trade) override;
	virtual void ProcessAdd(Trade<Bond> &data) override;
};

/*
 *class BondPositionListener : public BasicListener<Trade<Bond>> {
 *public:
 *    BondPositionListener(BondTradeBookingService &tradesrv);
 *    virtual ~BondPositionListener() = default;
 *    virtual void ProcessAdd(Trade<Bond> &data) override;
 *private:
 *    BondTradeBookingService* tradesrv_ptr;
 *};
 */
