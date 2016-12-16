#include "GenInputFiles.hpp"
#include <fstream>
#include <iterator>
#include <cstdlib>
#include <algorithm>
#include <iostream>
#include "utility.hpp"

using namespace std;


void GenTradeInputFile(std::string filename){
	ofstream out(filename);
	vector<string> TRSY_LIST = {"TRSY1", "TRSY2", "TRSY3"};
	vector<string> DIRECTION = {"BUY", "SELL"};
	int cnt=0;
	for(auto&& bondid : CUSIPS_LIST){
		for(int i=1; i<=NUM_OF_TRADE; i++){
			vector<string> record = { 
				"T"+to_string(++cnt), // trade id
				bondid, // bond id
				TRSY_LIST[rand()%3], // TRSY
				//BondPrice_double2string(100 + (rand()%512 - 256) / 256.0), // price
				to_string((rand()%10)*10000), // volume
				DIRECTION[rand()%2] // direction
			};

			copy(record.begin(), record.end(),
					ostream_iterator<string>(out, ","));
			out << endl;
		}
	}
	out.close();
}

void GenPriceInputFile(string filename){
	ofstream out(filename);
	for(auto&& bondid : CUSIPS_LIST){
		for(int i=1; i<=NUM_OF_PRICE; i++){
			double mid = 100 + (rand()%512 - 256) / 256.0;
			double spread = (rand()%3 + 2) / 256.0;
			vector<string> record = {
				bondid, // bond id
				BondPrice_double2string(mid), // mid price
				BondPrice_double2string(spread) // bid/offer spread
			};
			copy(record.begin(), record.end(),
					ostream_iterator<string>(out, ","));
			out << endl;
		}
	}
}
