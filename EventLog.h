/*
 * EventLog.h
 *
 *  Created on: Jul 29, 2014
 *      Author: taylor
 */

#ifndef EVENTLOG_H_
#define EVENTLOG_H_

#include <iostream>
#include <fstream>
using namespace std;



class EventLog {
private:
	ofstream logOut;

public:
	EventLog();
	~EventLog();

	void logNew(int PID, int pageTableSize);
	void logRead(int PID, int page, int frame, string set);
	void logWrite(int PID, int page, int frame, string set);
	void logTerminate(int PID, int memAccesses, int totalFaults, int totalIntervals, int sumOfSets);

	void logReadWriteError(int PID, int pageNumber);

	void logIntervalStats(int PID, int  resSetSize, string set);



};

#endif /* EVENTLOG_H_ */
