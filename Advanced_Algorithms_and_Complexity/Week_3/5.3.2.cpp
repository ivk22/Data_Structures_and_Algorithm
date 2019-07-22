// 5.3.2.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include <list>
#include <set>
#include <iterator>
#include <algorithm>
using namespace std;



int main()
{
	int n = 0, m = 0;
	cin >> n >> m;
	set<int>* G = new set<int>[n + 1];

	for (int i = 0; i < m; ++i) {
		int v = 0, u = 0;

		cin >> u >> v;
		G[u].insert(v);
		G[v].insert(u);

	}

	int pairs = 0;

	for (int i = 1; i <= n; ++i) {
		pairs += n - G[i].size()-1;
	}

	cout << 2*n + n*2 * ((n*(n - 1)) / 2)+(n-1)*pairs << " " << n*n << endl;
	for (int i = 0; i < n; ++i) {
		for (int j = 1; j <= n; ++j) {
			cout << i * n + j << " ";
		}
		cout << 0 << endl;

		for (int j = 1; j <= n; ++j) {
			cout << (j-1)*n+i+1 << " ";
		}
		cout << 0 << endl;
	}

	for (int k = 0; k < n; ++k) {
		for (int i = 1; i < n; ++i) {
			for (int j = i + 1; j <= n; ++j) {
				cout << -(i+k*n) << " " << -(j + k * n) << " " << 0 << endl;
				cout << -((i-1)*n+k+1) << " " << -((j-1)*n+k+1) << " " << 0 << endl;
			}
		}
	}

	set<int> st;

	for (int i = 1; i <= n; ++i) {
		st.insert(i);
	}

	for (int i = 1; i <= n; ++i) {
		set<int> s = st;

		set<int> result;

		G[i].insert(i);

		set_difference(s.begin(),s.end(),
			G[i].begin(),G[i].end(), inserter(result, result.end()));

		for (const auto & val : result) {
			for (int k = 1; k < n; ++k) {
				cout << -((i - 1)*n + k) << " " << -((val - 1)*n + k+1) << " " << 0 << endl;
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
