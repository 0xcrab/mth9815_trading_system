#ifndef UTILITY_H
#define UTILITY_H

#include <string>
#include <fstream>
#include <vector>

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

// Convert from fraction notation to decimal
double BondPrice_string2double(std::string strprice);
// Convert from decimal notation to fraction
std::string BondPrice_double2string(double dprice);

#endif
