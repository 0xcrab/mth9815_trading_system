/* 
 * This file provides functions that can generate input files to test this 
 * trading system
 * @ Zilun Shen <shenzilun@gmail.com>
 */
#ifndef GENINPUTFILES_H
#define GENINPUTFILES_H

#include "config.hpp"
#include <string>

// Generate trade input file 
void GenTradeInputFile(std::string filename);

// Generate price input file
void GenPriceInputFile(std::string filename);

// Generate marketdata input file
void GenMarketdataInputFile(std::string filename);

// Generate inquiry input file
void GenInquiryInputFile(std::string filename);

#endif
