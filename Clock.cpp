/*
 * Clock.cpp
 *
 *  Created on: Jul 30, 2014
 *      Author: taylor
 */

#include "Clock.h"

Clock::Clock() {
	time = 0;
}

void Clock::tick(){
	time++;
}
int Clock::getTime(){
	return time;
}
