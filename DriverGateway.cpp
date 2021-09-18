#ifndef DRIVER_GATEWAY
#define DRIVER_GATEWAY

#include <iostream>
#include <string>
#include <vector>
#include <math.h>
#include <algorithm>
#include <iomanip>
#include "DataBase.cpp"

using namespace std;

class DriverGateway {
private:
	static bool checkUser(Driver* driv, string ID) {
		if (!(*driv).isLogin()) {
			cout << "Driver " << (*driv).getName() << " " << (*driv).getSurname() << " is not logged in!\n";
			return false;
		}
		else if (!(*driv).isUserID(ID)) {
			cout << "Driver " << (*driv).getName() << " " << (*driv).getSurname() << " has not authorized this device\n";
			return false;
		}
		return true;
	}
	static bool cmp(const pair<Order*, Passenger*>& A, const pair<Order*, Passenger*>& B) {
		return *(A.first) > *(B.first);
	}
public:
	static Driver* Register(string name, string surname, string password, Car car, string ID) {
		Driver* driv = new Driver(name, surname, password,  car, ID, 1);
		DataBase::addDriver(driv);
		cout << "Driver " << name << " " << surname << " is registered in the system\n";
		(*driv).Login(password, ID);
		return driv;
	}
	
	static void Login(Driver* driv, string password, string ID) {
		if (!driv->isFunctionAvailable("Login")) throw "user cannot use this function";
		bool f = (*driv).Login(password, ID);
		string verdikt = " is not logged in. Wrong password";
		if (f) verdikt = " successfully logged in";
		cout << "Driver " << (*driv).getName() << " " << (*driv).getSurname() << verdikt << "\n";
	}

	static void showOrderHistory(Driver* driv, string ID) {
		if (!driv->isFunctionAvailable("showOrderHistory") || !checkUser(driv, ID)) throw "user cannot use this function";
		vector<Order> orderHistory = (*driv).getOrderHistory();
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
			cout<< orderHistory[i].startTime.hour << ":";
			if (orderHistory[i].startTime.minute >= 0 && orderHistory[i].startTime.minute <= 9)cout << "0";
			cout<<orderHistory[i].startTime.minute << " " << orderHistory[i].from.toString() << "\n";
			cout << "   end: ";
			if (orderHistory[i].endTime.hour >= 0 && orderHistory[i].endTime.hour <= 9)cout << "0";
			cout << orderHistory[i].endTime.hour << ":";
			if (orderHistory[i].endTime.minute >= 0 && orderHistory[i].endTime.minute <= 9)cout << "0";
			cout << orderHistory[i].endTime.minute << " " << orderHistory[i].to.toString() << "\n";
			cout << "   cost: " << orderHistory[i].cost<<"\n";
			cout << "   payment by ";
			if (orderHistory[i].paymentMeth == paymentMethods::CARD)cout << "card\n";
			else if (orderHistory[i].paymentMeth == paymentMethods::CASH) cout << "cash\n";
			else cout << " wendex plus points\n";
			cout << " }\n";
		}
	}
	
	static void updateStatus(Driver* driv, DriverStatus status, string ID) {
		if (!driv->isFunctionAvailable("updateStatus") || !checkUser(driv, ID)) throw "user cannot use this function";
		(*driv).setStatus(status);
	}

	static vector<pair<Order*, Passenger*>> checkOrders(Driver* driv, string ID) {
		if (!driv->isFunctionAvailable("checkOrders") || !checkUser(driv, ID)) throw "user cannot use this function";
		vector<pair<Order*, Passenger*>> availableOrders;
		for (int i = 0; i < DataBase::waitingList.size(); i++) {
			Order* order = DataBase::waitingList[i].first;
			if ((*order).type == (*driv).getCarType()) 
				availableOrders.push_back(make_pair(order, DataBase::waitingList[i].second));
		}
		sort(availableOrders.begin(), availableOrders.end(), cmp);
		return availableOrders;
	}

	static void acceptOrder(Driver* driv, Order* order, Passenger* pass, string ID) {
		if (!driv->isFunctionAvailable("acceptOrder") || !checkUser(driv, ID)) throw "user cannot use this function";
		if (!driv->getCar().getStatus()) {
			cout << "Administrator did not authorize the car\n";
			return;
		}
		if (!(driv->getStatus() == DriverStatus::FREE || driv->getStatus() == DriverStatus::NOT_WORKING)) {
			cout << "Driver must complete the previous order\n";
			return;
		}
		driv->setStatus(DriverStatus::ON_WAY_TO_CLIENT);
		cout << "Driver on the way to the client\n";
		Time updateStart = Time::getCurrentMoment();
		double hours = double(order->duration)/3600;
		Time updateEnd = Time(updateStart.year, updateStart.month, updateStart.day + ((updateStart.hour + int(hours)) >= 24), (updateStart.hour + int(hours) + (updateStart.minute + (int(hours * 60)) % 60 >= 60)) % 24, (updateStart.minute + (int(hours * 60)) % 60) % 60);
		order->startTime = updateStart;
		if (order->type == CarType::BUSINESS) {
			driv->parkRightInFrontOfTheEntrance();
		}
		driv->setStatus(DriverStatus::ON_WAY_WITH_CLIENT);

		order->endTime = updateEnd;
		driv->setStatus(DriverStatus::FREE);
		if (order->type == CarType::COMFORT || order->type == CarType::COMFORT_PLUS) {
			int bottle = driv->offerWater();
			cout << "Passenger took " << bottle << " bottles of water\n";
		}
		if (order->paymentMeth == paymentMethods::PLUS_POINTS) {
			pass->withdrawPoints(order->cost);
		}
		pass->setMyPosition(order->to);
		if (pass->getSubsPlan() == subsPlan::WENDEX_PLUS) {
			pass->accruePoints(order->cost * 0.15);
		}
		cout << "Driver arrived at the destination. Order completed\n";
		pass->setStatus(PassengerStatus::IDLE);
		driv->setStatus(DriverStatus::FREE);
		driv->setPosition(order->to);
		driv->addOrder(*order);
		driv->addRating(rand() % 5);
		pass->addOrder(*order);
		pass->addRating(rand() % 5);

	}
};


#endif