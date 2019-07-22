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

bool BFS(size_t n, list<pair<int64_t, size_t>>*& G,
	size_t u, int64_t*& dist) {
	bool res = 0;

	bool* inner_visited = new bool[n + 1];

	for (size_t i = 1; i <= n; ++i) {
		inner_visited[i] = 0;
	}

	queue<size_t> q;
	q.push(u);
	inner_visited[u] = 1;
	while (!q.empty()) {
		size_t elem = q.front();

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



bool BFS_(size_t n, list<pair<int64_t, size_t>>*& G,
	size_t u, int64_t*& dist, list<size_t>& changed) {
	bool res = 0;

	bool* inner_visited = new bool[n + 1];
	bool* list_visited = new bool[n + 1];

	for (size_t i = 1; i <= n; ++i) {
		inner_visited[i] = 0;
		list_visited[i] = 0;
	}

	queue<size_t> q;
	q.push(u);
	inner_visited[u] = 1;
	while (!q.empty()) {
		size_t elem = q.front();

		for (const auto & val : G[elem]) {
			if (dist[val.second] > dist[elem] + val.first) {
				dist[val.second] = dist[elem] + val.first;
				res = 1;
				if (!list_visited[val.second]) {
					list_visited[val.second] = 1;
					changed.push_back(val.second);
				}

			}
			if (!inner_visited[val.second]) {
				inner_visited[val.second] = 1;
				q.push(val.second);
			}
		}

		q.pop();

	}
	delete[] inner_visited;
	delete[] list_visited;
	return res;
}



void Explore(size_t u, list<pair<int64_t, size_t>>*& G, bool*& visited) {
	queue<size_t> q;
	q.push(u);
	visited[u] = 1;
	while (!q.empty()) {
		size_t temp = q.front();
		for (const auto & val : G[temp]) {
			if (!visited[val.second]) {
				visited[val.second] = 1;
				q.push(val.second);
			}
		}
		q.pop();
	}
}

void Check_Cycle(int64_t*& dist,size_t n,
	list<pair<int64_t, size_t>>*& G, size_t u) {

	dist[u] = 0;


	bool res = 1;
	for (size_t i =1; i<=n-1;++i) {
		bool res = BFS(n, G, u, dist);
		if (!res) {
			break;
		}
	}
	if (res) {
		list<size_t> changed;
		bool* visited = new bool[n + 1];
		for (size_t i = 1; i <= n; ++i) {
			visited[i] = 0;
		}
		BFS_(n, G, u, dist, changed);
		for (const auto& val : changed) {
			if (!visited[val]) {
				Explore(val, G, visited);
			}
		}

		int64_t mn = numeric_limits<int64_t>::min();

		for (size_t i = 1; i <= n; ++i) {
			if (visited[i]) {
				dist[i] = mn;
			}
		}
	}

}

int main()
{


	size_t n = 0, m = 0;
	cin >> n >> m;

	list<pair<int64_t, size_t>>* G = new list<pair<int64_t, size_t>>[n + 1];
	size_t u = 0, v = 0;
	int64_t c = 0;

	for (size_t i = 0; i < m; ++i) {
		cin >> u >> v >> c;
		G[u].push_back(pair<int64_t, size_t>{c, v});
	}

	cin >> u;
	int64_t* dist = new int64_t[n + 1];

	int64_t mx = numeric_limits<int64_t>::max();

	int64_t mn = numeric_limits<int64_t>::min();
	for (size_t j = 1; j <= n; ++j) {
		dist[j] = mx;

	}

	Check_Cycle(dist,n, G,u);

	for (size_t i = 1; i <= n; ++i) {
		if (dist[i] == mx) {
			cout << "*" << endl;
		}
		else if (dist[i] == mn) {
			cout << "-" << endl;
		}
		else {
			cout << dist[i] << endl;
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
