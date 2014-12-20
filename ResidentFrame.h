/*
 * ResidentFrame.h
 *
 *  Created on: Jul 30, 2014
 *      Author: taylor
 */

#ifndef RESIDENTFRAME_H_
#define RESIDENTFRAME_H_

class ResidentFrame {
public:
	ResidentFrame();


	void setUseBit(bool);
	bool checkUseBit();


	void setOwnerPID(int);
	int getOwnerPID();

	void setOwnerPageNumber(int);
	int getOwnerPageNumber();

	void clear();


private:
	bool useBit;
	int ownerPID;
	int ownerPageNumber;

};

#endif /* RESIDENTFRAME_H_ */
