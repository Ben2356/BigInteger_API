#include <iostream>
#include "bigint.h"
#include <time.h>
using namespace std;

//TODO:
//create a function isZero()
//optimize
int main()
{
	/*BigInt test("0");
	BigInt test2("0");
	BigInt test3("4500");
	BigInt ops;

	time_t t = clock();
	for (test; test < test3; test++, test2++)
	{
	cout << test << " * " << test2 << " : ";
	ops = test * test2;
	cout << ops << endl;
	}
	t = clock() - t;
	cout << "SECONDS: " << (((float)t) / CLOCKS_PER_SEC) << endl;*/

	//CONTROL TEST
	/*long long ops;
	time_t t = clock();
	for (long long i = 0; i < 4500; i++)
	{
	cout << i << " * " << i << " : ";
	ops = i * i;
	cout << ops << endl;
	}
	t = clock() - t;
	cout << "SECONDS: " << (((float)t) / CLOCKS_PER_SEC) << endl;*/

	/*BigInt test("-32768");
	BigInt test2("32767");

	cout << test.toInt() << endl;
	cout << test2.toInt() << endl;*/

	BigInt test(154);
	BigInt test2(4871);
	cout << test << endl;
	cout << test2 << endl;
	test = test2;
	cout << test << endl;
	test = 35;
	cout << test << endl;

	cin.clear();
	cin.ignore();
	cin.get();

	return 0;
}