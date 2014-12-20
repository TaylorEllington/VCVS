/*
 * FreeFrameTable.h
 *
 *  Created on: Jul 30, 2014
 *      Author: taylor
 */

#ifndef FREEFRAMETABLE_H_
#define FREEFRAMETABLE_H_

#include "ResidentFrame.h"
#include <string>
#include <stdlib.h>
#include <stdio.h>

using namespace std;

class FreeFrameTable {
private:
	int Size;

public:

	FreeFrameTable();
	virtual ~FreeFrameTable();

	ResidentFrame * table;

	void setup(int size);
	char* listWorkingSet(int pid);

	bool checkContents(int PID, int FrameNumber);

	string residentOutput(int PID);

	int residentSize(int PID);


};

#endif /* FREEFRAMETABLE_H_ */
