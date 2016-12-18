/** 
 * This file provides several useful tools in the trading system project
 * such as convert price between string and double, reading csv files
 * and output csv files
 * @ Zilun Shen <shenzilun@gmail.com>
 */
#ifndef UTILITY_H
#define UTILITY_H

#include <string>
#include <fstream>
#include <vector>
#include "framework/products.hpp"

// Read input data from .csv file
class InputFileReader{
public:
	InputFileReader(const std::string& _path);
	~InputFileReader();
	bool getNextLine(std::vector<std::string>& vline);
private:
	std::string filepath;
	std::ifstream indata;
};

// Output data to a .csv file
class OutputFileWriter{
public:
	OutputFileWriter(const std::string&_path);
	~OutputFileWriter();
	void OutputLine(const std::vector<std::string>& vline);
private:
	std::string filepath;
	std::ofstream outdata;
};

// Convert from fraction notation to decimal
double BondPrice_string2double(std::string strprice);
// Convert from decimal notation to fraction
std::string BondPrice_double2string(double dprice);

// Create Bond from CUSIP id
Bond makeBond(std::string bondid);

// Calculate Bond PV01
double BondPV01(const std::string cusip);

#endif
