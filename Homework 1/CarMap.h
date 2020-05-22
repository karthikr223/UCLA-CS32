#ifndef CARMAPH
#define CARMAPH

#include "Map.h"
#include <iostream>

class CarMap
{
public:
	CarMap();       // Create an empty car map.
	bool addCar(std::string license);
	double gas(std::string license) const;
	bool addGas(std::string license, double gallons);
	bool useGas(std::string license, double gallons);
	int fleetSize() const;
	void print() const;
private:
	Map c_map;
};

#endif