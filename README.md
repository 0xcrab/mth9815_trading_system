#Bond Trading System for MTH9815
This is the final project for MTH9815 Fall 2016. 

### Input and output
All input files will be generated under *input* folder, and output files
will be under *output* folder. 
The header file ```GenInputFiles.hpp``` provides a series of functions that can generate trading, market, price, inquiry and all kinds of data that are needed as input for this system.


### How to build
This project can be build with CMake3.5.2 and g++6.2.0
```
cmake .
make
./main.out
```