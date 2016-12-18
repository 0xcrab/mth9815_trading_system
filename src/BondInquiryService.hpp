/**
 * BondInquiryService.hpp
 * Defines Bond Inquiry Service
 * 
 * Defines Bond Inquiry Connector that can read trade 
 * from file
 * 
 * @Zilun Shen <shenzilun@gmail.com>
 */

#ifndef BONDINQUIRYSEVICE_HPP
#define BONDINQUIRYSEVICE_HPP

#include "framework/inquiryservice.hpp"
#include "framework/products.hpp"
#include "BasicService.hpp"
#include "utility.hpp"
#include <string>

class BondInquiryService;

class BondInquiryConnector_File : public Connector<Inquiry<Bond>>,
	private InputFileReader
{
public:
	BondInquiryConnector_File(std::string file);
	void bindService(BondInquiryService &inqsrv);
	void start();
	void Publish(const Inquiry<Bond>& data) override;
private:
	BondInquiryService* srv_ptr;
};

class BondInquiryService : public InquiryService<Bond>,
	public virtual BasicService<std::string, Inquiry<Bond>>
{
public:

	// Set InquiryId as key
	BondInquiryService(const Connector<Inquiry<Bond>>& _conn);

	// Send a quote back to the client
	void SendQuote(const string &inquiryId, double price) override;

	// Reject an inquiry from the client
	void RejectInquiry(const string &inquiryId) override;

	void OnMessage(Inquiry<Bond> &data) override;

private:
	Connector<Inquiry<Bond>> *conn;
};

#endif
