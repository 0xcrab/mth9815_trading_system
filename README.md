#Bond Trading System for MTH9815
This is the final project for MTH9815 Fall 2016. 

### Input and output
All input files will be generated under *input* folder, and output files
will be under *output* folder. 
The header file ```GenInputFiles.hpp``` provides a series of functions that can generate trading, market, price, inquiry and all kinds of data that are needed as input for this system.

### Sample Size
The size of *market data* and *price* for each Bond should be 1,000,000. However it cost about 3.5G memory which my laptop can't afford. Thus, I change it to 100,000 when I run this trading system.
To get a smaller sample size, please change *config.hpp*
```
// Line 77
const int NUM_OF_PRICE = 100000;
// Line 82
const int NUM_OF_MARKETDATA = 100000;
```

### How to build
This project can be build with CMake3.5.2 and g++6.2.0
```
cmake .
make
./main.out
```
