/*
 * Process.cpp
 *
 *  Created on: Jul 30, 2014
 *      Author: taylor
 */

#include "Process.h"

Process::Process(int pid, int pageTableSize) {

	setPID(pid);
	pageTable = new ResidentFrame[pageTableSize];
	memoryAccessCount=0;
	pageFaultCount=0;
	totalPageFaults=0;
	numberOfIntervals=0;
	residentSetSum=0;

	intervalStart=0;
}

Process::~Process() {

	delete pageTable;
}


void Process::setPID(int pid){
	PID = pid;
}
void Process::accessMemory(){
	memoryAccessCount++;
}
void Process::signialPageFault(){
	pageFaultCount++;
}
void Process::newInterval(){
	numberOfIntervals++;
	intervalStart = clock.getTime();

	totalPageFaults = totalPageFaults + pageFaultCount;
	pageFaultCount = 0;
}
void Process::noteResidentSet(int summand){
	residentSetSum = residentSetSum + summand;
}

int Process::getPID(){
	return PID;
}
int Process::getMemoryAccessCount(){
	return memoryAccessCount;
}
int Process::getPageFaultCount(){
	return pageFaultCount;
}
int Process::getNumberOfIntervals(){
	return numberOfIntervals;
}
int Process::getResidentSetSum(){
	return residentSetSum;
}

int Process::getTotalPageFaults(){
	return totalPageFaults;
}

int Process::getIntervalStart(){
	return intervalStart;
}
