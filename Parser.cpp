/*
 * Parser.cpp
 *
 *  Created on: Jul 29, 2014
 *      Author: taylor
 */

#include "Parser.h"


Parser::Parser(){


	commandIn.open("VSWSsystemTrace.txt", ifstream::in);

}

void Parser::next(){
	char temp[256]; //holds each line while parsed

	char id[256];
	char command;
	char pageNumber[256];

	int idCount = 0,  pageNumberCount = 0; //place holders for multi character strings

	int parserType =0; //0 for id, 1 for command, 2 for page number

	commandIn.getline(temp, 265, '\n'); //read in next line

	for(int i = 0; i < (unsigned) strlen(temp); i++){
		//parse line stored in temp in to 3 seperate entries

		//ignore spaces
		if(temp[i] == ' ' ){

			if(parserType == 0){
				parserType =1;
			}

		}else{
			//if not a space store data in one of 3 fields
			if( parserType ==0 ) {
				id[idCount] = temp[i];
				idCount++;
			}else if(parserType == 1){
				command = temp[i];
				parserType=2;
			}else if(parserType == 2){
				pageNumber[pageNumberCount]= temp[i];
				pageNumberCount++;
			}else{
				cout << "ERROR IN PARSER::read()"  << endl;
				//if this appears use the VSWSsystemTrace.txt supplied with this code.
			}

		}// end of else

	}

	id[idCount]= '\0';
	pageNumber[pageNumberCount] = '\0';

	//cast fields to appropriate types and store in class variables for later access.
	PID = atoi(id);
	Command = command;
	PageNumber = atoi(pageNumber);



	//DEBUG STATEMENTS
	//cout << temp<< endl;
	//cout << id <<"|" << command << "|" << pageNumber<<endl;
}


bool Parser::MoreCommandsExist(){

	if(commandIn.eof()){
		return false;
	}else{
		return true;
	}




}

int Parser::getPID(){
	return PID;
}
char Parser::getCommand(){
	return Command;
}
int Parser::getPageNumber(){
	return PageNumber;
}


