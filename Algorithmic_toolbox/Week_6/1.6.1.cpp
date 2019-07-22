// 1.6.1.cpp : This file contains the 'main' function. Program execution begins and ends there.
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

int main()
{
	size_t W = 0, n = 0;
	cin >> W >> n;
	size_t* values = new size_t[n];
	size_t* weights = new size_t[n];

	for (size_t i = 0; i < n; ++i) {
		cin >> weights[i];
		values[i]= weights[i];
	}


	size_t** matr = new size_t*[W+1];

	for (size_t i = 0; i <= W; ++i) {
		matr[i] = new size_t[n + 1];
		for (size_t j = 0; j <= n; ++j) {
			if (!i || !j) {
				matr[i][j] = 0;
				continue;
			}

			size_t mx = 0;
			if (weights[j - 1] <= i) {
				mx = matr[i - weights[j - 1]][j - 1] + values[j - 1];
			}

			if (matr[i][j - 1] > mx) {
				mx = matr[i][j - 1];
			}

			matr[i][j] = mx;

		}

	}
	cout << matr[W][n];
	
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
