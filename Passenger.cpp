#ifndef PASSENGER
#define PASSENGER

#include <stdio.h>
#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
#include <math.h>
#include <iomanip>
#include "User.cpp"
using namespace std;

//WENDEX_PLUS - Sale 10%
//Premium - Sale 15% for Comfort, 20% for Comfort+ and Business
//Super - for special passenger, Sale 100%
enum class subsPlan {
	DEFAULT, WENDEX_PLUS, PREMIUM, SUPER
};

enum class PassengerStatus {
	WAITING, ON_WAY, IDLE
};
class Passenger : public User {
private:
	int getFunctionLockIndex(string functionName) {
		if (functionName == "Login") return 2;
		else if (functionName == "checkOrder") return 3;
		else if (functionName == "showOrderHistory") return 5;
		else if (functionName == "orderRide") return 7;
		else if (functionName == "askMyCoordinate") return 11;
		else return 1;
	}
	paymentMethods payMethod;
	subsPlan plan;
	Adress pinnedAdress;
	Adress currentPosition;
	double plusBalance;
	PassengerStatus status;
	int blockIndex = 1;
public:
	Passenger() {
		name = "Name";
		surname = "Surname";
		password = "";
		rating = 0;
		tripsNum = 0;
		totalRating = 0;
		payMethod = paymentMethods::CASH;
		plan = subsPlan::DEFAULT;
		pinnedAdress = Adress();
		currentPosition = Adress();
		plusBalance = 0;
		status = PassengerStatus::IDLE;
	}
	Passenger(string Name, string Surname, string Password, string ID) :
		User(Name, Surname, Password, ID), status(PassengerStatus::IDLE){}
	/*Passenger(string Name, string Surname, string Password, string ID) : 
		User(name, surname, password, ID){
		rating = 0;
		tripsNum = 0;
		totalRating = 0;
		payMethod = paymentMethods::CASH;
		plan = subsPlan::DEFAULT;
		pinnedAdress = Adress();
		currentPosition = Adress();
		plusBalance = 0;
		status = PassengerStatus::IDLE;
	}*/

	Passenger(string Name, string Surname, string Password, string ID, subsPlan Plan) : 
		Passenger(Name, Surname, Password, ID) {	
		plan = Plan;
		status = PassengerStatus::IDLE;
	}

	Passenger(string Name, string Surname, string Password, 
		double Rating, int TripsNum, double TotalRating,
		paymentMethods payMeth, subsPlan Plan, vector<Order> OrderHistory, vector<string>UsersID,
		Adress pinAdress, double PlusBalance, int BlockIndex) : 
		User(Name, Surname, Password, OrderHistory, UsersID, Rating, TripsNum, TotalRating), 
		payMethod(payMeth), plan(Plan), pinnedAdress(pinAdress), plusBalance(PlusBalance), blockIndex(BlockIndex){
		status = PassengerStatus::IDLE;
	}

	double getPlusBalance() {
		return plusBalance;
	}
	Adress getMyPosition() {
		return currentPosition;
	}
	paymentMethods getPayMethod() {
		return payMethod;
	}
	Adress getAdress() {
		return pinnedAdress;
	}
	PassengerStatus getStatus() {
		return status;
	}
	subsPlan getSubsPlan() {
		return plan;
	}
	int getIndex() {
		return blockIndex;
	}
	void setAdress(Adress adress) {
		pinnedAdress = adress;
	}
	void setAdress(string city, string street, int houseNumber, double X, double Y) {
		pinnedAdress = Adress(city, street, houseNumber, Point(X, Y));
	}
	void setPayMethod(paymentMethods payM) {
		payMethod = payM;
	}

	void setPlan(subsPlan subP) {
		plan = subP;
	}

	void setMyPosition(Adress p) {
		currentPosition = p;
	}
	void setStatus(PassengerStatus Status) {
		status = Status;
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
		blockIndex = 2310;
	}

	void accruePoints(double point) {
		plusBalance += point;
	}

	void withdrawPoints(double cost) {
		plusBalance -= cost;
	}
};

#endif 