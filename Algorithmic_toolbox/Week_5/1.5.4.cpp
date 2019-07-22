// 1.5.3.cpp : This file contains the 'main' function. Program execution begins and ends there.
//


#include <algorithm>
#include <iostream>
#include <list>
#include <vector>
#include <sstream>
#include <string>
#include <iomanip>
#include <stack>

using namespace std;

void Output(size_t**& matr, size_t& count, size_t i, size_t j, int64_t*& s1,
	int64_t*& s2) {
	if (!i && !j) {
		return;
	}
	if (i && matr[i][j] == matr[i - 1][j] + 1) {
		Output(matr, count, i - 1, j,s1,s2);
	}
	else if (j && matr[i][j] == matr[i][j - 1] + 1) {
		Output(matr, count, i, j - 1, s1, s2);
	}
	else {
		if (s1[i - 1] == s2[j - 1]) {
			++count;
		}
		Output(matr, count, i - 1, j - 1, s1, s2);
	}
}


int main()
{



	size_t n = 0, m = 0;
	cin >> n;

	int64_t* s1 = new int64_t[n];

	for (size_t i = 0; i < n; ++i) {
		cin >> s1[i];
	}
	cin >> m;
	int64_t* s2 = new int64_t[m];
	
	for (size_t i = 0; i < m; ++i) {
		cin >> s2[i];
	}

	size_t** matr = new size_t*[n + 1];
	for (size_t i = 0; i <= n; ++i) {

		matr[i] = new size_t[m + 1];
		if (i == 0) {
			for (size_t j = 0; j <= m; ++j) {
				matr[i][j] = 0;
			}
			continue;
		}
		matr[i][0] = 0;
	}

	

	for (size_t i = 1; i <= n; ++i) {
		for (size_t j = 1; j <= m; ++j) {
			size_t mx = 0;
			if (s1[i - 1] == s2[j - 1]) {
				mx = matr[i - 1][j - 1] + 1;
			}
			else {
				mx = matr[i - 1][j - 1];
			}
			if (matr[i - 1][j]> mx) {
				mx = matr[i - 1][j];
			}
			if (matr[i][j - 1] > mx) {
				mx = matr[i][j - 1];
			}
			matr[i][j] = mx;

		}
	}

	cout << matr[n][m];

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
