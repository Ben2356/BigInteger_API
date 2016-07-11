/**
	AUTHOR: Benjamin Moreno
	LAST MODIFIED: 7/9/16
*/

#pragma once
#ifndef BIGINT_H
#define BIGINT_H
#include <iostream>
#include <string>
#include <stdexcept>
using namespace std;

//new design of BigInt could use traditional unsigned long longs and fill up each letting overflows have new unsigned long
//longs and storing all the overflows in a vector/array => would allow for the system to handle numbers more "natively"

//max size of an int possible in generic C++ is 
// unsigned long long (0 to 18446744073709551615)
//							01234567890123456789 (20 digits)
//GOAL: build a data type capable of storing more than 20 digits

class BigInt
{
private:
	/**store each digit in an array
	*/
	short *data;

	/**store the size of the num that this data type is holding
	*/
	int digits;

	/**store the sign of the number, 0 will always be positive
	*/
	bool isPositive;

	/**adds 1 to the BigInt directly
	*/
	void addOne();

	/**subtracts 1 from the BigInt directly
	*/
	void subtractOne();

	/**deep copies BigInt
	*/
	void copy(const BigInt &other);

	/**performs check on string parameter then creates a BigInt with that value; throws invalid_argument exception if string 
	is not valid
	*/
	void setBigInt(string val);

	/**increases the array size by 1 and makes new digit = 1
	*/
	void resize();

	//possibility of using resize with a specific parameter(eg parameter of newSize which in this function can pass in a negative num)
	/**removes non significant 0s
	*/
	void trim();

	/**true if this object is larger than b, should be called when both have the same number of digits but one is larger
	*/
	bool isLarger(const BigInt &b) const;

	/**true if this object is the same exact number as b including signs
	*/
	bool isEqual(const BigInt &b) const;
	
public:
	/**default constructor builds a BigInt that has a size of one and a value of 0
	*/
	BigInt();

	/**builds a BigInt given a string of the number, number can be signed eg) +45, -45, or left blank eg) 45
	*/
	BigInt(string val);
	
	/**copy constructor
	*/
	BigInt(const BigInt &other);
	
	/**destructor for dynamically allocated memory
	*/
	~BigInt();

	/**retrieves the pointer that holds the array of digits
	*/
	short* getData() const { return data; }

	/**retrieves the number of digits in the BigInt
	*/
	int getDigits() const { return digits; }

	/**retrieves a bool value that is true if the number is positive or 0 and false if negative
	*/
	bool getIsPositive() const { return isPositive; }

	/**sets the sign of the BigInt, if true then positive (for values of 0 this will default to true/positive regardless of 
	passed parameter) else false then negative
	*/
	void setIsPositive(bool b);

	/**overloaded assignment operator
	*/
	BigInt& operator=(const BigInt &other);
	
	/**addition: BigInt + BigInt
	*/
	friend BigInt operator+(const BigInt &a, const BigInt &b);

	/**addition: BigInt + long long
	*/
	friend BigInt operator+(const BigInt &a, long long num);

	/**addition: long long + BigInt
	*/
	friend BigInt operator+(long long num, const BigInt &a);

	/**subtraction: BigInt - BigInt
	*/
	friend BigInt operator-(const BigInt &a, const BigInt &b);

	/**subtraction: BigInt - long long
	*/
	friend BigInt operator-(const BigInt &a, long long num);

	/**subtraction: long long - BigInt
	*/
	friend BigInt operator-(long long num, const BigInt &a);

	/**multiplication: BigInt * BigInt
	*/
	friend BigInt operator*(const BigInt &a, const BigInt &b);

	/**multiplication: BigInt * long long
	*/
	friend BigInt operator*(const BigInt &a, long long num);

	/**multiplication: long long * BigInt
	*/
	friend BigInt operator*(long long num, const BigInt &a);

	/**division: BigInt / BigInt (NOTE: division is integer trunction)
	*/
	friend BigInt operator/(const BigInt &a, const BigInt &b);

	/**division: BigInt / long long (NOTE: division is integer trunction)
	*/
	friend BigInt operator/(const BigInt &a, long long num);

	/**division: long long / BigInt (NOTE: division is integer trunction)
	*/
	friend BigInt operator/(long long num, const BigInt &a);

	/**modulus: BigInt % BigInt (NOTE: works with negative numbers)
	*/
	friend BigInt operator%(const BigInt &a, const BigInt &b);

	/**modulus: BigInt % long long (NOTE: works with negative numbers)
	*/
	friend BigInt operator%(const BigInt &a, long long num);

	/**modulus: long long % BigInt (NOTE: works with negative numbers)
	*/
	friend BigInt operator%(long long num, const BigInt &a);

	/**prints the BigInt and its sign (even if positive)
	*/
	friend ostream& operator<<(ostream &out, const BigInt &a);

	/**writes the user input to the BigInt, provides input validition and throws an invalid_argument exception upon failure
	*/
	friend istream& operator>>(istream &in, BigInt &a);

	/**returns BigInt < BigInt
	*/
	friend bool operator<(const BigInt &a, const BigInt &b);

	/**returns BigInt < long long 
	*/
	friend bool operator<(const BigInt &a, long long num);

	/**returns long long < BigInt
	*/
	friend bool operator<(long long num, const BigInt &a);

	/**returns BigInt <= BigInt
	*/
	friend bool operator<=(const BigInt &a, const BigInt &b);

	/**returns BigInt <= long long
	*/
	friend bool operator<=(const BigInt &a, long long num);

	/**returns long long <= BigInt
	*/
	friend bool operator<=(long long num, const BigInt &a);

	/**returns BigInt > BigInt
	*/
	friend bool operator>(const BigInt &a, const BigInt &b);

	/**returns BigInt > long long
	*/
	friend bool operator>(const BigInt &a, long long num);

	/**returns long long > BigInt
	*/
	friend bool operator>(long long num, const BigInt &a);

	/**returns BigInt >= BigInt
	*/
	friend bool operator>=(const BigInt &a, const BigInt &b);

	/**returns BigInt >= long long
	*/
	friend bool operator>=(const BigInt &a, long long num);

	/**returns long long >= BigInt
	*/
	friend bool operator>=(long long num, const BigInt &a);

	/**returns BigInt == BigInt
	*/
	friend bool operator==(const BigInt &a, const BigInt &b);

	/**returns BigInt == long long
	*/
	friend bool operator==(const BigInt &a, long long num);

	/**returns long long == BigInt
	*/
	friend bool operator==(long long num, const BigInt &a);

	/**returns BigInt != BigInt
	*/
	friend bool operator!=(const BigInt &a, const BigInt &b);

	/**returns BigInt != long long
	*/
	friend bool operator!=(const BigInt &a, long long num);

	/**returns long long != BigInt
	*/
	friend bool operator!=(long long num, const BigInt &a);

	/**access and modification of specific digits in BigInt, checks to see if index is in range if not then throws out_of_range
	exception
	*/
	short& operator[](const short index);

	/**access of specific digits in BigInt, checks to see if index is in range if not then throws out_of_range
	exception
	*/
	const short& operator[](const short index) const;

	/**returns -BigInt
	*/
	BigInt operator-() const;

	/**returns a positive BigInt
	*/
	BigInt operator+() const;

	/**prefix operator that adds 1 to the BigInt
	*/
	BigInt& operator++();

	/**postfix operator that adds 1 to the BigInt
	*/
	BigInt operator++(int);

	/**prefix operator that subtracts 1 from the BigInt
	*/
	BigInt& operator--();

	/**postfix operator that subtracts 1 from the BigInt
	*/
	BigInt operator--(int);

	/**converts the stored number to a string
	*/
	string toString() const;

	/**converts the stored number to an int, will overflow if number is too large
	*/
	int toInt() const;

	/**converts the stored number to a long long, will overflow if number is too large
	*/
	long long toLong() const;
};
#endif