// 1.5.2.cpp : This file contains the 'main' function. Program execution begins and ends there.
//


#include <algorithm>
#include <iostream>
#include <list>
#include <vector>

using namespace std;

int main()
{
	size_t n = 0;
	cin >> n;
	size_t* arr = new size_t[n + 1];
	size_t* traceback = new size_t[n + 1];

	arr[1] = 0;

	traceback[1] = 1;

	for (size_t i = 2; i <= n; ++i) {

		size_t pos = i - 1;

 		size_t mn = arr[i-1]+1, v2 = 0, v3 = 0;

		if (i % 2 == 0 && arr[i / 2] + 1< mn) {
			mn = arr[i / 2] + 1;
			pos=i/2;
		}
		if (i % 3 == 0 && arr[i / 3] + 1 < mn) {
			mn = arr[i / 3] + 1;
			pos = i / 3;
		}

		traceback[i]=pos;
		arr[i] = mn;

	}
	cout << arr[n] << endl;

	size_t val = n;
	list <size_t> lst;
	lst.push_front(val);
	while (val !=1) {
		val = traceback[val];
		lst.push_front(val);
	}
	for (const auto& val: lst) {
		cout << val << " ";
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
