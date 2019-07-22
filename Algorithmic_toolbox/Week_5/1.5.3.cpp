// 1.5.3.cpp : This file contains the 'main' function. Program execution begins and ends there.
//


#include <algorithm>
#include <iostream>
#include <list>
#include <vector>
#include <sstream>
#include <string>
#include <iomanip>


using namespace std;

int main()
{
	string s1,s2;
	getline(cin, s1);
	getline(cin, s2);
	size_t** matr = new size_t*[s1.size() + 1];
	for (size_t i = 0; i <= s1.size(); ++i) {

		matr[i] = new size_t[s2.size() + 1];
		if (i == 0) {
			for (size_t j = 0; j <= s2.size(); ++j) {
				matr[i][j] = j;
			}
			continue;
		}
		matr[i][0] = i;
	}

	for (size_t i = 1; i <= s1.size(); ++i) {
		for (size_t j = 1; j <= s2.size(); ++j) {
			size_t mn = 0;
			if (s1[i-1]==s2[j-1]) {
				mn = matr[i - 1][j - 1];
			}
			else {
				mn = matr[i - 1][j - 1] + 1;
			}
			if (matr[i - 1][j]+1 < mn) {
				mn = matr[i - 1][j] + 1;
			}
			if (matr[i][j-1] + 1 < mn) {
				mn = matr[i][j - 1] + 1;
			}
			matr[i][j] = mn;

		}
	}
	cout << matr[s1.size()][s2.size()];

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
