// 5.4.3_final.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include <list>
#include <queue>
#include <limits>
#include <limits.h>
#include <cmath>
#include <math.h>

using namespace std;

int main()
{

	size_t n = 0, m = 0;
	cin >> n >> m;


	vector<vector<int64_t>> G(n + 1, vector<int64_t>(n + 1, 0));


	for (size_t i = 0; i < m; ++i) {
		size_t u = 0, v = 0, t = 0;
		cin >> u >> v >> t;
		G[u][v]=t;
		G[v][u]=t;
	}


	uint64_t p = (1<<(n-1));

	
	vector<vector<pair<int64_t, int64_t>>> T(p, vector<pair<int64_t, int64_t>>(n, { -1 ,-1}));


	for (size_t k = 1; k < p; ++k) {
		for (size_t i = 1; i < n; ++i) {
			if (!(k&(1 << (i - 1)))) {
				continue;
			}

			if (!(k ^ (1 << (i-1)))) {
				if (G[1][i + 1]) {
					T[k][i] = { G[1][i + 1] ,0 };
				}
				continue;
			}

			for (size_t j = 1; j < n; ++j) {
				if (j != i) {
					if (G[j + 1][i + 1] && T[k ^ (1 << (i - 1))][j].first!=-1) {
						if (T[k][i].first == -1) {
							T[k][i].first = T[k ^ (1 << (i - 1))][j].first + G[j + 1][i + 1];
							T[k][i].second = j;
						}
						else {
							if (T[k ^ (1 << (i - 1))][j].first + G[j + 1][i + 1]< T[k][i].first) {
								T[k][i].first = T[k ^ (1 << (i - 1))][j].first + G[j + 1][i + 1];
								T[k][i].second = j;
							}
							
						}
						
					}
				}
			}
		}
	}

	int64_t mn = -1;

	size_t last = 0;
	for (size_t j = 1; j < n; ++j) {
		if (G[j + 1][1] && T[p - 1][j].first != -1) {
			if (mn == -1 || T[p - 1][j].first + G[j + 1][1] < mn) {
				mn = T[p - 1][j].first + G[j + 1][1];
				last = j;
			}
		}
	}
	cout << mn;

	if (mn != -1) {
		cout << endl;
		uint64_t val = p - 1;
		vector<size_t> v(n);

		v[n - 1] = last+1;
		size_t pos = n - 1;

		while (pos) {
			--pos;

			size_t next_last = T[val][last].second;

			val = (val ^ (1<<(last-1)));

			last = next_last;

			v[pos] = last+1;
			
		}
		for (size_t j = 0; j < n; ++j) {
			cout << v[j] << (j< n -1 ? " ":"");
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
