// 1.5.1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//


#include <iostream>
using namespace std;

int main()
{
	size_t n = 0;
	cin >> n;
	size_t* arr = new size_t[n+1];
	arr[0]=0;
	size_t* coins = new size_t[3];
	coins[0] = 1;
	coins[1] = 3;
	coins[2] = 4;
	for (size_t i = 1; i <= n; ++i) {

		size_t mn = 0;

		for (size_t j = 0; j < 3; ++j) {
			if (i >= coins[j]) {
				if (arr[i - coins[j]] + 1 < mn || !mn) {
					mn = arr[i - coins[j]] + 1;
				}
			}
		}
		arr[i] = mn;
	}
	cout << arr[n];

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
