// 3.4.2.cpp : This file contains the 'main' function. Program execution begins and ends there.
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

bool BFS(size_t n, list<pair<int, size_t>>*& G,
	size_t u, int*& dist, bool*& visited) {
	bool res = 0;

	bool* inner_visited = new bool[n + 1];

	for (int i = 1; i <= n; ++i) {
		inner_visited[i] = 0;
	}

	queue<size_t> q;
	q.push(u);
	inner_visited[u] = 1;
	while (!q.empty()) {
		size_t elem = q.front();
			visited[elem] = 1;
			for (const auto & val : G[elem]) {
				if (dist[val.second] > dist[elem] + val.first) {
					dist[val.second] = dist[elem] + val.first;
					res = 1;
				}
				if (!inner_visited[val.second]) {
					inner_visited[val.second] = 1;
					q.push(val.second);
				}
			}

		q.pop();
		
	}
	delete[] inner_visited;
	return res;
}


bool Check_Cycle(size_t n, list<pair<int, size_t>>*& G) {
	bool* visited = new bool[n + 1];
	int* dist = new int[n+1];
	int mx = numeric_limits<int>::max();
	for (int i = 1; i <= n; ++i) {
		visited[i] = 0;
	}

	for (size_t i = 1; i <= n; ++i) {
		if (!visited[i]) {
			for (int j = 1; j <= n; ++j) {
				dist[j] = mx;
			}
			dist[i] = 0;
			int cnt = 0;
			while (true) {
				bool res = BFS(n, G, i, dist, visited);
				++cnt;
				if (cnt == n && res) {
					return 1;
				}
				if (!res) {
					break;
				}
			}
		}
	}
	return 0;
}

int main()
{


	size_t n = 0, m = 0;
	cin >> n >> m;

	list<pair<int, size_t>>* G = new list<pair<int, size_t>>[n + 1];
	size_t u = 0, v = 0;
	int c = 0;

	for (size_t i = 0; i < m; ++i) {
		cin >> u >> v >> c;
		G[u].push_back(pair<int, size_t>{c, v});
	}

	cout << Check_Cycle(n, G);
	
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
