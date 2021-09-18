#ifndef ADRESS
#define ADRESS
#include <stdio.h>
#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include "Point.cpp"

using namespace std;

class Adress{
private:
	string city;
	string street;
	int houseNumber;
	Point position;
public:
	Adress(string City, string Street, int HouseNumber) :
		city(City), street(Street), houseNumber(HouseNumber) {
		srand(time(0));
		position.x_c = rand() % 1000;
		position.y_c = rand() % 1000;
	}
	Adress(string City, string Street, int HouseNumber, Point Position) :
		city(City), street(Street), houseNumber(HouseNumber), position(Position) {}
	
	Adress(): 
		city("Kazan"), street("Baumana"){
		srand(time(0));
		position.x_c = rand() % 1000;
		position.y_c = rand() % 1000;
		houseNumber = rand() % 50;
	}
	string getCity() {
		return city;
	}
	string getStreet() {
		return street;
	}
	int getHouseNumber() {
		return houseNumber;
	}
	Point getPoint() {
		return position;
	}
	void setCity(string City) {
		city = City;
	}
	void setStreet(string Street) {
		street = Street;
	}
	void setHouseNumber(int HouseNumber) {
		if (houseNumber <= 0)return;
		houseNumber = HouseNumber;
	}

	string toString() {
		return city + " " + street + " " + to_string(houseNumber);
	}
};

#endif