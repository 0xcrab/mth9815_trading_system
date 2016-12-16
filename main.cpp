/**
 * main.cpp: This is the entrance of the trading system
 * TODO: Main functions of this trading system
 *
 * @author Zilun Shen, shenzilun@gmail.com
 */

#include <iostream>
#include <algorithm>
#include <iterator>
#include "src/utility.hpp"
#include "src/GenInputFiles.hpp"
#include "src/BondTradeBookingService.hpp"
#include "src/BondPositionService.hpp"
#include "src/BondPricingService.hpp"
using namespace std;


void testUtilities();
void testTradeBooking_n_Position();
void testPricing_n_Risk();

int main() {

	testPricing_n_Risk();
	// TODO: BondPricingService is ready, next step is to
	// implement BondRiskService and add listeners to BondPricingService
	return 0;
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

void testTradeBooking_n_Position(){
	GenTradeInputFile("testgeninputfile.txt");

	BondPositionService pos_srv;
	BondTradeBookingService trade_srv;
	BondPositionListener pos_lsn(trade_srv, pos_srv);

	// Start load trade data
	BondTradeConnector_File trade_con("./testgeninputfile.txt");
	trade_con.bindService(trade_srv);
	trade_con.start();
}
	
void testPricing_n_Risk(){
	GenPriceInputFile(PRICE_INPUT_FILE);
	
	BondPricingService prc_srv;
	BondPricingConnector_File prc_con(PRICE_INPUT_FILE);
	prc_con.bindService(prc_srv);
	prc_con.start();

}

