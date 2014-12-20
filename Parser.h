/*
 * Parser.h
 *
 *  Created on: Jul 29, 2014
 *      Author: taylor
 */

#ifndef PARSER_H_
#define PARSER_H_

#include <iostream>
#include <fstream>
#include <string.h>
#include <stdlib.h>
using namespace std;

class Parser {

private:
	ifstream commandIn;
	int PID, PageNumber;
	char Command;

public:
	Parser();
	//~Parser();
	void next();

	int getPID();
	char getCommand();
	int getPageNumber();

	bool MoreCommandsExist();




};

#endif /* PARSER_H_ */
