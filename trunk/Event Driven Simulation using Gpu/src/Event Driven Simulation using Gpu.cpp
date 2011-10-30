//============================================================================
// Name        : Event.cpp
// Author      : Ervin Domazet - M.Sancar Koyunlu
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include "InputVector.h"
#include "Interconnection.h"

using namespace std;

int main() {
	Interconnection *deneme=new Interconnection(5);
	InputVector *a = new InputVector(deneme,15, true);
	cout << "!!!Hello World!!!" << endl; // prints !!!Hello World!!!
	return 0;
}
