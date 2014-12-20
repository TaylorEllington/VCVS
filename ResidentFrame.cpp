/*
 * ResidentFrame.cpp
 *
 *  Created on: Jul 30, 2014
 *      Author: taylor
 */

#include "ResidentFrame.h"

ResidentFrame::ResidentFrame() {
	setOwnerPID(-1);
	setOwnerPageNumber(-1);
	setUseBit(false);
}
void ResidentFrame::setUseBit(bool bit){
	useBit = bit;
}
bool ResidentFrame::checkUseBit(){
	return useBit;
}
void ResidentFrame::setOwnerPID(int pid){
	ownerPID = pid;
}
int ResidentFrame::getOwnerPID(){
	return ownerPID;
}
void ResidentFrame::setOwnerPageNumber(int pageNumber){
	ownerPageNumber = pageNumber;
}
int ResidentFrame::getOwnerPageNumber(){
	return ownerPageNumber;
}
void ResidentFrame::clear(){
	setOwnerPID(-1);
	setOwnerPageNumber(-1);
	setUseBit(false);
}

