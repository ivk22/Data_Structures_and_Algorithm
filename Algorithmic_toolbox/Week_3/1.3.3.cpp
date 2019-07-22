// 1.3.3.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <algorithm>
#include <vector>
#include <iostream>
#include <iomanip>
using namespace std;

int main()
{
	size_t d = 0, m = 0, n = 0;
	cin >> d >> m >> n;
	++n;
	size_t* arr = new size_t[n];
	arr[n - 1] = d;
	size_t cur = m, res = 0;
	for (size_t i = 0; i < n - 1; ++i) {
		cin>> arr[i];
	}
	if (arr[0] > cur) {
		cout << -1;
	}
	else {
		cur -= arr[0];
		bool b = 1;
		for (size_t i = 0; i < n - 1; ++i) {
			if (arr[i + 1] - arr[i] > m) {
				cout << -1;
				b = 0;
				break;
			} else if (arr[i + 1] - arr[i] > cur) {
				++res;
				cur = m-(arr[i + 1] - arr[i]);
			}
			else {
				cur -= (arr[i + 1] - arr[i]);
			}
		}
		if (b) {
			cout << res;
		}
	}

	
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
