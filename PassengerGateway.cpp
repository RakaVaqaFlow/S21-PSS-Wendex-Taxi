#ifndef PASSENGER_GATEWAY
#define PASSENGER_GATEWAY
#include <iostream>
#include <string>
#include <vector>
#include <math.h>
#include <iomanip>
#include "DataBase.cpp"

class PassengerGateway {
private:
	static bool checkUser(Passenger* pass, string ID) {
		if (!(*pass).isLogin()) {
			cout << "Passenger " << (*pass).getName() << " " << (*pass).getSurname() << " is not logged in!\n";
			return false;
		}
		else if (!(*pass).isUserID(ID)) {
			cout << "Passenger " << (*pass).getName() << " " << (*pass).getSurname() << " has not authorized this device\n";
			return false;
		}
		return true;
	}
public:
	static Passenger* Register(string name, string surname, string password, string ID) {
		Passenger* pass = new Passenger(name, surname, password, ID);
		DataBase::addPassenger(pass);
		cout << "Passenger " << name << " " << surname << " is registered in the system\n";
		(*pass).Login(password, ID);
		return pass;
	}

	static Passenger* Register(string name, string surname, string password, string ID, subsPlan plan) {
		Passenger* pass = new Passenger(name, surname, password, ID, plan);
		DataBase::addPassenger(pass);
		cout << "Passenger " << name << " " << surname << " is registered in the system\n";
		(*pass).Login(password, ID);
		return pass;
	}

	static void Login(Passenger* pass, string password, string ID) {
		if (!pass->isFunctionAvailable("Login"))throw "user cannot use this function";
		bool f = (*pass).Login(password, ID);
		string verdikt = " is not logged in. Wrong password";
		if (f) verdikt = " successfully logged in";
		cout << "Passenger " << (*pass).getName() << " " << (*pass).getSurname() << verdikt << "\n";
	}

	static Order* checkOrder(Passenger* pass, Adress A, Adress B, CarType type, string ID) {
		if (!pass->isFunctionAvailable("checkOrder") || !checkUser(pass, ID)) throw "user cannot use this function";
		double speed = 1;
		double per = 1;
		double sale = 1;
		if (type == CarType::ECONOMY) {
			speed = 50;
			per = 4;
		}
		else if (type == CarType::COMFORT) {
			speed = 60;
			per = 5;
		}
		else if (type == CarType::COMFORT_PLUS) {
			speed = 65;
			per = 6;
		}
		else if (type == CarType::BUSINESS) {
			speed = 70;
			per = 8;
		}
		long long currentSec = time(NULL);
	    if ((*pass).getSubsPlan() == subsPlan::PREMIUM && type == CarType::COMFORT)sale = 0.85;
		else if ((*pass).getSubsPlan() == subsPlan::PREMIUM && (type == CarType::COMFORT_PLUS || type == CarType::BUSINESS))sale = 0.8;
		else if ((*pass).getSubsPlan() == subsPlan::SUPER)sale = 0;
		double hours = Point::calcLength(A.getPoint(), B.getPoint()) / (speed);
		double cost = Point::calcLength(A.getPoint(), B.getPoint()) * per * sale;
		Time startTime = Time::getCurrentMoment();
		Time endTime = Time(startTime.year, startTime.month, startTime.day+((startTime.hour + int(hours))>=24), (startTime.hour+ int(hours)+(startTime.minute+(int(hours*60))%60>=60))%24, (startTime.minute + (int(hours * 60)) % 60)%60);
		Order* order = new Order(startTime, endTime, A, B, cost, type, (*pass).getPayMethod(), int(hours*60*60));
		cout << "Ride from " << (*order).from.getStreet() << " " << (*order).from.getHouseNumber() << " to " << (*order).to.getStreet() << " " << (*order).to.getHouseNumber();
		cout << " will cost " << (*order).cost << " and take " << int(hours) << "h. " << int((hours*60))%60 << "m. for passenger " << pass->getName() << " " << pass->getSurname() << "\n";
		return order;
	}

	static void showOrderHistory(Passenger* pass, string ID) {
		if (!pass->isFunctionAvailable("showOrderHistory") || !checkUser(pass, ID)) throw "user cannot use this function";
		vector<Order> orderHistory = (*pass).getOrderHistory();
		if (orderHistory.size() == 0) {
			cout << "No orders\n";
			return;
		}
		if (orderHistory.size() == 1)cout << "Order:\n";
		else cout << "Orders:\n";
		for (int i = 0; i < orderHistory.size(); i++) {
			cout << " {\n";
			cout << "   start: ";
			if (orderHistory[i].startTime.hour >= 0 && orderHistory[i].startTime.hour <= 9)cout << "0";
			cout << orderHistory[i].startTime.hour << ":";
			if (orderHistory[i].startTime.minute >= 0 && orderHistory[i].startTime.minute <= 9)cout << "0";
			cout << orderHistory[i].startTime.minute << " " << orderHistory[i].from.toString() << "\n";
			cout << "   end: ";
			if (orderHistory[i].endTime.hour >= 0 && orderHistory[i].endTime.hour <= 9)cout << "0";
			cout << orderHistory[i].endTime.hour << ":";
			if (orderHistory[i].endTime.minute >= 0 && orderHistory[i].endTime.minute <= 9)cout << "0";
			cout << orderHistory[i].endTime.minute << " " << orderHistory[i].to.toString() << "\n";
			cout << "   cost: " << orderHistory[i].cost << "\n";
			cout << "   payment by ";
			if (orderHistory[i].paymentMeth == paymentMethods::CARD)cout << "card\n";
			else if (orderHistory[i].paymentMeth == paymentMethods::CASH) cout << "cash\n";
			else cout << " wendex plus points\n";
			cout << " }\n";
		}
	}

	static void orderRide(Order* order, Passenger* pass, string ID) {
		if (!pass->isFunctionAvailable("orderRide") || !checkUser(pass, ID)) throw "user cannot use this function";
		if ((*pass).getStatus() != PassengerStatus::IDLE) {
			cout << "Passenger " << (*pass).getName() << " " << (*pass).getSurname()<<" is on the way already.\n";
			return;
		}
		if (order->paymentMeth == paymentMethods::PLUS_POINTS && order->cost > pass->getPlusBalance()) {
			cout << "Passenger "<<pass->getName()<<" "<<pass->getSurname()<<" does not have enough points plus to pay\n";
			return;
		}
		(*pass).setMyPosition((*order).from);
		DataBase::addOrder(order, pass);
		(*pass).setStatus(PassengerStatus::WAITING);
		cout << (*pass).getName() << " " << (*pass).getSurname() << " ordered the ride\n";
	}
	
	static void orderRide(Order* order, Passenger* pass, paymentMethods payM, string ID) {
		(*order).paymentMeth = payM;
		orderRide(order, pass, ID);
	}

	static void askMyCoordinate(Passenger* pass, string ID) {
		if (!pass->isFunctionAvailable("askMyCoordinate") || !checkUser(pass, ID)) throw "user cannot use this function";
		Adress adress = pass->getMyPosition();
		cout << "Position of "<<pass->getName()<<" "<<pass->getSurname()<<adress.toString()<<"\n";
	}
};
#endif