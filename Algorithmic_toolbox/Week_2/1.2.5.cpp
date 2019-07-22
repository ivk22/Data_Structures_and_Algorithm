// 1.2.5.cpp : This file contains the 'main' function. Program execution begins and ends there.
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
				return i-1;
			}
		}
	}
	
}


int main()
{
	size_t n = 0, m = 0;

	cin >> n >> m;
	size_t thr = m * m + 1;
	size_t* arr = new size_t[thr];

	size_t period = Fib_period(thr, m, arr);

	cout << arr[n%period];


	return 0;
}

