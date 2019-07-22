// 1.2.8.cpp : This file contains the 'main' function. Program execution begins and ends there.
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
	uint64_t n = 0, m = 10;
	cin >> n;

	size_t thr = m * m + 1;
	size_t* arr = new size_t[thr];

	size_t period = Fib_period(thr, m, arr);

	cout << (arr[n%period] * arr[(n + 1) % period])%m;

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
