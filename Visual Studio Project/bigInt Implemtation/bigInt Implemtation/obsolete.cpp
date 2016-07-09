//working but issue of inability to represent the bigInts in a way the system can understand makes this useless
/*string bigIntToBinaryString(const BigInt &a)
{
string binaryString;
BigInt tmp(a);

//working with 64 bits to test speed
for (long long i = 9223372036854775807; i > 0; i /= 2)
{
if ((tmp - i) >= 0)
{
binaryString += "1";
tmp = tmp - i;
}
else
{
binaryString += "0";
}
}
return binaryString;
}*/

//OLD UNOPTIMIZED ADDITION ALGORITHM
/*BigInt operator+(const BigInt &a, const BigInt &b)
{
if ((!a.isPositive && b.isPositive) || (a.isPositive && !b.isPositive))
{
BigInt tmp(b);
tmp.isPositive = true;
return a - tmp;
}
BigInt larger;
BigInt smaller;
if (!a.isPositive && !b.isPositive)
{
larger.isPositive = false;
}
if (a.digits >= b.digits)
{
larger = a;
smaller = b;
}
else
{
larger = b;
smaller = a;
}
int smallerIndex = smaller.digits-1;
bool addOne = false;
for (int i = larger.digits-1; i >= 0; i--,smallerIndex--)
{
if (smallerIndex >= 0)
{
larger.data[i] = larger.data[i] + smaller.data[smallerIndex] + (addOne ? 1 : 0);
addOne = false;
}
else if (addOne)
{
larger.data[i]++;
addOne = false;
}
if (larger.data[i] > 9)
{
larger.data[i] -= 10;

//check to see if new memory has to be allocated so that i-1 exists
if (i - 1 < 0)
{
larger.resize();
}
addOne = true;
}
}
return larger;
}*/

//OLD UNOPTIMIZED MULTIPLICATION ALGORITHM
/*BigInt operator*(const BigInt &a, const BigInt &b)
{
BigInt soln;
BigInt tmp(b);
tmp.isPositive = true;
for (BigInt i; i < tmp; i++)
{
soln = soln + a;
}
if (!a.isPositive && !b.isPositive)
soln.isPositive = true;
else if ((a.isPositive && !b.isPositive) || (!a.isPositive && b.isPositive))
soln.isPositive = false;
return soln;
}*/

/*bool isLarger(const BigInt &a, const BigInt &b)
{
	if (a.isPositive && !b.isPositive)
		return true;
	else if (a.isPositive && b.isPositive)
	{
		for (int i = 0; i < a.digits; i++)
		{
			if (a.data[i] > b.data[i])
				return true;
			else if (a.data[i] < b.data[i])
				return false;
		}
	}
	else if (!a.isPositive && !b.isPositive)
	{
		for (int i = 0; i < a.digits; i++)
		{
			if (a.data[i] < b.data[i])
				return true;
			else if (a.data[i] > b.data[i])
				return false;
		}
	}
	else
		return false;
}

bool isEqual(const BigInt &a, const BigInt &b)
{
	if (a.digits != b.digits || a.isPositive != b.isPositive)
		return false;
	else
	{
		for (int i = 0; i < a.digits; i++)
		{
			if (a.data[i] != b.data[i])
				return false;
		}
		return true;
	}
}*/

//OLD UNOPTIMIZED SUBTRACTION ALGORITHM
/*BigInt operator-(const BigInt &a, const BigInt &b)
{
	if ((a.isPositive && !b.isPositive) || (!a.isPositive && b.isPositive))
	{
		BigInt tmp(b);
		tmp.isPositive = a.isPositive;
		return a + tmp;
	}
	BigInt larger;
	BigInt smaller;
	bool isNegative = false;

	//larger and smaller are representive of actual value of the bigInt
	if (a.digits > b.digits)
	{
		larger = a;
		smaller = b;
	}
	else if (a.digits == b.digits)
	{
		if (a > b)
		{
			larger = a;
			smaller = b;
		}
		else
		{
			larger = b;
			smaller = a;
			isNegative = true;
		}
	}
	else
	{
		larger = b;
		smaller = a;
		isNegative = true;
	}
	int smallerIndex = smaller.digits - 1;
	for (int i = larger.digits - 1; i >= 0; i--, smallerIndex--)
	{
		if (larger.data[i] < 0)
		{
			larger.data[i - 1]--;
			larger.data[i] = 10;
		}
		if (smallerIndex >= 0)
		{
			if (smaller.data[smallerIndex] > larger.data[i])
			{
				larger.data[i - 1]--;
				larger.data[i] += 10;
			}
			larger.data[i] = larger.data[i] - smaller.data[smallerIndex];
		}
	}
	//b > a then same value numerically as a - b but negative
	if (isNegative)
		larger.isPositive = false;

	//trim the solution
	larger.trim();

	//if the answer is 0 then make sure it is positive
	if (larger.digits == 1 && larger.data[0] == 0)
		larger.isPositive = true;

	return larger;
}*/

//UNOPTIMIZED DIVISION ALGORITHM
/*BigInt operator/(const BigInt &a, const BigInt &b)
{
	BigInt tmp(a);
	BigInt divisor(b);
	BigInt count;
	divisor.isPositive = true;
	tmp.isPositive = true;
	if (divisor > tmp)
		return count;
	while (tmp != 0)
	{
		tmp = tmp - divisor;
		count++;
	}
	if ((!a.isPositive && b.isPositive) || a.isPositive && !b.isPositive)
		count.isPositive = false;
	return count;
}*/

//UNOPTIMIZED MODULUS ALGORITHM
/*BigInt operator%(const BigInt &a, const BigInt &b)
{
	BigInt tmp(a);
	BigInt divisor(b);
	divisor.isPositive = true;
	tmp.isPositive = true;
	if (divisor == tmp)
	{
		BigInt count;
		return count;
	}
	while (tmp > divisor)
	{
		tmp = tmp - divisor;
	}
	if (!a.isPositive)
		tmp.isPositive = false;
	return tmp;
	}*/