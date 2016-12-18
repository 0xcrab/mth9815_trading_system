#include "BondInquiryService.hpp"
#include "framework/inquiryservice.hpp"
#include "utility.hpp"
#include <string>
#include <iostream>
using namespace std;

BondInquiryService::BondInquiryService(const Connector<Inquiry<Bond>>& _conn)
	: BasicService<string, Inquiry<Bond>>
	  ([](const Inquiry<Bond>& v){return v.GetInquiryId();}),
	  conn(&const_cast<Connector<Inquiry<Bond>>&>(_conn))
{
}

BondInquiryConnector_File::BondInquiryConnector_File(std::string file)
	: InputFileReader(file) 
{
}

void BondInquiryService::OnMessage(Inquiry<Bond> &data)
{
	switch(data.GetState()){
		case RECEIVED :
			BasicService::OnMessage(data);
			SendQuote(data.GetInquiryId(), 100.00);
			break;
		case QUOTED :
			// Do not send back any thing
			BasicService::OnMessage(data);
			break;
		case DONE : 
			// Do not send back any thing
			BasicService::OnMessage(data);
#ifdef DEBUG_PRINT_DEMO
			cout << data.GetInquiryId() 
				 << "\t Price: " << data.GetPrice() 
				 << "\t" << "Done!" << endl;
#endif
			break;
		default :
			break;
	}
}

void BondInquiryConnector_File::Publish(const Inquiry<Bond>& data)
{
	// Set state to QUOTED
	auto quoted = data;
	quoted.ChangeState(QUOTED);
	srv_ptr->OnMessage(quoted);
	// Set state to DONE
	quoted.ChangeState(DONE);
	srv_ptr->OnMessage(quoted);
}

void BondInquiryService::RejectInquiry(const string &inquiryId)
{
}

void BondInquiryService::SendQuote(const string &inquiryId, double price)
{
	auto inq = BasicService::GetData(inquiryId);
	inq.ChangePrice(price);
	conn->Publish(inq);
}

void BondInquiryConnector_File::bindService(BondInquiryService &inqsrv)
{
	srv_ptr = &inqsrv;
}

void BondInquiryConnector_File::start()
{
	vector<string> record;
	if(srv_ptr != nullptr){
		while(getNextLine(record)){
			Inquiry<Bond> inq(record[0],
					makeBond(record[1]),
					Side(stoi(record[2])),
					stoi(record[3]),
					BondPrice_string2double(record[4]),
					InquiryState(stoi(record[5])));
			srv_ptr->OnMessage(inq);
		}
	}
}

