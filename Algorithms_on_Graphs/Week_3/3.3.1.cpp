// 3.3.1.cpp : This file contains the 'main' function. Program execution begins and ends there.
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

int L(size_t n, list<size_t>*& G, size_t u, size_t v) {
	int* dist = new int[n + 1];
	for (size_t i = 0; i <= n; ++i) {
		dist[i] = -1;
	}
	dist[u] = 0;
	queue<size_t> q;
	q.push(u);
	while (!q.empty()) {
		size_t elem = q.front();
		for (const auto & val : G[elem]) {
			if (dist[val] == -1) {
				if (val == v) {
					return dist[elem] + 1;
				}
				dist[val] = dist[elem] + 1;
				q.push(val);
			}
		}
		q.pop();
	}
	return dist[v];
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

	cin >> u >> v;
	cout << L(n, G,u,v);




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
