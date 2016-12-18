/**
 * This file defines some global variable 
 * @ Zilun Shen <shenzilun@gmail.com>
 */

#ifndef TRADINGSYSTEM_CONFIG_H
#define TRADINGSYSTEM_CONFIG_H

#include <string>
#include <vector>
#include "framework/products.hpp"
#include "boost/date_time/gregorian/gregorian.hpp"
using boost::gregorian::date;
using boost::date_time::Nov;

// Total number of bonds
const int NUM_OF_BONDS = 6;
const std::vector<std::string> CUSIPS_LIST = {
	"912828M72",
	"912828N22",
	"912828M98",
	"912828M80",
	"912828M56",
	"912810RP5"
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

// Trade intput csv file name
const std::string TRADE_INPUT_FILE = "./input/trades.txt";
// Number of trade for each bond
const int NUM_OF_TRADE = 10;

// Price input csv file name
const std::string PRICE_INPUT_FILE = "./input/price.txt";
// Number of trade for each bond
const int NUM_OF_PRICE = 10;

// Marketdata input csv file name
const std::string MARKETDATA_INPUT_FILE = "./input/marketdata.txt";
// Number of marketdata for each bond
const int NUM_OF_MARKETDATA = 10;

// BondStreamingService output file
const std::string BONDSTREAM_OUTPUT_FILE = "./output/bondstream.txt";

// Inquiry input csv file name
const std::string INQUIRY_INPUT_FILE = "./input/inquiry.txt";
// Number of inquiry for each bond
const int NUM_OF_INQUIRY = 10;


#endif
