/*
 * Driver.h
 *
 *  Created on: Jul 29, 2014
 *      Author: taylor
 */

#ifndef DRIVER_H_
#define DRIVER_H_

#include <iostream>

#include "Parser.h"
#include "EventLog.h"
#include "Settings.h"
#include "FreeFrameTable.h"
#include "Process.h"



using namespace std;

class Driver {
public:

	Parser parser;
	EventLog eventlog;
	Settings settings;


	Driver();
	~Driver();
	void run();

private:
	Process ** processes;
	FreeFrameTable pageFrameTable;

	void newProcess(int PID, int tableSize);
	void read(int PID, int PageToRead);
	void write(int PID, int PageToWrite);
	void terminate(int PID);

	bool checkInterval(int PID);

	void clearUseBits(int PID);
	void discardUnusedPages(int PID);

	void discardAllPages(int PID);
	void DebugFrameTablePrint();

};

#endif /* DRIVER_H_ */
