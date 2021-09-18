#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include <vector>
#include <math.h>
#include <iomanip>
#include "DriverGateway.cpp"
#include "PassengerGateway.cpp"
#include "AdminGateway.cpp"
using namespace std;


int main() {

	//download data from txt
	DataBase::downloadData();

	Passenger* Ivan = DataBase::passengers[0];
	Driver* Sergey = DataBase::drivers[0];
	Driver* Vasya = DataBase::drivers[1];
	Admin* Vladimir = DataBase::admins[0];
	Adress* a1 = DataBase::adresses[0];
	Adress* a2 = DataBase::adresses[5];
	Adress* a3 = DataBase::adresses[2];
	Adress* a4 = DataBase::adresses[9];
	Order* order1;
	Order* order2;
	
	//login
	PassengerGateway::Login(Ivan, "qwerty", "564546");
	DriverGateway::Login(Sergey, "pakmane", "12117");
	DriverGateway::Login(Vasya, "anychikibriki", "333");
	AdminGateway::Login(Vladimir, "edinayrussia", "11111");
	

	//register
	Passenger* Anton = PassengerGateway::Register("Anton", "Smirnov", "skibidi", "1945");
	Driver* Eric = DriverGateway::Register("Eric", "Kituashvili", "smotra", Car("BMW", CarType::BUSINESS, "black", "B333XB98"), "89621954");
	Admin* Arkady = AdminGateway::Register("Arkady", "Tsaregradsev", "motul", "999");

	//add new device
	PassengerGateway::Login(Anton, "skibidi", "8888");
	
	//check the time and price of the ride
	order1 = PassengerGateway::checkOrder(Anton, *a1, *a2, CarType::BUSINESS, "8888");
	order2 = PassengerGateway::checkOrder(Ivan, *a4, *a1, CarType::COMFORT_PLUS, "564546");

	//order ride
	PassengerGateway::orderRide(order1, Anton, "8888");
	PassengerGateway::orderRide(order2, Ivan, paymentMethods::PLUS_POINTS, "564546");

	//check orders
	vector<pair<Order*, Passenger*>> list1= DriverGateway::checkOrders(Eric, "89621954");
	
	//accept order
	order1 = list1[0].first;
	Passenger* p = list1[0].second;
	DriverGateway::acceptOrder(Eric, order1, p, "89621954"); // before authorization
	AdminGateway::authorizeCar(Arkady, Eric, "B333XB98", "999");
	DriverGateway::acceptOrder(Eric, order1, p, "89621954"); // after

	//ask my coordinate
	PassengerGateway::askMyCoordinate(Anton, "8888");
	
	//order ride
	order2 = PassengerGateway::checkOrder(Ivan, *a4, *a1, CarType::COMFORT_PLUS, "564546");
	PassengerGateway::orderRide(order2, Ivan, "564546");

	//ckeck orders
	list1 = DriverGateway::checkOrders(Sergey, "12117");

	//accept order
	order1 = list1[0].first;
	p = list1[0].second;
	DriverGateway::acceptOrder(Sergey, order1, p, "12117");
	
	//order history
	PassengerGateway::showOrderHistory(Anton, "8888");
	DriverGateway::showOrderHistory(Eric, "89621954");

	//suspicious device
	AdminGateway::blockFunction(Vladimir, Anton, "checkOrder", "7777"); 

	//block fucntion
	AdminGateway::blockFunction(Vladimir, Eric, "showOrderHistory", "11111");
	AdminGateway::blockFunction(Vladimir, Anton, "checkOrder", "11111");
	
	try {
		PassengerGateway::checkOrder(Anton, *a1, *a3, CarType::ECONOMY, "8888");
	}
	catch(const char* error){
		cout << error<<"\n";
	}
	try {
		DriverGateway::showOrderHistory(Eric, "89621954");
	}
	catch(const char* error){
		cout << error<<"\n";
	}
	//show information 
	AdminGateway::showInformration(Vladimir, "11111");
	
	//upload data in txt
	DataBase::uploadData();
}
