/*
 * FreeFrameTable.cpp
 *
 *  Created on: Jul 30, 2014
 *      Author: taylor
 */

#include "FreeFrameTable.h"



FreeFrameTable::FreeFrameTable(){

}

void FreeFrameTable::setup(int size){
	table = new ResidentFrame[size];
	Size = size;
}

FreeFrameTable::~FreeFrameTable() {
	// TODO Auto-generated destructor stub
	delete table;
}

string FreeFrameTable::residentOutput(int PID){

	string output ="(";

	int count =0;

	char buffer[50];
	char number[50];

	for(int i = 0; i < Size; i++){
		if(table[i].getOwnerPID() == PID){

			sprintf(buffer, "%d", table[i].getOwnerPageNumber() );
			sprintf(number, "%d", i );

			output = output + buffer + ":" + number + ",";
			count++;
		}
	}
	sprintf(buffer, "%d", count );
	output = buffer + output;

	if(count > 0){
		output.at(output.length()-1) = ')';
	}


	return output;

}


int FreeFrameTable::residentSize(int PID){

	int count =0;

	for(int i = 0; i < Size; i++){
		if(table[i].getOwnerPID() == PID){
			count++;
		}
	}

	return count;

}
