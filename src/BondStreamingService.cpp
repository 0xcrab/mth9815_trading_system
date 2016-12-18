#include "BondStreamingService.hpp"
#include <string>
using namespace std;

BondStreamingListener::BondStreamingListener(BondAlgoStreamingService &algostrsrv,
		BondStreamingService &bstrsrv)
{
	algostrsrv.AddListener(this);
	bstrsrv_ptr = &bstrsrv;
}

BondStreamingService::BondStreamingService(std::string path)
	: fileWriter(path)
{
}

void BondStreamingListener::ProcessAdd(AlgoStream& data)
{
	bstrsrv_ptr->PublishPrice(data.GetPriceStream());
}

void BondStreamingService::PublishPrice(const PriceStream<Bond>& priceStream)
{
	fileWriter.Publish(priceStream);
	auto tmp = priceStream;
	BasicService::OnMessage(tmp);
}

BondStreamingConnector_File::BondStreamingConnector_File(std::string path)
	: OutputFileWriter(path)
{
}

void BondStreamingConnector_File::Publish(const PriceStream<Bond> &priceStream)
{
	OutputFileWriter::OutputLine({priceStream.GetProduct().GetProductId(),
				to_string(priceStream.GetBidOrder().GetPrice()),
				to_string(priceStream.GetBidOrder().GetHiddenQuantity()),
				to_string(priceStream.GetBidOrder().GetVisibleQuantity()),
				to_string(priceStream.GetOfferOrder().GetPrice()),
				to_string(priceStream.GetOfferOrder().GetHiddenQuantity()),
				to_string(priceStream.GetOfferOrder().GetVisibleQuantity())
				});
}

