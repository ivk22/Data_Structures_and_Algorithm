// 1.6.2.cpp : This file contains the 'main' function. Program execution begins and ends there.
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
	size_t n = 0;
	cin >>n;
	size_t* values = new size_t[n];
	size_t* weights = new size_t[n];

	size_t total = 0;

	for (size_t i = 0; i < n; ++i) {
		cin >> weights[i];
		values[i] = weights[i];
		total += values[i];
	}

	if (total % 3 != 0) {
		cout << 0;
	}
	else {

		size_t W = total / 3;

		size_t** matr = new size_t*[W + 1];

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

		if (matr[W][n]!= W) {
			cout << 0;
		}
		else {
			pair<size_t, size_t> p = { W,n };

			bool* occupaied = new bool[n];

			for (size_t i = 0; i < n; ++i) {
				occupaied[i] = 0;
			}

			size_t new_size=n;

			while (p.first && p.second) {
				--p.second;
				if (p.first > weights[p.second]) {
					if (matr[p.first][p.second+1] == matr[p.first - weights[p.second]][p.second] + values[p.second]) {
						p.first -= weights[p.second];
						occupaied[p.second] = 1;
						--new_size;
						continue;
					}
				}
			}

			size_t* new_weights = new size_t[new_size];
			size_t* new_values = new size_t[new_size];
			size_t k = 0;

			for (size_t i = 0; i < n;++i) {
				if (!occupaied[i]) {
					new_weights[k] = weights[i];
					new_values[k] = values[i];
					++k;
				}
			}

			size_t** matr = new size_t*[W + 1];

			for (size_t i = 0; i <= W; ++i) {
				matr[i] = new size_t[new_size + 1];
				for (size_t j = 0; j <= new_size; ++j) {
					if (!i || !j) {
						matr[i][j] = 0;
						continue;
					}

					size_t mx = 0;
					if (new_weights[j - 1] <= i) {
						mx = matr[i - new_weights[j - 1]][j - 1] + new_values[j - 1];
					}

					if (matr[i][j - 1] > mx) {
						mx = matr[i][j - 1];
					}

					matr[i][j] = mx;

				}

			}

			if (matr[W][new_size] != W) {
				cout << 0;
			}
			else {
				cout << 1;
			}


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
