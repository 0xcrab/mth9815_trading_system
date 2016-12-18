#include "BondHistoricalDataService.hpp"
#include "BondRiskService.hpp"
#include <iostream>
using namespace std;

BondHistoricalDataService::BondHistoricalDataService()
	: BasicService([](const HistoricalData& v){return "";})
{
	// Make a file writer for each service where we need to collect historical data
	file_writer_map.insert({SERVICE_KEY_POSITION, 
			std::make_shared<OutputFileWriter>(HISTORYDATA_OUTPUT_POSITION)});
	file_writer_map.insert({SERVICE_KEY_RISK, 
			std::make_shared<OutputFileWriter>(HISTORYDATA_OUTPUT_RISK)});
	file_writer_map.insert({SERVICE_KEY_EXECUTION, 
			std::make_shared<OutputFileWriter>(HISTORYDATA_OUTPUT_EXECUTION)});
	file_writer_map.insert({SERVICE_KEY_STREAMING, 
			std::make_shared<OutputFileWriter>(HISTORYDATA_OUTPUT_STREAMING)});
	file_writer_map.insert({SERVICE_KEY_INQUIRY, 
			std::make_shared<OutputFileWriter>(HISTORYDATA_OUTPUT_INQUIRY)});
}

void BondHistoricalDataService::PersistData(string persistKey, const HistoricalData& data)
{
	auto writer_ptr = file_writer_map.find(persistKey);
	if(writer_ptr != file_writer_map.end()){
		writer_ptr->second->OutputLine(HistoricalData(data).GetContent());
	}
}

void BondHistoricalDataService::OnMessage(HistoricalData &data){
	// For BondHistoricalDataService, we don't need to store all records in memory.
	// Also we don't have enough memory to do this
}


const std::vector<string>& HistoricalData::GetContent() const
{
	return content;
}

HistoricalData::HistoricalData()
{
	content.push_back("---------------------------------------------------------");
}

HistoricalData::HistoricalData(const string& str, double d)
{
	content.push_back(str);
	content.push_back(to_string(d));
}

HistoricalData::HistoricalData(PV01<Bond>& data)
{
}

HistoricalData::HistoricalData(Position<Bond>& data)
{
	content.push_back(data.GetProduct().GetProductId());
	content.push_back(to_string(data.GetPosition("TRSY1")));
	content.push_back(to_string(data.GetPosition("TRSY2")));
	content.push_back(to_string(data.GetPosition("TRSY3")));
	content.push_back(to_string(data.GetAggregatePosition()));
}

HistoricalData::HistoricalData(ExecutionOrder<Bond>& data)
{
	content.push_back(data.GetOrderId());
	content.push_back(data.GetProduct().GetProductId());
	content.push_back(to_string(data.GetOrderType()));
	content.push_back(to_string(data.GetPrice()));
	content.push_back(to_string(data.GetVisibleQuantity()));
	content.push_back(to_string(data.GetHiddenQuantity()));
}

HistoricalData::HistoricalData(Inquiry<Bond>& data)
{
	content.push_back(data.GetInquiryId());
	content.push_back(data.GetProduct().GetProductId());
	content.push_back(to_string(data.GetSide()));
	content.push_back(to_string(data.GetPrice()));
	content.push_back(to_string(data.GetQuantity()));
	content.push_back(to_string(data.GetState()));
}

HistoricalData::HistoricalData(PriceStream<Bond>& data)
{
	content.push_back(data.GetProduct().GetProductId());
	auto bid = data.GetBidOrder();
	auto offer = data.GetOfferOrder();
	content.push_back(to_string(bid.GetSide()));
	content.push_back(to_string(bid.GetPrice()));
	content.push_back(to_string(bid.GetVisibleQuantity()));
	content.push_back(to_string(bid.GetHiddenQuantity()));
	content.push_back(to_string(offer.GetSide()));
	content.push_back(to_string(offer.GetPrice()));
	content.push_back(to_string(offer.GetVisibleQuantity()));
	content.push_back(to_string(offer.GetHiddenQuantity()));
}

