/*
 * Clock.h
 *
 *  Created on: Jul 30, 2014
 *      Author: taylor
 */

#ifndef CLOCK_H_
#define CLOCK_H_

class Clock {
public:
	Clock();

	void tick();
	int getTime();


private:
	int time;

};

#endif /* CLOCK_H_ */
