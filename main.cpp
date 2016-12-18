/**
 * main.cpp: This is the entrance of the trading system
 * This is the entrance of this system
 * In main function, there is a demo of this trading system.
 *
 * @author Zilun Shen, shenzilun@gmail.com
 */

#include <iostream>
#include <algorithm>
#include <iterator>
#include "src/config.hpp"
#include "src/utility.hpp"
#include "src/GenInputFiles.hpp"
#include "src/BondTradeBookingService.hpp"
#include "src/BondPositionService.hpp"
#include "src/BondPricingService.hpp"
#include "src/BondRiskService.hpp"
#include "src/BondMarketdataService.hpp"
#include "src/BondAlgoStreamingService.hpp"
#include "src/BondStreamingService.hpp"
#include "src/BondInquiryService.hpp"
#include "src/BondAlgoExcutionService.hpp"
#include "src/BondExecutionService.hpp"
#include "src/BondHistoricalDataService.hpp"
using namespace std;

void testUtilities();
void testTradeBooking_n_Position_n_Risk();
void testPricing_n_Stream();
void testMarketdata();
void testInquiry();

BondHistoricalDataService hist_srv;

int main() {

	testTradeBooking_n_Position_n_Risk();
	testPricing_n_Stream();
	testMarketdata();
	testInquiry();
	return 0;
}

void testInquiry(){
	// Test Inquiry
	cout << "------------------------------------------------" << endl;
	cout << "Generating Inquiry input file...";
	GenInquiryInputFile(INQUIRY_INPUT_FILE);
	cout << " Done!" << endl;
	BondInquiryConnector_File inq_conn(INQUIRY_INPUT_FILE);
	BondInquiryService inq_srv(inq_conn);

	cout << "BondInquiryService Created" << endl;

	BondHistoricalDataListener<Inquiry<Bond>> hist_inq_lsn(SERVICE_KEY_INQUIRY, inq_srv, hist_srv);
	
	cout << "BondInquiryConnector Started. Sending data to service...";
	inq_conn.bindService(inq_srv);
	inq_conn.start();
	cout << " Done!" << endl;
}

void testMarketdata(){
	cout << "------------------------------------------------" << endl;
	cout << "Generating Marketdata input file...";
	GenMarketdataInputFile(MARKETDATA_INPUT_FILE);
	cout << " Done!" << endl;
	BondMarketdataService mkt_srv;
	cout << "BondMarketdataService Created" << endl;
	// Input a orderbook and show AggregateDepth 
	BondMarketdataConnector_Demo mkt_con_demo;
	mkt_con_demo.bindService(mkt_srv);

	cout << "Use sample data to show AggregateDepth function" << endl;

	auto make_order_stack = [=](vector<double> price, PricingSide side){
		vector<Order> stk;
		for(auto i : price){
			stk.push_back(Order(i, 1000, side));
		}
		return stk;
	};

	// Generate sample orderbook, the volume is 1000 on each order
	mkt_con_demo.AddOrderBook(OrderBook<Bond>(
			makeBond(CUSIPS_LIST[0]),
			make_order_stack({99.998, 99.997, 99.994, 99.998}, BID),
			make_order_stack({100.001, 100.002, 100.001, 100.001}, OFFER)
			));
	cout << "AggregateDepth on 99.998 : " << 
		mkt_srv.AggregateDepth(CUSIPS_LIST[0], 99.998) << endl;
	cout << "AggregateDepth on 100.001 : " << 
		mkt_srv.AggregateDepth(CUSIPS_LIST[0], 100.001) << endl;


	BondMarketdataConnector_File mkt_con(MARKETDATA_INPUT_FILE);
	// Test Algo Execution Service
	BondAlgoExcutionService algo_srv;
	BondAlgoExcutionListener algo_lsn(mkt_srv, algo_srv);
	BondExecutionService exe_srv;
	BondExecutionListener exe_lsn(algo_srv, exe_srv);
	cout << "BondAlgoExecutionService Created" << endl;
	cout << "BondExecutionService Created" << endl;

	BondHistoricalDataListener<ExecutionOrder<Bond>> hist_exe_lsn(SERVICE_KEY_EXECUTION, exe_srv, hist_srv);

	cout << "BondMarketdataConnector Started. Sending data to service...";
	mkt_con.bindService(mkt_srv);
	mkt_con.start();
	cout << "Done!" <<endl;
}

void testTradeBooking_n_Position_n_Risk(){

	cout << "------------------------------------------------" << endl;
	cout << "Generating Trade input file...";
	GenTradeInputFile(TRADE_INPUT_FILE);
	cout << " Done!" << endl;

	BondPositionService pos_srv;
	BondTradeBookingService trade_srv;
	BondPositionListener pos_lsn(trade_srv, pos_srv);
	cout << "BondPositionService Created" << endl;

	BondRiskService risk_srv;
	BondRiskListener risk_lsn(pos_srv, risk_srv);
	cout << "BondRiskService Created" << endl;

	BondHistoricalDataListener<Position<Bond>> hist_pos_lsn(SERVICE_KEY_POSITION, pos_srv, hist_srv);
	BondHistoricalDataListener<PV01<Bond>> hist_risk_lsn(SERVICE_KEY_RISK, risk_srv, hist_srv);

	// Start load trade data
	cout << "BondTradeConnector Started. Sending data to service...";
	BondTradeConnector_File trade_con(TRADE_INPUT_FILE);
	// This connector reads file and is reusable.
	trade_con.bindService(trade_srv);
	trade_con.start();
	cout << "Done!" <<endl;
	// Then we can still bind it to another BondTradeBookingService
}
	
void testPricing_n_Stream(){
	cout << "------------------------------------------------" << endl;
	cout << "Generating Price input file...";
	GenPriceInputFile(PRICE_INPUT_FILE);
	cout << " Done!" << endl;
	
	// Pricing service
	BondPricingService prc_srv;
	cout << "BondPricingService Created" << endl;

	// Output price stream
	BondAlgoStreamingService algostream_srv;
	BondStreamingService stream_srv(BONDSTREAM_OUTPUT_FILE);
	BondAlgoStreamingListener algostream_lsn(prc_srv, algostream_srv);
	BondStreamingListener stream_lsn(algostream_srv, stream_srv);
	cout << "BondAlgoStreamingService Created" << endl;
	cout << "BondStreamingService Created" << endl;

	BondHistoricalDataListener<PriceStream<Bond>> hist_stream_lsn(SERVICE_KEY_STREAMING, stream_srv, hist_srv);

	cout << "BondPricingConnector Started. Sending data to service...";
	BondPricingConnector_File prc_con(PRICE_INPUT_FILE);
	prc_con.bindService(prc_srv);
	prc_con.start();
	cout << "Done!" <<endl;
}

// Test price conversion and input file gen
void testUtilities(){
	cout.precision(9);
	cout << BondPrice_string2double("100-001") << endl;
	cout << BondPrice_string2double("100-22+") << endl;
	cout << BondPrice_string2double("100-15+") << endl;
	cout << BondPrice_string2double("100-256") << endl;
	cout << BondPrice_double2string(BondPrice_string2double("101-25+")) << endl;
	cout << BondPrice_double2string(BondPrice_string2double("99-15+")) << endl;
	cout << BondPrice_double2string(BondPrice_string2double("100-001")) << endl;
	cout << BondPrice_double2string(BondPrice_string2double("100-00+")) << endl;
	cout << BondPrice_double2string(BondPrice_string2double("100-000")) << endl;
	cout << BondPrice_double2string(BondPrice_string2double("100-256")) << endl;

	InputFileReader testfile("./testcsv.csv");
	vector<string> line;
	while(testfile.getNextLine(line)){
		cout << " ==> ";
		std::copy(line.begin(), line.end(),
				  std::ostream_iterator<string>(std::cout, "  / "));
		cout << endl;
	}
}
