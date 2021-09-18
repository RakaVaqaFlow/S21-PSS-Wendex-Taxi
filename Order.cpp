#ifndef ORDER
#define ORDER
#include <string>
#include <iostream>
#include "CarType.cpp"
#include "Adress.cpp"
#include "PaymentMethods.cpp"
#include "Time.cpp"

using namespace std;
class Order {
public:
	Time startTime;
	Time endTime;
	Adress from;
	Adress to;
	paymentMethods paymentMeth;
	CarType type;
	double cost;
	int duration;
	Order() : startTime(Time(0, 0)), endTime(Time(0, 0)) {
		cost = 0;
		duration = 0;
		type = CarType::ECONOMY;
		paymentMeth = paymentMethods::CASH;
		from = Adress();
		to = Adress();
	}
	Order(Time StartTime, Time EndTime, Adress From, Adress To, double Cost, CarType Type)
		: startTime(StartTime), endTime(EndTime), from(From), to(To), cost(Cost), type(Type) {
		paymentMeth = paymentMethods::CASH;
		duration = Time::diffInSec(EndTime, StartTime);
	}
	Order(Time StartTime, Time EndTime, Adress From, Adress To, double Cost, CarType Type, paymentMethods payMeth)
		: Order(StartTime, EndTime, From, To, Cost, Type) {
		paymentMeth = payMeth;
		duration = Time::diffInSec(endTime, startTime);
	}
	Order(Time StartTime, Time EndTime, Adress From, Adress To, double Cost, CarType Type, paymentMethods payMeth, int Duration):
		Order(StartTime, EndTime, From, To, Cost, Type){
		paymentMeth = payMeth;
		duration = Duration;
	}
	

	bool operator>(const Order& B) {
		return (cost > B.cost || (cost == B.cost && duration < B.duration));
	};

	bool operator< (const Order& B) {
		return (cost < B.cost || (cost == B.cost && duration > B.duration));
	};
	bool operator>= (const Order& B) {
		return (cost >= B.cost || (cost == B.cost && duration <= B.duration));
	};

	bool operator<= (const Order& B) {
		return (cost <= B.cost || (cost == B.cost && duration >= B.duration));
	};

};




#endif