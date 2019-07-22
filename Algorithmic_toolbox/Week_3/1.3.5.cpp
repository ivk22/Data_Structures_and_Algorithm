// 1.3.5.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <algorithm>
#include <vector>
#include <iostream>
#include <iomanip>
#include <list>
using namespace std;



int main()
{
	size_t n = 0,a=0,b=0;
	cin >> n;
	vector<pair<size_t, size_t>> v(n);

	for (size_t i = 0; i < n; ++i) {
		cin >> a >> b;
		v[i] = { a,b };
	}

	sort(v.begin(), v.end());

	list<size_t> lst;

	size_t thr = v[0].second;
	
	for (size_t i = 1; i < n; ++i) {
		if (v[i].second < thr) {
			thr = v[i].second;
		}
		if (v[i].first > thr) {
			lst.push_back(thr);
			thr = v[i].second;
		}
	}
	lst.push_back(thr);
	cout << lst.size() << endl;
	for (const auto& val : lst) {
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
