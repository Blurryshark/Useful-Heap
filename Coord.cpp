#include <stdio.h>
#include <iostream>
#include <cmath>

using namespace std;

class Coord 
{
public:
	Coord (); 
	Coord (double, double, double);
private: 
	double xval;
	double yval;
	double theta;
public:
	void setXVal(double);
	double getXVal();

	void setYVal(double);
	double getYVal();

	void setTheta(double);
	double getTheta();

	void display();

	Coord convPol(double, double,double, double);
};

inline void Coord::setXVal(double newVal)
{
	(*this).xval = newVal;
}
inline double Coord::getXVal()
{
	return (*this).xval;
}

inline void Coord::setYVal(double newVal)
{
	(*this).yval = newVal;
}
inline double Coord::getYVal()
{
	return (*this).yval;
}

inline void Coord::setTheta(double newValue)
{
	(*this).theta = newValue;
}
inline double Coord::getTheta()
{
	return (*this).theta;
}

void Coord::display()
{
	cout << "(" << xval << ", " << yval << ")" << endl;
}

Coord Coord::convPol(double x, double y, double r, double t)
{
	Coord temp;

	temp.setXVal(r*cos(theta));
	temp.setYVal(r*sin(theta));
	temp.setTheta(t);

	return temp; 
}

Coord::Coord()
{
	xval = 0.0;
	yval = 0.0;
}
Coord::Coord(double x, double y, double t)
{
	xval = x;
	yval = y; 
	theta = t;
}

int main()
{
	Coord x(1.0, 2.0, 10.0);
	x.display();

	Coord a(10.0, 15.0, 10.0);
	a.display();
	return 0;
}