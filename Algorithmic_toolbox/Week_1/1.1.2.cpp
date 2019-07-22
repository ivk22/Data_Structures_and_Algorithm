// 1.1.1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//


#include <iostream>
using namespace std;
int main()
{
	int n;
	cin >> n;
	uint64_t* arr = new uint64_t[n];
	for (int i = 0; i < n; ++i) {
		cin >> arr[i];
	}
	uint64_t res1 = 0,res2=0;
	int ind = 0;

	for (int i = 0; i < n; ++i) {
		if (arr[i] > res1) {
			res1 = arr[i];
			ind = i;
		}
	}

	for (int i = 0; i < n; ++i) {
		if (arr[i] > res2 && ind!=i) {
			res2 = arr[i];
		}
	}
	cout << res1 * res2;
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
