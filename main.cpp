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
using namespace std;

int main() {

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
	return 0;
}

