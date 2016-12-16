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

#endif
