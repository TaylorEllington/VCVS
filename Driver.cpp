/*
 * Driver.cpp
 *
 *  Created on: Jul 29, 2014
 *      Author: taylor
 */

#include "Driver.h"

Driver::Driver(){

	//To easily change settings alter these lines. values in comments are the values given in assignment hand out
	settings.setM(4);	//	M = 4.  (boundary protection for exceptional conditions)
	settings.setL(6);	//	L = 6. (boundary protection for exceptional conditions)
	settings.setQ(3);	//	Q = 3.
	settings.setF(16);	//	F = 16 (0..15).
	settings.setP(4);	//	P = 4.


	processes = new Process*[settings.getP()];

	pageFrameTable.setup(settings.getF());



}

Driver::~Driver(){

	delete[] processes;
}

void Driver::run(){

	while(parser.MoreCommandsExist()){
		parser.next();

		if(parser.getCommand() == 'n'){

			newProcess(parser.getPID(), parser.getPageNumber());

		}else if(parser.getCommand() == 'r'){

			read(parser.getPID(), parser.getPageNumber());

		}else if(parser.getCommand() == 'w'){

			write( parser.getPID(), parser.getPageNumber() );

		}else if(parser.getCommand() == 't'){

			terminate( parser.getPID() );

		}



	}// end of while




}

void Driver::newProcess(int PID, int tableSize){
	processes[PID] = new Process(PID, tableSize);
	eventlog.logNew(parser.getPID(), parser.getPageNumber());

}
void Driver::read(int PID, int PageToRead){
	int firstEmptyPageFrame = -1;
	bool pageFoundInFrame = false;

	processes[PID]->accessMemory();

	//check PageFrameTable for requested page
	for(int i = 0; i < settings.getF(); i++){
		if(pageFrameTable.table[i].getOwnerPID() == PID && pageFrameTable.table[i].getOwnerPageNumber() == PageToRead){
			//if there: set usebit to 1 (aka true)
			pageFrameTable.table[i].setUseBit(true);
			pageFoundInFrame = true;
			firstEmptyPageFrame = i;
			break;
		}else if(firstEmptyPageFrame == -1 && pageFrameTable.table[i].getOwnerPID() == -1){
			firstEmptyPageFrame = i;
		}
	}

	//if not there:
	if( !pageFoundInFrame && firstEmptyPageFrame != -1){
		//pagefault for that PID
		processes[PID]->signialPageFault();

		//add page to PageFrameTable
		pageFrameTable.table[firstEmptyPageFrame].setOwnerPID(PID);
		pageFrameTable.table[firstEmptyPageFrame].setOwnerPageNumber(PageToRead);
		//set usebit
		pageFrameTable.table[firstEmptyPageFrame].setUseBit(true);
	}

	if(!pageFoundInFrame && firstEmptyPageFrame == -1){
		//log no free frame error
		eventlog.logReadWriteError( PID, PageToRead);
	}else{
		//log transaction
		eventlog.logRead(PID, PageToRead, firstEmptyPageFrame, pageFrameTable.residentOutput(PID));

	}

	//tick clock for calling process
	processes[PID]->clock.tick();


	//check interval bounds
	if( checkInterval(PID)){
		//if bounds met, clean working set

		discardUnusedPages(PID);
		clearUseBits(PID);
		eventlog.logIntervalStats(PID, pageFrameTable.residentSize(PID), pageFrameTable.residentOutput(PID) );

		processes[PID]->noteResidentSet(pageFrameTable.residentSize(PID) );
		processes[PID]->newInterval();



	}
			//if not met, do nothing

}
void Driver::write(int PID, int PageToWrite){
	int firstEmptyPageFrame = -1;
	bool pageFoundInFrame = false;

	processes[PID]->accessMemory();

	//check PageFrameTable for requested page
	for(int i = 0; i < settings.getF(); i++){
		if(pageFrameTable.table[i].getOwnerPID() == PID && pageFrameTable.table[i].getOwnerPageNumber() == PageToWrite){
			//if there: set usebit to 1 (aka true)
			pageFrameTable.table[i].setUseBit(true);
			pageFoundInFrame = true;
			firstEmptyPageFrame = i;
			break;
		}else if(firstEmptyPageFrame == -1 && pageFrameTable.table[i].getOwnerPID() == -1){
			firstEmptyPageFrame = i;
		}
	}

	//if not there:
	if( !pageFoundInFrame && firstEmptyPageFrame != -1){
		//pagefault for that PID
		processes[PID]->signialPageFault();
		//add page to PageFrameTable
		pageFrameTable.table[firstEmptyPageFrame].setOwnerPID(PID);
		pageFrameTable.table[firstEmptyPageFrame].setOwnerPageNumber(PageToWrite);
		//set usebit
		pageFrameTable.table[firstEmptyPageFrame].setUseBit(true);
	}

	if(!pageFoundInFrame && firstEmptyPageFrame == -1){
			//log no free frame error
		eventlog.logReadWriteError( PID, PageToWrite);

	}else{
		// log transaction
		eventlog.logWrite(PID, PageToWrite, firstEmptyPageFrame, pageFrameTable.residentOutput(PID) );
	}


	processes[PID]->clock.tick();

		//check interval bounds
		if( checkInterval(PID)){
			//if bounds met, clean working set

			discardUnusedPages(PID);
			clearUseBits(PID);
			processes[PID]->newInterval();
			processes[PID]->noteResidentSet(pageFrameTable.residentSize(PID) );
		}
			//if not met, do nothing
}
void Driver::terminate(int PID){

	//gather stats, and log transaction
	processes[PID]->newInterval();
	processes[PID]->noteResidentSet(pageFrameTable.residentSize(PID));


	int memAccesses = processes[PID]->getMemoryAccessCount();
	int totalFaults = processes[PID]->getTotalPageFaults();
	int totalIntervals = processes[PID]->getNumberOfIntervals();
	int sumOfSets = processes[PID]->getResidentSetSum();



	eventlog.logTerminate(PID, memAccesses, totalFaults, totalIntervals, sumOfSets);

	// remove pages from page table
	discardAllPages(PID);
	// destroy process
	delete processes[PID];
}

bool Driver::checkInterval(int PID){
	//uses VSWS policy to determine state of sampling instance

	int currentTime = processes[PID]->clock.getTime();
	int lastInterval = processes[PID]->getIntervalStart();
	int L = settings.getL();
	int M = settings.getM();
	int Q = settings.getQ();
	int numberOffaults = processes[PID]->getPageFaultCount();


	if( (currentTime >= L + lastInterval) || (currentTime >= M + lastInterval && numberOffaults >= Q ) )
		return true;
	else
		return false;
}

void Driver::clearUseBits(int PID){
	for (int i = 0; i < settings.getF(); i++){
		if(pageFrameTable.table[i].getOwnerPID() == PID){
			pageFrameTable.table[i].setUseBit(false);
		}
	}

}
void Driver::discardUnusedPages(int PID){
	for (int i = 0; i < settings.getF(); i++){
		if(pageFrameTable.table[i].getOwnerPID() == PID && !pageFrameTable.table[i].checkUseBit() ){
			pageFrameTable.table[i].clear();
		}
	}

}
void Driver::discardAllPages(int PID){
	for (int i = 0; i < settings.getF(); i++){
			if(pageFrameTable.table[i].getOwnerPID() == PID ){
				pageFrameTable.table[i].clear();
			}
		}
}
void Driver::DebugFrameTablePrint(){
	for( int i = 0; i < settings.getF(); i++){
		cout << i<< "|" << pageFrameTable.table[i].getOwnerPID() << "|" <<   pageFrameTable.table[i].getOwnerPageNumber() << "|" << pageFrameTable.table[i].checkUseBit() << endl;
	}
}





