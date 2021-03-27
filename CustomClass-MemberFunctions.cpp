#include <iostream>
#include "math.h"

using namespace std;

class Complex
{
public: 
    Complex(double = 0.0, double = 0.0, char = ' ');
    ~Complex();

private:
    char name; 
    double realPart;
    double imaginaryPart;

public: 
    void setName(char n);
    void setRealPart(double);
    void setImaginaryPart(double i);
    void assignNewValues(double, double, char n);

    void showComplexValues();
    double getRealPart(); 
    double getImaginaryPart(); 
    char getName(); 

    double amplitude();
    void multiply(Complex&);
    void swap(Complex&);

    Complex multScalar(double);

    Complex operator+(const Complex&);
    bool operator == (const Complex&);
};

bool Complex::operator==(const Complex& complex2)
{
    return (this->realPart == complex2.realPart) && (this->imaginaryPart == complex2.imaginaryPart);
}

Complex Complex::operator+(const Complex& complex2)
{
    Complex temp;
    temp.realPart = this->realPart + complex2.realPart;
    temp.imaginaryPart = this->imaginaryPart + complex2.imaginaryPart;
    return temp;
}

Complex Complex::multScalar(double factor)
{
    Complex m(0.0, 0.0, 'M');
    m.realPart = (*this).realPart * factor;
    m.imaginaryPart = (*this).imaginaryPart * factor;

    return m;
}

double Complex::amplitude()
{
    double a = sqrt(pow(realPart, 2) + pow(imaginaryPart, 2));
    return a;
}

Complex::Complex(double a, double b, char n)
{
    realPart = a; 
    imaginaryPart = b;
    name = n;
    //cout << name << "Constructor Called!" << endl;
}

Complex::~Complex()
{
    //cout << name << "Destructor Called!" << endl;
    realPart = 0.0;
}

void Complex::assignNewValues(double a, double b, char n)
{
    realPart = a;
    imaginaryPart = b;
    name = n;
}

void Complex::showComplexValues()
{
    char sign = '+';
    if (imaginaryPart < 0)
    {
        sign = '-';
    }
    cout << name << ", Value is: " << realPart << " " << sign << " " << abs(imaginaryPart) << "i" << endl;
}

inline void Complex::setRealPart(double r)
{
    realPart = r;
}

inline double Complex::getRealPart()
{
    return realPart;
}

inline void Complex::setName(char n)
{
    (*this).name = n; 
}

inline char Complex::getName()
{
    return name; 
}

inline void Complex::setImaginaryPart(double r)
{
    (*this).imaginaryPart = r; 
}

inline double Complex::getImaginaryPart()
{
    return (*this).imaginaryPart; 
}

void Complex::multiply(Complex& a)
{
    double temp = 0.0;
    Complex answer; 
    answer.realPart = ((*this).realPart * (*this).imaginaryPart) - ((*this).imaginaryPart * a.imaginaryPart);
    answer.imaginaryPart = ((*this).realPart * a.imaginaryPart) + ((*this).imaginaryPart + a.realPart);
    (*this).setRealPart(answer.getRealPart());
    (*this).setImaginaryPart(answer.getImaginaryPart());
}

void Complex::swap(Complex& b)
{
    Complex temp; 
    temp.assignNewValues(b.getRealPart(), b.getImaginaryPart(), b.getName());
    b.assignNewValues((*this).getRealPart(), (*this).getImaginaryPart(), (*this).getName());
    (*this).assignNewValues(temp.getRealPart(), temp.getImaginaryPart(), temp.getName());
}

int main()
{
    Complex a, b, c(4.5, 8.9, 'C');
    b.assignNewValues(3.3, 9.9, 'B');

    b.showComplexValues();
    c.showComplexValues();

    b.swap(c);

    b.showComplexValues();
    c.showComplexValues();

    b.multiply(c);

    b.showComplexValues();
}

