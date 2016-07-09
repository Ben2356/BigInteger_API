#include "bigint.h"

namespace BigInteger
{
	BigInt abs(const BigInt &a)
	{
		BigInt tmp(a);
		tmp.setIsPositive(true);
		return tmp;
	}
}