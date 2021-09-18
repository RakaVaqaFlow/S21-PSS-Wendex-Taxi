#ifndef POINT
#define POINT
#include <iostream>
#include <math.h>
#include <iomanip>

using namespace std;

class Point {
public:
	double x_c;
	double y_c;
	Point(int X, int Y) : x_c(X), y_c(Y) {}
	Point() :x_c(0), y_c(0) {}
	pair<double, double> getPoint() {
		return make_pair(x_c, y_c);
	}

	void setPoint(double X, double Y) {
		x_c = X;
		y_c = Y;
	}

	static double calcLength(Point A, Point B) {
		return sqrt((A.x_c - B.x_c) * (A.x_c - B.x_c) + (A.y_c - B.y_c) * (A.y_c - B.y_c));
	}
};

#endif