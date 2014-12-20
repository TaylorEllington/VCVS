/*
 * EventLog.cpp
 *
 *  Created on: Jul 29, 2014
 *      Author: taylor
 */

#include "EventLog.h"

EventLog::EventLog() {


	logOut.open("status.txt", ofstream::out);


}

EventLog::~EventLog() {

	logOut.flush();
	logOut.close();
}



void EventLog::logNew(int PID, int pageTableSize){

	cout << "Process " << PID << " is created. Page Table size is " << pageTableSize << " Number of resident pages is 0." << endl;
	logOut << "Process " << PID << " is created. Page Table size is " << pageTableSize << " Number of resident pages is 0." << endl;



}
void EventLog::logRead(int PID, int page, int frame, string set){
	//TODO finish
	cout << "Process "<< PID <<" is reading from virtual page "<< page
			<<" which occupies frame "<<frame <<".  Number of resident pages is "<<set<<"." << endl;

	logOut<< "Process "<< PID <<" is reading from virtual page "<< page
			<<" which occupies frame "<<frame <<".  Number of resident pages is "<<set<<"." << endl;
}
void EventLog::logWrite(int PID, int page, int frame, string set){
	//TODO finish

	cout << "Process "<< PID <<" is writing to virtual page "<< page
				<<" which occupies frame "<<frame <<".  Number of resident pages is "<<set<<"." << endl;

	logOut<< "Process "<< PID <<" is writing to virtual page "<< page
				<<" which occupies frame "<<frame <<".  Number of resident pages is "<<set<<"." << endl;

}
void EventLog::logTerminate(int PID, int memAccesses, int totalFaults, int totalIntervals, int sumOfSets){
	//TODO finish
	double pageFaultPercentage, avgSetSize;

	pageFaultPercentage = (double) totalFaults / (double) memAccesses;
	avgSetSize = (double) sumOfSets / (double) totalIntervals;

	cout << "Process "<< PID <<" terminated.  Total memory accesses: "<< memAccesses
			<<".   Total page faults: "<< totalFaults << ". Page fault percentage: "<< pageFaultPercentage
			<<".   Average resident set size: "<< avgSetSize << "." << endl;

	logOut << "Process "<< PID <<" terminated.  Total memory accesses: "<< memAccesses
			<<".   Total page faults: "<< totalFaults << ". Page fault percentage: "<< pageFaultPercentage
			<<".   Average resident set size: "<< avgSetSize << "." << endl;
}
void EventLog::logIntervalStats(int PID, int  resSetSize, string set){

	cout << "Process "<< PID <<" use-bits scanned.  New resident set size is "<< resSetSize
			<< ".   Resident set: " <<set << "." << endl;

	logOut << "Process "<< PID <<" use-bits scanned.  New resident set size is "<< resSetSize
					<< ".   Resident set: " <<set << "." << endl;


}
void EventLog::logReadWriteError(int PID, int pageNumber){

	cout << "Error: No free frame. Request from Process " << PID << ", page " << pageNumber << "." << endl;
	logOut  << "Error: No free frame. Request from Process " << PID << ", page " << pageNumber << "." << endl;


}
