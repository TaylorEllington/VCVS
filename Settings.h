/*
 * Settings.h
 *
 *  Created on: Jul 29, 2014
 *      Author: taylor
 */

#ifndef SETTINGS_H_
#define SETTINGS_H_

#include <iostream>
using namespace std;

class Settings {
private:
	// M (the minimum duration of the sampling interval, boundary protection for exceptional conditions)
	// L (the maximum duration of the sampling interval, boundary protection for exceptional conditions)
	// Q (the maximum # of page faults allowed between sampling instances)
	// F (the number of page frames)
	// P (the maximum # of processes that may be resident in main memory)

	int M, L, Q, F, P;


public:

	void setM(int m);
	void setL(int l);
	void setQ(int q);
	void setF(int f);
	void setP(int p);

	int getM();
	int getL();
	int getQ();
	int getF();
	int getP();


};

#endif /* SETTINGS_H_ */
