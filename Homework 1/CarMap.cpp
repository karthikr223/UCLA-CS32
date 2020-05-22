#include "CarMap.h"
#include <iostream>
#include <string>


CarMap::CarMap():c_map() {
}

bool CarMap::addCar(std::string license) {
	return c_map.insert(license, 0);
}

double CarMap::gas(std::string license) const {
	if (c_map.contains(license)) {
		double val;
		c_map.get(license, val);
		return val;
	}
	else
		return -1;
}

bool CarMap::addGas(std::string license, double gallons) {
	if (c_map.contains(license) == false || gallons < 0) {
		return false;
	}
	else {
		double val;
		c_map.get(license, val);
		val += gallons;
		c_map.update(license, val);
		return true;
	}
}

bool CarMap::useGas(std::string license, double gallons) {
	if (c_map.contains(license) == false || gallons < 0 || gallons > gas(license)) {
		return false;
	}
	else {
		double val;
		c_map.get(license, val);
		val -= gallons;
		c_map.update(license, val);
		return true;
	}
}

int CarMap::fleetSize() const {
	return c_map.size();
}

void CarMap::print() const {
	for (int i = 0; i < c_map.size(); i++) {
		KeyType l;
		ValueType d;
		c_map.get(i, l, d);
		std::cout << l << " " << d << std::endl;
	}
}
