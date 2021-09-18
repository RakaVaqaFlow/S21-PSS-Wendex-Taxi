#ifndef DATA_BASE
#define DATA_BASE
#include <iostream>
#include <string>
#include <vector>
#include <math.h>
#include <iomanip>
#include <fstream>
#include "Driver.cpp"
#include "Passenger.cpp"
#include "Admin.cpp"

class DataBase {
public:
	static inline int numOfPassengers;
	static inline int numOfDrivers;
	static inline int numOfAdresses;
	static inline int numOfAdmins;
	static inline vector<Admin*> admins;
	static inline vector<Passenger*> passengers;
	static inline vector<Driver*> drivers;
	static inline vector<Adress*> adresses;
	static inline vector<pair<Order*, Passenger*>> waitingList;

	static void addOrder(Order* order, Passenger* pass) {
		waitingList.push_back(make_pair(order, pass));
	}

	static void addPassenger(Passenger* pass) {
		passengers.push_back(pass);
		numOfPassengers++;
	}

	static void addDriver(Driver* driv) {
		drivers.push_back(driv);
		numOfDrivers++;
	}

	static void addAdmin(Admin* admin) {
		admins.push_back(admin);
		numOfAdmins++;
	}

	static void showInfo() {
		printPassengers();
		cout << "\n\n";
		printDrivers();
	}

	static void downloadData() {
		ifstream data;
		char c;
		string s;
		string name;
		string surname;
		string password;
		double rating;
		int tripsNum;
		double totalRating;
		vector<Order> ordersHistory;
		paymentMethods payMeth;
		subsPlan plan;
		Point position;
		string carType;
		Order order;
		string city1;
		string street1;
		int houseNumber1;
		string city2;
		string street2;
		int houseNumber2;
		int plusBalance = 0;
		int cntID;
		string ID;
		int blockIndex;
		vector<string> UsersID;
		//passengers
		data.open("Passengers.txt");
		data >> numOfPassengers;
		for (int i = 0; i < numOfPassengers; i++) {
			ordersHistory.clear();
			data >> c; //scan '[' in bd
			data >> s >> blockIndex;
			data >> name;
			data >> surname;
			data >> password;
			data >> cntID;
			UsersID.clear();
			for (int j = 0; j < cntID; j++) {
				data >> ID;
				UsersID.push_back(ID);
			}
			data >> rating;
			data >> tripsNum;
			data >> totalRating;
			
			data >> s;
			if (s == "Plus_Points")payMeth = paymentMethods::PLUS_POINTS;
			else if (s == "Card")payMeth = paymentMethods::CARD;
			else payMeth = paymentMethods::CASH;

			data >> s; // scan "Orders:" in bd;
			for (int j = 0; j < tripsNum; j++) {
				data >> s; //scan '{'
				data >> order.startTime.year >> order.startTime.month >> order.startTime.day;
				data >> order.startTime.hour >> c >> order.startTime.minute;
				
				data >> order.endTime.year >> order.endTime.month >> order.endTime.day;
				data >> order.endTime.hour >> c >> order.endTime.minute;

				data >> s >> order.duration;

				data >> city1 >> street1 >> houseNumber1;
				data >> city2 >> street2 >> houseNumber2;
				order.from = Adress(city1, street1, houseNumber1);
				order.to = Adress(city2, street2, houseNumber2);

				data >> order.cost;
				
				data >> s;
				if (s == "Plus_Points")order.paymentMeth = paymentMethods::PLUS_POINTS;
				else if (s == "Card")order.paymentMeth = paymentMethods::CARD;
				else order.paymentMeth = paymentMethods::CASH;

				data >> carType;
				if (carType == "Comfort+") order.type = CarType::COMFORT_PLUS;
				else if (carType == "Comfort") order.type = CarType::COMFORT;
				else if (carType == "Business") order.type = CarType::BUSINESS;
				else order.type = CarType::ECONOMY;

				ordersHistory.push_back(order);
				data >> s;//scan '}'
			}
			data >> s;
			if (s == "Premium") plan = subsPlan::PREMIUM;
			else if (s == "Super") plan = subsPlan::SUPER;
			else if (s == "Wendex_Plus") plan = subsPlan::WENDEX_PLUS;
			else plan = subsPlan::DEFAULT;
			data >> plusBalance;
			data >> city1 >> street1 >> houseNumber1;
			Passenger* pass = new Passenger(name, surname, password, rating, tripsNum, totalRating, payMeth, plan, ordersHistory, UsersID, Adress(city1, street1, houseNumber1), plusBalance, blockIndex);
			passengers.push_back(pass);
			data >> c; //scan ']' in bd
		}
		data.close();
		
		//drivers
		string model;
		CarType type;
		Point currentPoint;
		string colour;
		string number;
		vector<Car> cars;
		int carsNum;
		int isAuthorization;
		data.open("Drivers.txt");
		data >> numOfDrivers;
		for (int i = 0; i < numOfDrivers; i++) {
			ordersHistory.clear();
			data >> c; // scan '[' in bd
			data >> s >> blockIndex;
			data >> name;
			data >> surname;
			data >> password;
			data >> cntID;
			UsersID.clear();
			for (int j = 0; j < cntID; j++) {
				data >> ID;
				UsersID.push_back(ID);
			}
			data >> rating;
			data >> tripsNum;
			data >> totalRating;
			data >> s;
			for (int j = 0; j < tripsNum; j++) {
				data >> s;
				data >> order.startTime.year >> order.startTime.month >> order.startTime.day;
				data >> order.startTime.hour >> c >> order.startTime.minute;

				data >> order.endTime.year >> order.endTime.month >> order.endTime.day;
				data >> order.endTime.hour >> c >> order.endTime.minute;

				data >> s >> order.duration;

				data >> city1 >> street1 >> houseNumber1;
				data >> city2 >> street2 >> houseNumber2;
				order.from = Adress(city1, street1, houseNumber1);
				order.to = Adress(city2, street2, houseNumber2);

				data >> order.cost;

				data >> s;
				if (s == "Plus_Points")order.paymentMeth = paymentMethods::PLUS_POINTS;
				else if (s == "Card")order.paymentMeth = paymentMethods::CARD;
				else order.paymentMeth = paymentMethods::CASH;

				data >> carType;
				if (carType == "Comfort+") order.type = CarType::COMFORT_PLUS;
				else if (carType == "Comfort") order.type = CarType::COMFORT;
				else if (carType == "Business") order.type = CarType::BUSINESS;
				else order.type = CarType::ECONOMY;
				
				ordersHistory.push_back(order);
				data >> s;
			}
			data >> s >> carsNum;
			cars.clear();
			for (int j = 0; j < carsNum; j++) {
				data >> s;
				data >> model;
				data >> carType;
				if (carType == "Comfort+") type = CarType::COMFORT_PLUS;
				else if (carType == "Comfort") type = CarType::COMFORT;
				else if (carType == "Business") type = CarType::BUSINESS;
				else type = CarType::ECONOMY;
				data >> currentPoint.x_c >> currentPoint.y_c;
				data >> colour;
				data >> number;
				data >> s >> isAuthorization;
				data >> s;
				cars.push_back(Car(model, type, currentPoint, colour, number, isAuthorization));
			}
			Driver* driv = new Driver(name, surname, password, ordersHistory, UsersID, rating, tripsNum, totalRating, cars[0], cars, blockIndex);
			drivers.push_back(driv);
			data >> c;//scan ']' in bd
		}
		data.close();

		//admins
		data.open("Admin.txt");
		data >> numOfAdmins;
		for (int i = 0; i < numOfAdmins; i++) {
			data >> c; // scan '[' in bd
			data >> name;
			data >> surname;
			data >> password;
			data >> cntID;
			UsersID.clear();
			for (int j = 0; j < cntID; j++) {
				data >> ID;
				UsersID.push_back(ID);
			}
			Admin* admin = new Admin(name, surname, password, UsersID);
			admins.push_back(admin);
			data >> c;//scan ']' in bd
		}
		data.close();

		data.open("Adresses.txt");
		Adress* ad;
		data >> numOfAdresses;
		data >> c;
		for (int i = 0; i < numOfAdresses; i++) {
			data >> city1 >> street1 >> houseNumber1 >> position.x_c >> position.y_c;
			ad = new Adress(city1, street1, houseNumber1, position);
			adresses.push_back(ad);
		}
		data >> c;
		data.close();
	}
	
	static void printPassengers(){
		cout <<"Passengers: "<< numOfPassengers << "\n";
		Passenger pass;
		vector<Order> orders;
		for (int i = 0; i < numOfPassengers; i++) {
			pass = *passengers[i];
			cout << "[\n";
			cout << " " << "BlockIndex: " << pass.getIndex() << "\n";
			cout << " name:" << pass.getName() << "\n";
			cout << " surname:" << pass.getSurname() << "\n";
			cout << " password:" << pass.getPassword() << "\n";
			cout << " ID: " << pass.getUserIDs().size() << "\n";
			for (int j = 0; j < pass.getUserIDs().size(); j++) {
				cout << " " << " " << pass.getUserIDs()[j] << "\n";
			}
			cout << " rating:" << pass.getRating() << "\n";
			cout << " number of trips" << pass.getTripsNum() << "\n";
			cout << " payment method: ";
			if (pass.getPayMethod() == paymentMethods::CARD)cout << "Card\n";
			else if (pass.getPayMethod() == paymentMethods::CASH)cout << "Cash\n";
			else cout << "Plus_Points\n";

			cout << " " << "Orders:\n";
			orders = pass.getOrderHistory();
			for (int j = 0; j < pass.getTripsNum(); j++) {
				cout << " " << "{\n";

				cout << " " << " start: " << orders[j].startTime.toString() << "\n";
				cout << " " << " end: " << orders[j].endTime.toString() << "\n";

				cout << " " << " " << "duration: " << orders[j].duration << "\n";

				cout << " " << " from: " << orders[j].from.toString() << "\n";
				cout << " " << " to: " << orders[j].to.toString() << "\n";

				cout << " " << " cost: " << orders[j].cost << "\n";
				cout << " " << " payment method: ";
				if (orders[j].paymentMeth == paymentMethods::CARD)cout << "Card\n";
				else if (orders[j].paymentMeth == paymentMethods::CASH)cout << "Cash\n";
				else cout << "Plus_Points\n";
				cout << "  Type: ";
				if (orders[j].type == CarType::BUSINESS)cout << "Business\n";
				else if (orders[j].type == CarType::COMFORT)cout << "Comfort\n";
				else if (orders[j].type == CarType::COMFORT_PLUS)cout << "Comfort+\n";
				else cout << "Economy\n";

				cout << " " << "}\n";
			}
			cout << " subscription plan: ";
			if (pass.getSubsPlan() == subsPlan::WENDEX_PLUS)cout << "Wendex_Plus\n";
			else if (pass.getSubsPlan() == subsPlan::PREMIUM)cout << "Premium\n";
			else if (pass.getSubsPlan() == subsPlan::SUPER)cout << "Super\n";
			else cout << "Default\n";
			cout << " plus point balance:" << pass.getPlusBalance() << "\n";
			cout << " pinned adress:" << pass.getAdress().toString() << "\n";
			cout << "]\n";
		}
	}
	
	static void printDrivers(){
		Driver driv;
		vector<Order> orders;
		cout << "Drivers: "<<numOfDrivers << "\n";
		for (int i = 0; i < numOfDrivers; i++) {
			driv = *drivers[i];
			cout << "[\n";
			cout << " "<<"BlockIndex: " << driv.getIndex() << "\n";
			cout << " name: "<<driv.getName() << "\n";
			cout << " surname: "<<driv.getSurname() << "\n";
			cout << " password: "<<driv.getPassword() << "\n";
			cout << " IDs: "<<driv.getUserIDs().size() << "\n";
			for (int j = 0; j < driv.getUserIDs().size(); j++) {
				cout << " " << " " << driv.getUserIDs()[j] << "\n";
			}
			cout << " rating: "<<driv.getRating() << "\n";
			cout << " number of trips: "<<driv.getTripsNum() << "\n";

			cout << " " << "Orders:\n";
			orders = driv.getOrderHistory();
			for (int j = 0; j < driv.getTripsNum(); j++) {
				cout << " " << "{\n";

				cout << " " << " start: " << orders[j].startTime.toString() << "\n";
				cout << " " << " end: " << orders[j].endTime.toString() << "\n";

				cout << " " << " " << "duration: " << orders[j].duration << "\n";

				cout << " " << " from: " << orders[j].from.toString() << "\n";
				cout << " " << " to: " << orders[j].to.toString() << "\n";

				cout << " " << " cost: " << orders[j].cost << "\n";
				cout << " " << " payment method: ";
				if (orders[j].paymentMeth == paymentMethods::CARD)cout << "Card\n";
				else if (orders[j].paymentMeth == paymentMethods::CASH)cout << "Cash\n";
				else cout << "Plus_Points\n";
				cout << "  Type: ";
				if (orders[j].type == CarType::BUSINESS)cout << "Business\n";
				else if (orders[j].type == CarType::COMFORT)cout << "Comfort\n";
				else if (orders[j].type == CarType::COMFORT_PLUS)cout << "Comfort+\n";
				else cout << "Economy\n";

				cout << " " << "}\n";
			}
			cout << " " << "Cars: " << driv.getCarsList().size() << "\n";
			for (int j = 0; j < driv.getCarsList().size(); j++) {
				cout << " " << "{\n";
				Car car = driv.getCarsList()[j];
				cout << " " << " model: " << car.getModel() << "\n";
				cout << " " << " type: ";
				if (car.getCarType() == CarType::BUSINESS)cout << "Business\n";
				else if (car.getCarType() == CarType::COMFORT)cout << "Comfort\n";
				else if (car.getCarType() == CarType::COMFORT_PLUS)cout << "Comfort+\n";
				else cout << "Economy\n";
				cout << " " << " colour:"  << car.getColour() << "\n";
				cout << " " << " number: " << car.getNumber() << "\n";
				cout << " " << " " << "authorization: ";
				if (car.getStatus())cout << "1\n";
				else cout << "0\n";
				cout << " " << "}\n";
			}
			cout << "]\n";
		}
	}
	
	static void uploadData() {
		ofstream data;
		
		data.open("Passengers.txt");
		data << numOfPassengers << "\n";
		Passenger pass;
		vector<Order> orders;
		for (int i = 0; i < numOfPassengers; i++) {
			pass = *passengers[i];
			data << "[\n";
			data << "BlockIndex: " << pass.getIndex() << "\n";
			data << pass.getName() << "\n";
			data << pass.getSurname() << "\n";
			data << pass.getPassword() << "\n";
			data << pass.getUserIDs().size() << "\n";
			for (int j = 0; j < pass.getUserIDs().size(); j++) {
				data << pass.getUserIDs()[j]<<"\n";
			}
			data << pass.getRating() << "\n";
			data << pass.getTripsNum() << "\n";
			data << pass.getTotalRating() << "\n";

			if (pass.getPayMethod() == paymentMethods::CARD)data << "Card\n";
			else if (pass.getPayMethod() == paymentMethods::CASH)data << "Cash\n";
			else data << "Plus_Points\n";

			data << "Orders:\n";
			orders = pass.getOrderHistory();
			for (int j = 0; j < pass.getTripsNum(); j++) {
				data << "{\n";

				data << orders[j].startTime.toString()<<"\n";
				data << orders[j].endTime.toString() << "\n";

				data << "duration: " << orders[j].duration << "\n";

				data << orders[j].from.toString() << "\n";
				data << orders[j].to.toString() << "\n";
				
				data << orders[j].cost << "\n";

				if (orders[j].paymentMeth == paymentMethods::CARD)data<< "Card\n";
				else if (orders[j].paymentMeth == paymentMethods::CASH)data << "Cash\n";
				else data << "Plus_Points\n";

				if (orders[j].type == CarType::BUSINESS)data << "Business\n";
				else if (orders[j].type == CarType::COMFORT)data << "Comfort\n";
				else if (orders[j].type == CarType::COMFORT_PLUS)data << "Comfort+\n";
				else data << "Economy\n";

				data << "}\n";
			}
			if (pass.getSubsPlan() == subsPlan::WENDEX_PLUS)data << "Wendex_Plus\n";
			else if (pass.getSubsPlan() == subsPlan::PREMIUM)data << "Premium\n";
			else if (pass.getSubsPlan() == subsPlan::SUPER)data << "Super\n";
			else data << "Default\n";
			data << pass.getPlusBalance() << "\n";
			data << pass.getAdress().toString() << "\n";
			data << "]\n";
		}
		data.close();
		
		data.open("Drivers.txt");
		Driver driv;
		data << numOfDrivers << "\n";
		for (int i = 0; i < numOfDrivers; i++) {
			driv = *drivers[i];
			data << "[\n";
			data << "BlockIndex: "<<driv.getIndex() << "\n";
			data << driv.getName() << "\n";
			data << driv.getSurname() << "\n";
			data << driv.getPassword() << "\n";
			data << driv.getUserIDs().size() << "\n";
			for (int j = 0; j < driv.getUserIDs().size(); j++) {
				data << driv.getUserIDs()[j]<<"\n";
			}
			data << driv.getRating() << "\n";
			data << driv.getTripsNum() << "\n";
			data << driv.getTotalRating() << "\n";

			data << "Orders:\n";
			orders = driv.getOrderHistory();
			for (int j = 0; j < driv.getTripsNum(); j++) {
				data << "{\n";
				data << orders[j].startTime.toString() << "\n";
				data << orders[j].endTime.toString() << "\n";

				data << "duration: " << orders[j].duration << "\n";

				data << orders[j].from.toString() << "\n";
				data << orders[j].to.toString() << "\n";

				data << orders[j].cost << "\n";

				if (orders[j].paymentMeth == paymentMethods::CARD)data << "Card\n";
				else if (orders[j].paymentMeth == paymentMethods::CASH)data << "Cash\n";
				else data << "Plus_Points\n";

				if (orders[j].type == CarType::BUSINESS)data << "Business\n";
				else if (orders[j].type == CarType::COMFORT)data << "Comfort\n";
				else if (orders[j].type == CarType::COMFORT_PLUS)data << "Comfort+\n";
				else data << "Economy\n";
				data << "}\n";
			}
			data << "Cars: " << driv.getCarsList().size() << "\n";
			for (int j = 0; j < driv.getCarsList().size(); j++) {
				data << "{\n";
				Car car = driv.getCarsList()[j];
				data << car.getModel() << "\n";
				if (car.getCarType() == CarType::BUSINESS)data << "Business\n";
				else if (car.getCarType() == CarType::COMFORT)data << "Comfort\n";
				else if (car.getCarType() == CarType::COMFORT_PLUS)data << "Comfort+\n";
				else data << "Economy\n";
				data << car.getPoint().x_c << " " << car.getPoint().y_c << "\n";
				data << car.getColour() << "\n";
				data << car.getNumber() << "\n";
				data << "authorization: ";
				if (car.getStatus())data << "1\n";
				else data << "0\n";
				data << "}\n";
			}
			data << "]\n";
		}
		data.close();

		data.open("Admin.txt");
		Admin admin;
		data << numOfAdmins << "\n";
		for (int i = 0; i < numOfAdmins; i++) {
			admin = *admins[i];
			data << "[\n"; // scan '[' in bd
			data << admin.getName()<<"\n";
			data << admin.getSurname()<<"\n";
			data << admin.getPassword() << "\n";
			data << admin.getUserIDs().size()<<"\n";
			for (int j = 0; j < admin.getUserIDs().size(); j++) {
				data << admin.getUserIDs()[j]<<"\n";
			}
			data << "]\n";//scan ']' in bd
		}
		data.close();
	}
};

#endif