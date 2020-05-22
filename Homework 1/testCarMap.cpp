#include "CarMap.h"
#include <iostream>
#include <cassert>
using namespace std;

int main()
{
	CarMap c;  // maps strings to doubles
	c.addCar("ABC123");
	c.addCar("BAC123");
	c.addCar("ACD123");
	c.addCar("ZZZ123");
	c.addGas("ABC123", 10);
	assert(c.gas("ABC123") == 10);
	assert(c.fleetSize() == 4);
	c.print();
	c.useGas("ABC123", 5);
	assert(c.gas("ABC123") == 5);
	cout << "Passed all tests" << endl;
}