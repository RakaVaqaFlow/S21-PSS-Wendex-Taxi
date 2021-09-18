#ifndef CAR
#define CAR
#include <iostream>
#include <string>
#include <vector>
#include <math.h>
#include <iomanip>
#include "Point.cpp"
#include "CarType.cpp"
using namespace std;

class Car {
private:
	string model;
	CarType carType;
	Point currentPoint;
	string colour;
	string number;
	int freeBottleOfWater = 0;
	bool isAuthorized = 0;
public:	
	Car() {
		model = "Volkswagen Polo";
		carType = CarType::ECONOMY;
		currentPoint = Point();
		colour = "white";
		number = "A111MP716";
	}
	Car(string Model, CarType CarType, string Colour, string Number) :
		model(Model), carType(CarType), colour(Colour), number(Number)
	{
		if (carType == CarType::COMFORT) freeBottleOfWater = 15;
		else if (carType == CarType::COMFORT_PLUS) freeBottleOfWater = 20;
		if (carType == CarType::BUSINESS) colour = "black";
	}
	Car(string Model, CarType CarType, Point CurrentPoint, string Colour, string Number, bool IsAuthorized) :
		model(Model), carType(CarType), currentPoint(CurrentPoint), colour(Colour), number(Number), isAuthorized(IsAuthorized)
	{
		if (carType == CarType::COMFORT) freeBottleOfWater = 15;
		else if (carType==CarType::COMFORT_PLUS) freeBottleOfWater = 20;
		if (carType == CarType::BUSINESS) colour = "black";
	}

	string getModel() {
		return model;
	}

	CarType getCarType() {
		return carType;
	}

	Point getPoint() {
		return currentPoint;
	}
	string getColour() {
		return colour;
	}
	string getNumber() {
		return number;
	}
	bool getStatus() {
		return isAuthorized;
	}
	void setPoint(int X, int Y) {
		currentPoint.x_c = X;
		currentPoint.y_c = Y;
	}
	void setPoint(Point point) {
		currentPoint.x_c = point.x_c;
		currentPoint.y_c = point.y_c;
	}
	int takeFreeBottleOfWater() {
		if (carType < CarType::COMFORT)return 0;
		if (freeBottleOfWater <= 0) return 0;
		srand(time(0));
		int bottle = rand() % freeBottleOfWater;
		freeBottleOfWater -= bottle;
		return bottle;
	}

	bool parkRightInFrontOfTheEntrance() {
		if (carType != CarType::BUSINESS) return false;
		return true;
	}
	void authorize() {
		isAuthorized = 1;
	}
};

#endif