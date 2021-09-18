#ifndef USER
#define USER

#include <string>
#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <vector>
#include <math.h>
#include <iomanip>
#include "Order.cpp"
#include "PaymentMethods.cpp" 

using namespace std;

class User {
protected:
	string name;
	string surname;
	string password;
	double rating = 0;
	int tripsNum = 0;
	double totalRating = 0;
	vector<Order> orderHistory;
	vector<string>userIDs;
	bool login = false;
public:

	User() {
		name = "Name";
		surname = "Surname";
		password = "";
	}
	User(string Name, string Surname, string Password, string ID) :
		name(Name), surname(Surname), password(Password) {
		userIDs.push_back(ID);
	}

	User(string Name, string Surname, string Password, vector<string> UserID) :
		name(Name), surname(Surname), password(Password), userIDs(UserID) {}

	User(string Name, string Surname, string Password, vector<Order> OrderHistory,
		vector<string>UsersID, double Rating, int TripsNum, double TotalRating) :
		name(Name), surname(Surname), password(Password), orderHistory(OrderHistory),
		userIDs(UsersID), rating(Rating), tripsNum(TripsNum), totalRating(TotalRating) {}

	string getName() {
		return name;
	}
	string getSurname() {
		return surname;
	}
	string getPassword() {
		return password;
	}
	double getRating() {
		return rating;
	}
	int getTripsNum() {
		return tripsNum;
	}
	double getTotalRating() {
		return totalRating;
	}
	vector<Order> getOrderHistory() {
		return orderHistory;
	}
	vector<string> getUserIDs() {
		return userIDs;
	}
	void setPassword(string oldPassword, string Password) {
		if (oldPassword != password)return;
		password = Password;
	}
	void addOrder(Order order) {
		orderHistory.push_back(order);
	}
	bool addRating(double rate) {
		if (rate > 5.0 || rate < 0) {
			return false;
		}
		tripsNum++;
		totalRating += rate;
		rating = totalRating / double(tripsNum);
		return true;
	}
	bool isLogin() {
		return login;
	}
	bool regNewDevice(string Password, string ID) {
		if (!login || Password != password) return false;
		bool f = true;
		for (int i = 0; i < userIDs.size(); i++) {
			if (ID == userIDs[i]) f = false;
		}
		if(f)userIDs.push_back(ID);
		return true;
	}
	bool Login(string Password, string ID) {
		if (Password != password)return false;
		userIDs.push_back(ID);
		login = true;
		return true;
	}
	bool isUserID(string ID) {
		for (int i = 0; i < userIDs.size(); i++) {
			if (ID == userIDs[i]) return true;
		}
		return false;
	}
};

#endif 