#ifndef ADMIN_GATEWAY
#define ADMIN_GATEWAY

#include <iostream>
#include <string>
#include <vector>
#include <math.h>
#include <algorithm>
#include <iomanip>
#include "DataBase.cpp"
using namespace std;

class AdminGateway {
private:
	static bool checkUser(Admin* admin, string ID) {
		if (!(*admin).isLogin()) {
			cout << "Administrator " << (*admin).getName() << " " << (*admin).getSurname() << " is not logged in!\n";
			return false;
		}
		else if (!(*admin).isUserID(ID)) {
			cout << "Administrator "<< (*admin).getName() << " " << (*admin).getSurname() <<" has not authorized this device\n";
			return false;
		}
		return true;
	}
public:
	static Admin* Register(string name, string surname, string password, string ID) {
		Admin* admin = new Admin(name, surname, password, ID);
		DataBase::addAdmin(admin);
		cout << "Administrator " << name << " " << surname << " is registered in the system\n";
		(*admin).Login(password, ID);
		return admin;
	}

	static void Login(Admin* admin, string password, string ID) {
		bool f = (*admin).Login(password, ID);
		string verdikt = " is not logged in. Wrong password";
		if (f) verdikt = " successfully logged in";
		cout << "Administrator " << (*admin).getName() << " " << (*admin).getSurname() << verdikt << "\n";
	}

	static void blockFunction(Admin* admin, Passenger* pass, string functionName, string ID) {
		if(!checkUser(admin, ID)) return;
		admin->blockPassengerFunction(pass, functionName);
	}

	static void blockFunction(Admin* admin, Driver* driv, string functionName, string ID) {
		if (!checkUser(admin, ID)) return;
		admin->blockDriverFunction(driv, functionName);
	}
	static void showInformration(Admin* admin, string ID) {
		if (!checkUser(admin, ID)) return;
		DataBase::showInfo();
	}
	static void authorizeCar(Admin* admin, Driver* driv, string number, string ID) {
		if (!checkUser(admin, ID)) return;
		driv->authorizeCar(number);
	}
};

#endif