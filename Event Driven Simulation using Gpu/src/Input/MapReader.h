/*
 * MapReader.h
 *
 *  Created on: Nov 10, 2011
 *      Author: msk
 */

#ifndef MAPREADER_H_
#define MAPREADER_H_
#include "pugixml.hpp"
#include "../Gates/BaseGate.h"
using namespace pugi;
using namespace std;

class MapReader{
public:
	MapReader(char*);
	~MapReader();
	void readMap(BaseGate**);
	int getNumOfGates();
	int getNumOfInputsToCircuit();  //TODO (_numOfInputsToCircuit) not sure if this is necessary, can be deleted later
	void printMap();
private:
	xml_document _doc;
	int _numOfGates;
	int _numOfInputsToCircuit; //TODO (_numOfInputsToCircuit) not sure if this is necessary, can be deleted later
};


#endif /* MAPREADER_H_ */
