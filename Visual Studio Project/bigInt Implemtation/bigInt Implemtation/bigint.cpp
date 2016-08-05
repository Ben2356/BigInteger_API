/**
	AUTHOR: Benjamin Moreno
	LAST MODIFIED: 8/5/16
*/
#include <iostream>
#include <string>
#include <stdexcept>
#include "bigint.h"
using namespace std;

//validates a given string to make sure it contains only digits and/or a starting pos/neg sign
bool isValidString(string in)
{
	if (in.empty())
		return false;
	for (int i = 0; i < in.size(); i++)
	{
		//first char can be '+' || '-' to denote sign
		if (i == 0)
		{
			if ((in[i] != '+' && in[i] != '-') && (in[i] < 48 || in[i] > 57))
				return false;
		}

		//if not a digit
		else if (in[i] < 48 || in[i] > 57)
		{
			return false;
		}
	}
	return true;
}

//
//BIGINT PRIVATE FUNCTIONS START
//
void BigInt::addOne()
{
	if (data[digits - 1] == 9)
	{
		data[digits - 1] = 0;
		if (digits - 2 < 0)
		{
			resize();
		}
		else
		{
			bool addOne = true;
			for (int i = digits - 2; i >= 0; i--)
			{
				if (addOne)
				{
					data[i]++;
					addOne = false;
				}
				if (data[i] > 9)
				{
					data[i] -= 10;

					//check to see if new memory has to be allocated so that i-1 exists
					if (i - 1 < 0)
					{
						resize();
					}
					addOne = true;
				}
			}
		}
	}
	else
		data[digits - 1]++;
}

void BigInt::copy(const BigInt &other)
{
	data = new short[other.digits];
	digits = other.digits;
	isPositive = other.isPositive;
	for (int i = 0; i < other.digits; i++)
	{
		data[i] = other.data[i];
	}
}

void BigInt::clear()
{
	delete[] data;
	data = 0;
}

void BigInt::subtractOne()
{
	if (data[digits - 1] == 0)
	{
		data[digits - 1] = 9;
		data[digits - 2]--;
		for (int i = digits - 2; i >= 0; i--)
		{
			if (data[i] < 0)
			{
				data[i] = 9;
				data[i - 1]--;
			}
		}
		trim();
	}
	else
		data[digits - 1]--;
}

void BigInt::setBigInt(string val)
{
	if (!isValidString(val))
	{
		invalid_argument e("Passed string is invalid");
		throw e;
	}
	if (val[0] == '-' || val[0] == '+')
		digits = val.size() - 1;
	else
		digits = val.size();
	data = new short[digits];
	int digitIndex = 0;
	for (int i = 0; i < val.size(); i++)
	{
		if (i == 0)
		{
			if (val[i] == '-')
			{
				isPositive = false;
				continue;
			}
			else if (val[i] == '+')
			{
				isPositive = true;
				continue;
			}
			else
				isPositive = true;
		}
		data[digitIndex++] = val[i] - '0';
	}
}

void BigInt::setBigInt(long long val)
{
	if (val == 0)
	{
		data = new short[1];
		data[0] = 0;
		isPositive = true;
		digits = 1;
	}
	else
	{
		string tmp = to_string(val);
		int i = 0;
		if (tmp[0] == '-')
		{
			isPositive = false;
			i = 1;
		}
		else
			isPositive = true;
		digits = tmp.size() - i;
		data = new short[digits];
		for (int index = 0; i < tmp.size(); i++)
		{
			data[index++] = tmp[i] - '0';
		}
	}
}

void BigInt::resize()
{
	int* tmp = new int[digits];
	for (int i = 0; i < digits; i++)
		tmp[i] = data[i];
	delete[] data;
	digits++;
	data = new short[digits];
	for (int j = 1; j < digits; j++)
	{
		data[j] = tmp[j - 1];
	}
	data[0] = 1;
	delete[] tmp;
}

void BigInt::trim()
{
	//in the case of a value of 0 or if the first value is not a 0 then don't trim
	if (digits == 1 || data[0] != 0)
		return;
	int trimSize = 0;
	for (int i = 0; i < digits; i++)
	{
		//leave one 0 left when solution is completely 0s
		if (trimSize == digits - 1)
			break;

		//if a value other than 0 is hit then 0s following are no longer non significant
		if (data[i] != 0)
			break;

		if (data[i] == 0)
			trimSize++;
	}
	short* tmp = new short[digits - trimSize];
	int tmpIndex = 0;
	for (int i = trimSize; i < digits; i++)
		tmp[tmpIndex++] = data[i];
	delete[] data;
	data = tmp;
	digits -= trimSize;
}

bool BigInt::isLarger(const BigInt &b) const
{
	if (isPositive && !b.isPositive)
		return true;
	else if (isPositive && b.isPositive)
	{
		for (int i = 0; i < digits; i++)
		{
			if (data[i] > b.data[i])
				return true;
			else if (data[i] < b.data[i])
				return false;
		}
	}
	else if (!isPositive && !b.isPositive)
	{
		for (int i = 0; i < digits; i++)
		{
			if (data[i] < b.data[i])
				return true;
			else if (data[i] > b.data[i])
				return false;
		}
	}
	else
		return false;
}

bool BigInt::isEqual(const BigInt &b) const
{
	if (digits != b.digits || isPositive != b.isPositive)
		return false;
	else
	{
		for (int i = 0; i < digits; i++)
		{
			if (data[i] != b.data[i])
				return false;
		}
		return true;
	}
}
//
//END BIGINT PRIVATE FUNCTIONS
//

//
//BIGINT PUBLIC FUNCTIONS START
//
BigInt::BigInt()
	: data(new short[1]), digits(1), isPositive(true)
{
	data[0] = 0;
}

BigInt::BigInt(string val)
{
	setBigInt(val);
}

//val of a long long has the potential for up to 19 digits
BigInt::BigInt(long long val)
{
	setBigInt(val);
}

BigInt::BigInt(const BigInt &other)
{
	copy(other);
}

BigInt::~BigInt()
{
	clear();
}

void BigInt::setIsPositive(bool b)
{
	//set to true in the case of 0 just to be safe
	if (digits == 1 && data[0] == 0)
		isPositive = true;

	else
		isPositive = b;
}

BigInt& BigInt::operator=(const BigInt &other)
{
	if (this == &other)
		return *this;
	else
	{
		if (data != 0)
			clear();
		copy(other);
		return *this;
	}
}

BigInt& BigInt::operator=(const long long num)
{
	if (data != 0)
		clear();
	setBigInt(num);
	return *this;
}

//modify + operator so that it can add negative numbers to handle cases of subtractions
//OPTIMIZATION: once all the digits are adjusted that are over 9 and added value is done then break out of for loop
BigInt operator+(const BigInt &a, const BigInt &b)
{
	if ((!a.isPositive && b.isPositive) || (a.isPositive && !b.isPositive))
	{
		BigInt tmp(b);
		tmp.isPositive = true;
		return a - tmp;
	}
	BigInt soln;
	bool a_smaller = false;
	if (!a.isPositive && !b.isPositive)
	{
		soln.isPositive = false;
	}
	if (a.digits >= b.digits)
	{
		soln = a;
	}
	else
	{
		soln = b;
		a_smaller = true;
	}
	int smallerIndex = (a_smaller ? a.digits - 1 : b.digits - 1);
	bool addOne = false;
	for (int i = soln.digits - 1; i >= 0; i--, smallerIndex--)
	{
		if (smallerIndex >= 0)
		{
			soln.data[i] = soln.data[i] + (a_smaller ? a.data[smallerIndex] : b.data[smallerIndex]);
		}
		if (addOne)
		{
			soln.data[i]++;
			addOne = false;
		}
		if (soln.data[i] > 9)
		{
			soln.data[i] -= 10;

			//check to see if new memory has to be allocated so that i-1 exists
			if (i - 1 < 0)
			{
				soln.resize();
			}
			addOne = true;
		}
	}
	return soln;
}

BigInt operator+(const BigInt &a, long long num)
{
	return a + BigInt(to_string(num));
}

BigInt operator+(long long num, const BigInt &a)
{
	return a + num;
}

BigInt operator-(const BigInt &a, const BigInt &b)
{
	if ((a.isPositive && !b.isPositive) || (!a.isPositive && b.isPositive))
	{
		BigInt tmp(b);
		tmp.isPositive = a.isPositive;
		return a + tmp;
	}
	BigInt soln;
	bool a_smaller = false;
	bool isNegative = false;

	//larger and smaller are representive of actual value of the bigInt
	if (a.digits > b.digits)
	{
		soln = a;
	}

	else if (a.digits == b.digits)
	{
		if (a > b)
		{
			soln = a;
		}
		else
		{
			soln = b;
			a_smaller = true;
			isNegative = true;
		}
	}
	else
	{
		soln = b;
		a_smaller = true;
		isNegative = true;
	}
	int smallerIndex = (a_smaller ? a.digits - 1 : b.digits - 1);
	for (int i = soln.digits - 1; i >= 0; i--, smallerIndex--)
	{
		if (soln.data[i] < 0)
		{
			soln.data[i - 1]--;
			soln.data[i] = 10;
		}
		if (smallerIndex >= 0)
		{
			if ((a_smaller ? a.data[smallerIndex] : b.data[smallerIndex]) > soln.data[i])
			{
				soln.data[i - 1]--;
				soln.data[i] += 10;
			}
			soln.data[i] = soln.data[i] - (a_smaller ? a.data[smallerIndex] : b.data[smallerIndex]);
		}
	}
	//b > a then same value numerically as a - b but negative
	if(isNegative)
		soln.isPositive = false;

	//trim the solution
	soln.trim();

	//if the answer is 0 then make sure it is positive
	if (soln.digits == 1 && soln.data[0] == 0)
		soln.isPositive = true;

	return soln;
}

//long long is smaller than a unsigned long long but removes possibility of negative values
BigInt operator-(const BigInt &a, long long num)
{
	return a - BigInt(to_string(num));
}

BigInt operator-(long long num, const BigInt &a)
{
	return BigInt(to_string(num)) - a;
}

BigInt operator*(const BigInt &a, const BigInt &b)
{
	BigInt soln;
	for (BigInt i; (b.isPositive ? i < b : i > b); (b.isPositive ? i++ : i--))
	{
		soln = soln + a;
	}
	if (!a.isPositive && !b.isPositive)
		soln.isPositive = true;
	else if ((a.isPositive && !b.isPositive) || (!a.isPositive && b.isPositive))
		soln.isPositive = false;
	return soln;
}

BigInt operator*(const BigInt &a, long long num)
{
	return a * BigInt(to_string(num));
}

BigInt operator*(long long num, const BigInt &a)
{
	return a * num;
}

BigInt operator/(const BigInt &a, const BigInt &b)
{
	BigInt tmp(a);
	BigInt count;
	tmp.isPositive = true;
	if (b.isPositive ? b.isPositive : !b.isPositive)
		return count;
	while (tmp != 0)
	{
		tmp = tmp - (b.isPositive ? b : -b);
		count++;
	}
	if ((!a.isPositive && b.isPositive) || a.isPositive && !b.isPositive)
		count.isPositive = false;
	return count;
}

BigInt operator/(const BigInt &a, long long num)
{
	return a / BigInt(to_string(num));
}

BigInt operator/(long long num, const BigInt &a)
{
	return BigInt(to_string(num)) / a;
}

BigInt operator%(const BigInt &a, const BigInt &b)
{
	BigInt tmp(a);
	tmp.isPositive = true;
	if ((b.isPositive ? b : -b) == tmp)
	{
		BigInt count;
		return count;
	}
	while (tmp > (b.isPositive ? b : -b))
	{
		tmp = tmp - (b.isPositive ? b : -b);
	}
	if (!a.isPositive)
		tmp.isPositive = false;
	return tmp;
}

BigInt operator%(const BigInt &a, long long num)
{
	return a % BigInt(to_string(num));
}

BigInt operator%(long long num, const BigInt &a)
{
	return BigInt(to_string(num)) % a;
}

ostream& operator<<(ostream &out, const BigInt &a)
{
	out << (a.isPositive ? "+" : "-");
	for (int i = 0; i < a.digits; i++)
	{
		out << a.data[i];
	}
	return out;
}

istream& operator>>(istream &in, BigInt &a)
{
	string par;
	in >> par;
	a.setBigInt(par);
	return in;
}

bool operator<(const BigInt &a, const BigInt &b)
{
	//if both are 0
	if (a.digits == 1 && b.digits == 1 && a.data[0] == 0 && b.data[0] == 0)
		return false;
	
	//if both have the same number of digits
	if (a.digits == b.digits)
		return !(a.isLarger(b));

	else
		return a.digits < b.digits;
}

bool operator<(const BigInt &a, long long num)
{
	return a < BigInt(to_string(num));
}

bool operator<(long long num, const BigInt &a)
{
	return BigInt(to_string(num)) < a;
}

bool operator<=(const BigInt &a, const BigInt &b)
{
	return (a < b || a.isEqual(b));
}

bool operator<=(const BigInt &a, long long num)
{
	return a <= BigInt(to_string(num));
}

bool operator<=(long long num, const BigInt &a)
{
	return BigInt(to_string(num)) <= a;
}

bool operator>(const BigInt &a, const BigInt &b)
{
	return !(a <= b);
}

bool operator>(const BigInt &a, long long num)
{
	return a > BigInt(to_string(num));
}

bool operator>(long long num, const BigInt &a)
{
	return BigInt(to_string(num)) > a;
}

bool operator>=(const BigInt &a, const BigInt &b)
{
	return (!(a <= b) || a.isEqual(b));
}

bool operator>=(const BigInt &a, long long num)
{
	return a >= BigInt(to_string(num));
}

bool operator>=(long long num, const BigInt &a)
{
	return BigInt(to_string(num)) >= a;
}

bool operator==(const BigInt &a, const BigInt &b)
{
	return a.isEqual(b);
}

bool operator==(const BigInt &a, long long num)
{
	return a == BigInt(to_string(num));
}

bool operator==(long long num, const BigInt &a)
{
	return BigInt(to_string(num)) == a;
}

bool operator!=(const BigInt &a, const BigInt &b)
{
	return !a.isEqual(b);
}

bool operator!=(const BigInt &a, long long num)
{
	return a != BigInt(to_string(num));
}

bool operator!=(long long num, const BigInt &a)
{
	return BigInt(to_string(num)) != a;
}

short& BigInt::operator[](const short index)
{
	if(index < digits && index >= 0)
		return data[index];
	else
	{
		out_of_range e("Index is out of bounds of BigInt data array");
		throw e;
	}
}

const short& BigInt::operator[](const short index) const
{
	if (index < digits && index >= 0)
		return data[index];
	else
	{
		out_of_range e("Index is out of bounds of BigInt data array");
		throw e;
	}
}

BigInt BigInt::operator-() const
{
	BigInt tmp(*this);
	tmp.isPositive = !isPositive;
	return tmp;
}

BigInt BigInt::operator+() const
{
	if (this->isPositive)
		return *this;
	else
	{
		BigInt tmp(*this);
		tmp.isPositive = true;
		return tmp;
	}
}

BigInt& BigInt::operator++()
{
	if (isPositive)
		addOne();
	else
		subtractOne();
	if (digits == 1 && data[0] == 0)
		isPositive = true;
	return *this;
}

BigInt BigInt::operator++(int)
{
	BigInt tmp(*this);
	++(*this);
	return tmp;
}

BigInt& BigInt::operator--()
{
	if (digits == 1 && data[0] == 0)
	{
		addOne();
		isPositive = false;
	}
	else if (isPositive)
		subtractOne();
	else
		addOne();
	return *this;
}

BigInt BigInt::operator--(int)
{
	BigInt tmp(*this);
	--(*this);
	return tmp;
}

string BigInt::toString() const
{
	string val;
	if (!isPositive)
	{
		val += '-';
	}
	for (int i = 0; i < digits; i++)
	{
		val += to_string(data[i]);
	}
	return val;
}

int BigInt::toInt() const
{
	int num;
	string noSign;
	noSign = toString();
	if (!isPositive)
	{
		noSign = noSign.substr(1);
		num = stoi(noSign);
		num = -num;
	}
	else
		num = stoi(noSign);
	return num;
}

long long BigInt::toLong() const
{
	long long num;
	string noSign;
	noSign = toString();
	if (!isPositive)
	{
		noSign = noSign.substr(1);
		num = stoll(noSign);
		num = -num;
	}
	else
		num = stoll(noSign);
	return num;
}
//
//END BIGINT PUBLIC FUNCTIONS
//
