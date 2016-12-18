/**
 * This file defines some global variable 
 * @ Zilun Shen <shenzilun@gmail.com>
 */

#ifndef TRADINGSYSTEM_CONFIG_H
#define TRADINGSYSTEM_CONFIG_H

#include <string>
#include <vector>
#include "utility.hpp"
#include "framework/products.hpp"
#include "framework/riskservice.hpp"
#include "boost/date_time/gregorian/gregorian.hpp"
using boost::gregorian::date;
using boost::date_time::Nov;

// Total number of bonds
const int NUM_OF_BONDS = 6;
const std::string BOND_YEAR_2  = "912828U40";
const std::string BOND_YEAR_3  = "912828U73";
const std::string BOND_YEAR_5  = "912828U65";
const std::string BOND_YEAR_7  = "912828U57";
const std::string BOND_YEAR_10 = "912828U24";
const std::string BOND_YEAR_30 = "912810RU4";

const std::vector<std::string> CUSIPS_LIST = {
	BOND_YEAR_2 ,
	BOND_YEAR_3 ,
	BOND_YEAR_5 ,
	BOND_YEAR_7 ,
	BOND_YEAR_10,
	BOND_YEAR_30
};

const std::vector<double> PV01_LIST = {
	0.01974732,
	0.02333471,
	0.01587385,
	0.02387587,
	0.07124954,
	0.05928573
};

const std::vector<BondIdType> BOND_ID_TYPE_LIST{CUSIP, CUSIP, CUSIP,  CUSIP,  CUSIP,  CUSIP};
const std::vector<string> TICKER_LIST{"T", "T", "T", "T", "T", "T"};
const std::vector<float> COUPON_LIST{0.05f, 0.05f, 0.05f, 0.05f, 0.05f, 0.05f};  
const std::vector<date> MATURITY_LIST{
	date(2016, Nov, 25),
	date(2016, Nov, 25),
	date(2016, Nov, 25),
	date(2016, Nov, 25),
	date(2016, Nov, 25),
	date(2016, Nov, 25)
};

const std::vector<std::string> POSITION_BOOK_LIST{
	"TRSY1",
	"TRSY2",
	"TRSY3"
};

/*********************************************************************
 * 
 *   Describe the input file for each service
 *   
 ********************************************************************/

// Trade intput csv file name
const std::string TRADE_INPUT_FILE = "./input/trades.txt";
// Number of trade for each bond
const int NUM_OF_TRADE = 10;

// Price input csv file name
const std::string PRICE_INPUT_FILE = "./input/price.txt";
// Number of trade for each bond
const int NUM_OF_PRICE = 1000000;

// Marketdata input csv file name
const std::string MARKETDATA_INPUT_FILE = "./input/marketdata.txt";
// Number of marketdata for each bond
const int NUM_OF_MARKETDATA = 1000000;

// BondStreamingService output file
const std::string BONDSTREAM_OUTPUT_FILE = "./output/bondstream.txt";

// Inquiry input csv file name
const std::string INQUIRY_INPUT_FILE = "./input/inquiry.txt";
// Number of inquiry for each bond
const int NUM_OF_INQUIRY = 10;

/*********************************************************************
 * 
 *	 This part is for HistoricalDataService
 *   Describe the files and keys for each service
 *   
 ********************************************************************/

const std::string SERVICE_KEY_POSITION    = "Position Service";
const std::string SERVICE_KEY_RISK        = "Risk Service";
const std::string SERVICE_KEY_EXECUTION   = "Execution Service";
const std::string SERVICE_KEY_STREAMING   = "Streaming Service";
const std::string SERVICE_KEY_INQUIRY	 = "Inquiry Service";

const std::vector<std::string> SERVICE_KEY_LIST{
	SERVICE_KEY_POSITION,
	SERVICE_KEY_RISK,
	SERVICE_KEY_EXECUTION,
	SERVICE_KEY_STREAMING,
	SERVICE_KEY_INQUIRY
};

const std::string HISTORYDATA_OUTPUT_POSITION = "./output/position.txt";
const std::string HISTORYDATA_OUTPUT_RISK = "./output/risk.txt";
const std::string HISTORYDATA_OUTPUT_EXECUTION = "./output/execution.txt";
const std::string HISTORYDATA_OUTPUT_STREAMING = "./output/streaming.txt";
const std::string HISTORYDATA_OUTPUT_INQUIRY = "./output/allinquiries.txt";


#endif
