#include <iostream>
#include "Driver.h"
using namespace std;

//to build use command:
// g++ ./*.cpp
// when in the directory with this file
// Tested on genuse20.lyle.smu.edu


int main() {

	//to change values for M, L, Q, F, and P, look in Driver::Driver() in Driver.cpp



	Driver driver;
	driver.run();

}


//Increasing values of M and P slightly allowed for fewer faults, However a large increase or any decrease resulted in
// increased faults.
