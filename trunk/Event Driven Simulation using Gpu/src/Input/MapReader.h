/*
 * MapReader.h
 *
 *  Created on: Nov 10, 2011
 *      Author: msk
 */

#ifndef MAPREADER_H_
#define MAPREADER_H_
#include <map>
#include "pugixml.hpp"
#include "../Gates/BaseGate.h"
#include "../InputVector.h"
#include "../InputVectorList.h"
using namespace pugi;
using namespace std;

class MapReader{
public:
	MapReader(char*,char*);
	~MapReader();
	void readMap(BaseGate**);
	void readInput(InputVectorList&,InputVector**);
	int getNumOfGates();
	int getNumOfInputGates();
	int getNumOfInputs();
	int getGcdDelay();
	int getMaxDelay();
	void printMap();
private:
	int gcd(int,int);
	xml_document _doc_circuit;
	xml_document _doc_input;
	int _numOfGates;
	int _numOfInputGates;
	int _numOfInputs;
	int _max_delay;
	int _gcd_delay;
	map<string,BaseGate*> _gate_address;
};


#endif /* MAPREADER_H_ */
