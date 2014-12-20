/*
 * Process.h
 *
 *  Created on: Jul 30, 2014
 *      Author: taylor
 */

#ifndef PROCESS_H_
#define PROCESS_H_

#include "ResidentFrame.h"
#include "Clock.h"
#include <iostream>

using namespace std;

class Process {
public:
	Clock clock;

	Process(int, int);
	~Process();

	void setPID(int pid);
	void accessMemory();
	void signialPageFault();
	void newInterval();
	void noteResidentSet(int summand);


	int getPID();
	int getMemoryAccessCount();
	int getPageFaultCount();
	int getTotalPageFaults();
	int getNumberOfIntervals();
	int getResidentSetSum();
	int getIntervalStart();



private:
	int PID;
	int memoryAccessCount;
	int pageFaultCount;
	int totalPageFaults;
	int numberOfIntervals;
	int residentSetSum;

	int intervalStart;

	ResidentFrame * pageTable;

};

#endif /* PROCESS_H_ */
