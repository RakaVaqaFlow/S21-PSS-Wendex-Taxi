#ifndef DRIVER
#define DRIVER
#include <iostream>
#include <string>
#include <vector>
#include <math.h>
#include <iomanip>
#include "User.cpp"
#include "Car.cpp"
using namespace std;

enum class DriverStatus {
	FREE, NOT_WORKING, ON_WAY_TO_CLIENT, ON_WAY_WITH_CLIENT
};


class Driver : public User{
private:
	int getFunctionLockIndex(string functionName) {
		if (functionName == "Login") return 2;
		else if (functionName == "showOrderHistory") return 3;
		else if (functionName == "updateStatus") return 5;
		else if (functionName == "checkOrders") return 7;
		else if (functionName == "acceptOrder") return 11;
		else if (functionName == "declineOrder") return 13;
		else return 1;
	}
	DriverStatus status;
	vector<Car> cars;
	Car currentCar;
	int blockIndex = 1;
public:
	Driver() {
		name = "Name";
		surname = "Surname";
		password = "";
		status = DriverStatus::NOT_WORKING;
		rating = 0;
		tripsNum = 0;
		totalRating = 0;
	}
	Driver(string Name, string Surname, string Password, Car driverCar, string ID, int BlockIndex):
		User(Name, Surname, Password, ID), currentCar(driverCar), blockIndex(BlockIndex) {
		cars.push_back(currentCar);
	}

	Driver(string Name, string Surname, string Password, vector<Order> OrderHistory, 
		vector<string>UsersID, double Rating, int TripsNum, double TotalRating, Car driverCar, vector<Car> Cars, int BlockIndex):
		User(Name, Surname, Password,  OrderHistory, UsersID, Rating, TripsNum, TotalRating), 
		currentCar(driverCar), cars(Cars), blockIndex(BlockIndex), status(DriverStatus::NOT_WORKING) {}
	
	Car getCar() {
		return currentCar;
	}
	DriverStatus getStatus() {
		return status;
	}
	void setStatus(DriverStatus Status) {
		status = Status;
	}
	void setCar(Car newCar) {
		currentCar = newCar;
	}
	CarType getCarType() {
		return currentCar.getCarType();
	}
	vector<Car> getCarsList() {
		return cars;
	}
	int getIndex() {
		return blockIndex;
	}
	void changeCar(string number) {
		for (int i = 0; i < cars.size(); i++) {
			if (number == cars[i].getNumber()) {
				currentCar = cars[i];
				return;
			}
		}
	}
	bool isFunctionAvailable(string functionName) {
		if (blockIndex % getFunctionLockIndex(functionName) == 0) return false;
		return true;
	}
	void blockFunction(string functionName) {
		if (blockIndex % getFunctionLockIndex(functionName) == 0) return;
		blockIndex *= getFunctionLockIndex(functionName);
	}
	void Ban() {
		blockIndex = 30030;
	}
	void authorizeCar(string number) {
		if (number == currentCar.getNumber()) {
			currentCar.authorize();
		}
		for (int i = 0; i < cars.size(); i++) {
			if (number == cars[i].getNumber()) {
				cars[i].authorize();
			}
		}
	}
	void parkRightInFrontOfTheEntrance() {
		if (currentCar.getCarType() != CarType::BUSINESS) return;
		cout << "Driver parked the car right in front of the entrance\n";
	}
	int offerWater() {
		return currentCar.takeFreeBottleOfWater();
	}
	void setPosition(Adress adress) {
		currentCar.setPoint(adress.getPoint());
	}
};

#endif