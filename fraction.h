// Harsh Shah
// Asignment 2

#ifndef _FRACTION_H
#define _FRACTION_H

#include<iostream>

class Fraction {
	public:
		// Define the constructor and the destructor
        // This class takes in two parameters as the input(n and d) and gives them a default value of 0 and 1 respectively
		Fraction(int n=0, int d = 1);
		~Fraction(void);

		// Overload these operators for the Fraction class
		Fraction operator+(Fraction rhs);
		Fraction operator-(Fraction rhs);
		Fraction operator*(Fraction rhs);
		Fraction operator/(Fraction rhs);

		// Overload these boolean operators for the Fraction class
		bool operator==(Fraction rhs);
		bool operator!=(Fraction rhs);
		bool operator>=(Fraction rhs);
		bool operator<=(Fraction rhs);
		bool operator>(Fraction rhs);
		bool operator<(Fraction rhs);
		
		// Makes it so that it can give access to all the private members of this class
		friend std::istream &operator>>(std::istream &, Fraction &);
		friend std::ostream &operator<<(std::ostream &, Fraction &);


	private:
		int
			num,
			den;
};


#endif