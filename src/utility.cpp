#include "utility.hpp"
#include <iostream>
#include <cmath>
#include <utility>
#include <fstream>
#include <sstream>
#include <vector>
#include "config.hpp"
using namespace std;

InputFileReader::InputFileReader(const std::string& _path)
	: filepath(_path)
{
	indata.open(filepath);
}

InputFileReader::~InputFileReader()
{
	indata.close();
}

bool InputFileReader::getNextLine(std::vector<std::string>& vline)
{
	vline.clear();
	string line;
	if(getline(indata, line)){
		stringstream lineStream(line);
		string cell;
		while(getline(lineStream, cell, ',')){
			vline.push_back(cell);
		}
		return true;
	}
	return false;
}

// Convert from fraction notation to decimal
double BondPrice_string2double(std::string strprice){
	double dprice;
	// exclude -xyz part from 100-xyz
	dprice = stoi(strprice.substr(0, strprice.length()-4));
	dprice += stoi(strprice.substr(strprice.length()-3, 2)) / 32.0;
	if(strprice.back() == '+')	strprice.back() = '4';
	dprice += stoi(strprice.substr(strprice.length()-1)) / 256.0;
	return dprice;
}

// Convert from decimal notation to fraction
std::string BondPrice_double2string(double dprice){
	std::string strprice;
	int big = static_cast<int>(dprice);
	dprice -= big;
	strprice = std::to_string(big);
	strprice += '-';
	// round to 1/256
	int iprice = static_cast<int>(dprice * 256 + 0.5);
	int r = iprice % 8;
	strprice += std::to_string(iprice / 80);
	strprice += std::to_string(iprice / 8 % 10);
	if(r == 4)	strprice += '+';
	else strprice += std::to_string(r);
	return strprice;
}

// Create Bond from CUSIP id
Bond makeBond(std::string bondid){
	size_t i;
	for(i=0; i<NUM_OF_BONDS; i++){
		if(CUSIPS_LIST[i] == bondid){
			return Bond(bondid,
					BOND_ID_TYPE_LIST[i],
					TICKER_LIST[i],
					COUPON_LIST[i],
					MATURITY_LIST[i]);
		}
	}
	return Bond();
}
