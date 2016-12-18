#include "GenInputFiles.hpp"
#include <fstream>
#include <iterator>
#include <cstdlib>
#include <algorithm>
#include <iostream>
#include "utility.hpp"
#include "config.hpp"
#include "framework/inquiryservice.hpp"

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
	out.close();
}

void GenMarketdataInputFile(std::string filename){
	ofstream out(filename);
	const double increment = 1.0/ 256.0;
	for(auto&& bondid : CUSIPS_LIST){
		for(int i=1; i<=NUM_OF_MARKETDATA; i++){
			vector<string> record;
			record.push_back(bondid);
			double mid = 100 + (rand()%512 - 256) / 256.0;
			double bid = mid - increment;
			double ask = mid + increment;
			// bid1 --- bid5
			for(int j=0; j<5; j++){
				record.push_back(BondPrice_double2string(bid - j*increment));
				// volume
				record.push_back(to_string((j+1) * 10 * 1000000));
			}
			// ask1 --- ask5
			for(int j=0; j<5; j++){
				record.push_back(BondPrice_double2string(ask + j*increment));
				// volume
				record.push_back(to_string((j+1) * 10 * 1000000));
			}
			// output to file
			copy(record.begin(), record.end(),
					ostream_iterator<string>(out, ","));
			out << endl;
		}
	}
	out.close();
}


void GenInquiryInputFile(std::string filename){
	ofstream out (filename);
	size_t inq_id = 0;
	for(auto&& bondid : CUSIPS_LIST){
		for(int i=1; i<=NUM_OF_INQUIRY; i++){
			vector<string> record;
			record.push_back("Inquiry #" + to_string(++inq_id));
			record.push_back(bondid);
			record.push_back(to_string(rand()%2));
			record.push_back(to_string(rand()%1000000));
			record.push_back(BondPrice_double2string(
						100 + (rand()%512 - 256) / 256.0));
			record.push_back(to_string(InquiryState::RECEIVED));
			copy(record.begin(), record.end(),
					ostream_iterator<string>(out, ","));
			out << endl;
		}
	}
	out.close();
}
