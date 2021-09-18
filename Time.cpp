#ifndef TIME
#define TIME
#include <iostream>
#include <string>
#include <chrono>
#include <ctime>

using namespace std;

class Time {
public:
	int year, day, hour, minute;
	string month;
	Time(int Year, string Month, int Day, int Hour, int Minute) :
		year(Year), month(Month), day(Day), hour(Hour), minute(Minute) {}

	Time(int Hour, int Minute) :
		year(0), month(""), day(0), hour(Hour), minute(Minute) {}

	string toString() {
		string s = to_string(year) + " " + month + " " + to_string(day) + " ";
		if (hour >= 0 && hour <= 9)s += "0";
		s += to_string(hour) + ":";
		if (minute >= 0 && minute <= 9)s += "0";
		s += to_string(minute);
		return s;
	}

	static Time getMomentInNormalFormat(time_t tim) {

		time_t t = tim;
		tm* timeinfo = new tm;
		localtime_s(timeinfo, &t);
		int currentYear = timeinfo->tm_year + 1900;
		int currentM = timeinfo->tm_mon;
		string currentMonth = intToMonth(currentM);
		int currentDay = timeinfo->tm_mday;
		int currentHour = timeinfo->tm_hour;
		int currentMinute = timeinfo->tm_min;
		return Time(currentYear, currentMonth, currentDay, currentHour, currentMinute);
	}

	static Time getCurrentMoment() {
		time_t t = time(0);  
		return getMomentInNormalFormat(t);
	}

	static string intToMonth(int num) {
		if (num == 0) return  "January";
		else if (num == 1) return  "February";
		else if (num == 2) return  "March";
		else if (num == 3) return  "April";
		else if (num == 4) return  "May";
		else if (num == 5) return  "June";
		else if (num == 6) return  "July";
		else if (num == 7) return  "August";
		else if (num == 8) return  "September";
		else if (num == 9) return  "October";
		else if (num == 10) return  "November";
		else return "December";
	}

	static int monthToInt(string month) {
		if (month == "January") return 0;
		else if (month == "February") return 1;
		else if (month == "March") return  2;
		else if (month == "April") return 3;
		else if (month == "May") return 4;
		else if (month == "June") return 5;
		else if (month == "July") return 6;
		else if (month == "August") return 7;
		else if (month == "September") return 8;
		else if (month == "October") return 9;
		else if (month == "November") return 10;
		else return 11;
	}

	static int howManyDaysInMonth(string month) {
		if (month == "January") return 31;
		else if (month == "February") return 28;
		else if (month == "March") return  31;
		else if (month == "April") return 30;
		else if (month == "May") return 31;
		else if (month == "June") return 30;
		else if (month == "July") return 31;
		else if (month == "August") return 31;
		else if (month == "September") return 30;
		else if (month == "October") return 31;
		else if (month == "November") return 30;
		else return 31;
	}

	static int howManyDaysInMonth(string month, int year) {
		if (month == "February" && year % 4 == 0) return 29;
		return howManyDaysInMonth(month);
	}

	static int diffInSec(Time A, Time B) {
		time_t start, end;
		tm* timeinfoA = new tm;
		timeinfoA->tm_year = A.year - 1900;
		timeinfoA->tm_mon = Time::monthToInt(A.month);
		timeinfoA->tm_mday = A.day;
		timeinfoA->tm_hour = A.hour;
		timeinfoA->tm_min = A.minute;
		tm* timeinfoB = new tm;
		timeinfoB->tm_year = B.year - 1900;
		timeinfoB->tm_mon = Time::monthToInt(B.month);
		timeinfoB->tm_mday = B.day;
		timeinfoB->tm_hour = B.hour;
		timeinfoB->tm_min = B.minute;
		int dif;
		start = mktime(timeinfoA);
		end = mktime(timeinfoB);
		dif = difftime(end, start);
		return dif;
	}

	bool operator>(const Time& B) {
		return (year > B.year || (year == B.year && Time::monthToInt(month) > Time::monthToInt(B.month))
			|| (year == B.year && Time::monthToInt(month) == Time::monthToInt(B.month) && day > B.day)
			|| (year == B.year && Time::monthToInt(month) == Time::monthToInt(B.month) && day == B.day && hour > B.hour)
			|| (year == B.year && Time::monthToInt(month) == Time::monthToInt(B.month) && day == B.day && hour == B.hour && minute > B.minute));
	};

	bool operator<(const Time& B) {
		return (year < B.year || (year == B.year && Time::monthToInt(month) < Time::monthToInt(B.month))
			|| (year == B.year && Time::monthToInt(month) == Time::monthToInt(B.month) && day < B.day)
			|| (year == B.year && Time::monthToInt(month) == Time::monthToInt(B.month) && day == B.day && hour < B.hour)
			|| (year == B.year && Time::monthToInt(month) == Time::monthToInt(B.month) && day == B.day && hour == B.hour && minute < B.minute));

	};

	bool operator>=(const Time& B) {
		return !(*this < B);
	};


	bool operator<= (const Time& B) {
		return !(*this > B);
	};

	Time operator-(const Time& B) {
		int dif = Time::diffInSec(*this, B);
		return Time(0, "", dif / 86400, (dif % 86400) / 3600, (dif % 3600) / 60);
	};
};




#endif 