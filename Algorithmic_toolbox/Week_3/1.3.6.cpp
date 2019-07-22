// 1.3.6.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <algorithm>
#include <vector>
#include <iostream>
#include <iomanip>
#include <list>
using namespace std;

int main()
{
	size_t n = 0;
	cin >> n;
	size_t k = 1;
	list<size_t> lst;
	while (n) {
		if (k + 1>n-k) {
			lst.push_back(n);
			break;
		}
		else {
			lst.push_back(k);
		}
		
		n-=k;
		++k;

	}
	cout << lst.size() << endl;
	for (const auto & val : lst) {
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
