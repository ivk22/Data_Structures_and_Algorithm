// 1.3.7.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <algorithm>
#include <vector>
#include <iostream>
#include <iomanip>
#include <list>
#include <sstream>
using namespace std;

bool comp(const size_t & l, const size_t & r) {
	return (l*pow(10,to_string(r).size())+r< r*pow(10, to_string(l).size()) + l);
}

int main()
{
	string res="";
	size_t n = 0;
	cin >> n;

	vector<size_t> v(n);
	

	for (size_t i = 0; i < n; ++i) {
		cin >> v[i];

	}

	sort(v.begin(), v.end(), comp);

	for (size_t i = n-1; i < n; --i) {
		res += to_string(v[i]);
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
