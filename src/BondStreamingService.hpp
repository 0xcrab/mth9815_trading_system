/**
 * BondStreamingService.hpp
 * This file defines Bond Streaming service
 * and a Listener class to get data from 
 * BondAlgoStreamingService
 * 
 * @ Zilun Shen <shenzilun@gmail.com>
 */

#ifndef BONDSTREAMINGSERVCE_HPP
#define BONDSTREAMINGSERVCE_HPP

#include "framework/streamingservice.hpp"
#include "BondAlgoStreamingService.hpp"
#include "utility.hpp"

class BondStreamingConnector_File : public Connector<PriceStream<Bond>>,
	private OutputFileWriter
{
public:
	BondStreamingConnector_File(std::string path);
	// Publish data to the Connector
	virtual void Publish(const PriceStream<Bond> &data);
};

class BondStreamingService : StreamingService<Bond>,
	public virtual BasicService<std::string, PriceStream<Bond>>
{
public:
	BondStreamingService(std::string path);
	void PublishPrice(const PriceStream<Bond>& priceStream);
private:
	BondStreamingConnector_File fileWriter;
};

class BondStreamingListener : public BasicListener<AlgoStream>
{
public:
	BondStreamingListener(BondAlgoStreamingService &algostrsrv,
			BondStreamingService &bstrsrv);
	void ProcessAdd(AlgoStream& data);
private:
	BondStreamingService *bstrsrv_ptr;
};

#endif
