// 4.2.4.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <map>
#include <algorithm>
#include <list>
#include <sstream>
#include <ostream>
#include <iterator>
#include <set>

using namespace std;

int main()
{
	string T;
	getline(cin, T);

	set<pair <string, size_t> > s;
	

	for (size_t i = 0; i < T.size(); ++i) {

		string temp(T.begin()+i,T.end());
		s.insert(pair <string, size_t> {temp, i});
	}

	for (const auto & val : s) {
		cout << val.second << " ";
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
