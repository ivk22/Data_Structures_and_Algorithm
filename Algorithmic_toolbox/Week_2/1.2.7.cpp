// 1.2.7.cpp : This file contains the 'main' function. Program execution begins and ends there.
//


#include <iostream>
using namespace std;

size_t Fib_period(size_t n, size_t m, size_t* arr) {

	arr[0] = 0;
	arr[1] = 1;

	size_t temp = 0;

	for (size_t i = 2; i <= n; ++i) {
		arr[i] = (arr[i - 1] + arr[i - 2]) % m;
		if (i > 2) {
			if (arr[i] == 1 && arr[i - 1] == 0) {
				return i - 1;
			}
		}
	}

}


int main()
{
	uint64_t n = 0, m = 10, s = 0;
	cin >> s >> n;

	size_t thr = m * m + 1;
	size_t* arr = new size_t[thr];

	size_t period = Fib_period(thr, m, arr);

	uint64_t res1 = 0,res2=0;

	size_t resid1 = (n + 1) % period;

	size_t resid2 = s % period;

	for (size_t i = 0; i < resid1; ++i) {
		res1 = (res1 + arr[i]) % m;
	}


	for (size_t i = 0; i < resid2; ++i) {
		res2 = (res2 + arr[i]) % m;
	}

	cout << (res1 + m - res2)%m;

}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
