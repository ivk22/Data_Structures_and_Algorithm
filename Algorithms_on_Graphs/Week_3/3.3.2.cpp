// 3.3.2.cpp : This file contains the 'main' function. Program execution begins and ends there.
//


#include <iostream>
#include <string>
#include <queue>
#include <ostream>
#include <sstream>
#include <iterator>
#include <cmath>
#include <list>
#include <algorithm>
#include <vector>
#include <random>
using namespace std;


bool Explore(size_t v, list<size_t>*& G, 
	bool * visited, bool * color, bool col) {
	visited[v] = 1;
	color[v] = col;
	for (const auto & val : G[v]) {
		if (visited[val] == 0) {
			bool res = Explore(val, G, visited, color, (!col));
			if (!res) {
				return 0;
			}
		}
		else {
			if (color[v] == color[val]) {
				return 0;
			}
		}
	}
	return 1;
}


bool Bipartite(size_t n, list<size_t>*& G) {

	bool * visited = new bool[n + 1];
	bool * color = new bool[n + 1];

	for (size_t i = 1; i <= n; ++i) {
		visited[i] = 0;
		color[i] = 0;
	}

	for (size_t i = 1; i <= n; ++i) {
		if (visited[i] == 0) {
			bool res = Explore(i, G, visited, color, 1);
			if (!res) {
				return 0;
			}
		}
	}

	return 1;
}

int main()
{
	size_t n = 0, m = 0;
	cin >> n >> m;

	list<size_t>* G = new list<size_t>[n + 1];
	size_t u = 0, v = 0;

	for (size_t i = 0; i < m; ++i) {
		cin >> u >> v;
		G[u].push_back(v);
		G[v].push_back(u);
	}

	cout << Bipartite(n, G);
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
