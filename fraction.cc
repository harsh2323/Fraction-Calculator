// Harsh Shah
// Assignment 2

#include "fraction.h"

// function to find the greatest common divsor
static int gcd(int a, int b) {
	int r;

	if( a < 0 ) {
		a = -a;
	}
	if( b < 0 ) {
		b = -b;
	}

	while( b != 0 ) {
		r = a % b;
		a = b;
		b = r;
	}

	return a;
}

// Implementation of the constructor
Fraction::Fraction(int n, int d) {
	int g;

	if( n < 0 ){
		n = -n;
		d = -d;
	}

	g = gcd(n, d);

	n /= g;
	d /= g;
	num = n;
	den = d;
}

Fraction::~Fraction(void) { }

// Implementation of the plus operator
Fraction Fraction::operator+(Fraction rhs) {
	int s, t;

	s = num * rhs.den + den * rhs.num;
	t = den * rhs.den;

	return Fraction(s, t);
}

// Implementation of the minus operator
Fraction Fraction::operator-(Fraction rhs) {
	int s,t;

	s = num * rhs.den - den * rhs.num;
	t = den * rhs.den;

	return Fraction(s, t);
}

// Implementation of the multiplication operator
Fraction Fraction::operator*(Fraction rhs) {
	int s,t;

	s = num * rhs.num;
	t = den * rhs.den;

	return Fraction(s, t);
}

// Implementation of the division operator
Fraction Fraction::operator/(Fraction rhs) {
	int s, t;

	s = rhs.den * num;
	t = den * rhs.num;

	return Fraction(s, t);
}

// Implementation of the comparison operator
bool Fraction::operator==(Fraction rhs) {
	return num == rhs.num && den == rhs.den;
}

// Implementation of the "less than" operator
bool Fraction::operator<(Fraction rhs) {
	if( den * rhs.den >= 0) {
		return num * rhs.den < den * rhs.num;
	}
	else {
		return num * rhs.den > den * rhs.num;
	}
}

// Implementation of the "greater than" operator
bool Fraction::operator>(Fraction rhs) {
	if( den * rhs.den >=0 ) {
		return num * rhs.den > den * rhs.num;
	}
	else {
		return num * rhs.den > den * rhs.num;
	}
}

// Implementation of the "less than or equal to" operator
bool Fraction::operator<=(Fraction rhs) {
	if( den * rhs.den >= 0 ) {
		return num * rhs.den <= den * rhs.num;
	}
	else {
		return num * rhs.den <= den * rhs.num;
	}
}

// Implementation of the "greater than or equal to" operator
bool Fraction::operator>=(Fraction rhs) {
	if( den * rhs.den >= 0 ) {
		return num * rhs.den >= den * rhs.num;
	}
	else {
		return num * rhs.den >= den * rhs.num;
	}
}

// Implementation of the "not equal to" operator
bool Fraction::operator!=(Fraction rhs) {
	if( den * rhs.den >= 0 ) {
		return num * rhs.den != den * rhs.num;
	}
	else {
		return num * rhs.den != den * rhs.num;
	}
}

// Implementation of the operator ">>" to collect the input from the users
std::istream &operator>>(std::istream &is, Fraction &f) {
	int n,d;

	char slash;

	is >> n >> slash >> d;

	f = Fraction(n, d);

	return is;	
}

// Implementation of the operator "<<" to display the output to the user
std::ostream &operator<<(std::ostream &os, Fraction &f) {
	os << f.num << " / " << f.den;

	return os;
}