#ifndef ADMIN
#define ADMIN
#include <string>
#include <iostream>
#include "User.cpp"
#include "Passenger.cpp"
#include "Driver.cpp"

class Admin : public User {
public:
	Admin() = default;
	Admin(string Name, string Surname, string Password, string ID) :
	User(Name, Surname, Password, ID){}
	Admin(string Name, string Surname, string Password, vector<string> UserID) :
		User(Name, Surname, Password, UserID) {}
	void blockPassengerFunction(Passenger* pass, string functionName) {
		pass->blockFunction(functionName);
	}
	void blockDriverFunction(Driver* driv, string functionName) {
		driv->blockFunction(functionName);
	}
	void banPassenger(Passenger* pass) {
		pass->Ban();
	}
	void banDriver(Driver* driv) {
		driv->Ban();
	}
};
#endif 
