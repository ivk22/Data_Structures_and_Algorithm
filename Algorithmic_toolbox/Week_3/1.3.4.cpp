// 1.3.4.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <algorithm>
#include <vector>
#include <iostream>
#include <iomanip>
using namespace std;

int main()
{
	size_t n = 0;
	cin >> n;
	vector<int64_t> a(n),b(n);
	for (size_t i = 0; i < n; ++i) {
		cin >> a[i];
	}
	for (size_t i = 0; i < n; ++i) {
		cin >> b[i];
	}

	sort(a.begin(), a.end());

	sort(b.begin(), b.end());

	int64_t res = 0;
	for (size_t i = 0; i < n; ++i) {
		res+=a[i]*b[i];
	}
	cout << res;
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
