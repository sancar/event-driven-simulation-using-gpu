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
	int getNumOfInputsToCircuit();
	void printMap();
private:
	xml_document _doc;
	int _numOfGates;
	int _numOfInputsToCircuit;
	int _max_delay;
};


#endif /* MAPREADER_H_ */
