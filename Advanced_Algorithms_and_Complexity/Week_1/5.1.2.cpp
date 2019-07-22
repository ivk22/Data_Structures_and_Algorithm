// 5.1.2.cpp : This file contains the 'main' function. Program execution begins and ends there.
//


#include <iostream>
#include <list>
#include <queue>
#include <stack>
#include <tuple>
#include <vector>
#include <string>
using namespace std;

uint64_t FindPath(vector<pair<pair<size_t, size_t>,
	pair<size_t, size_t>>>*& GR, size_t n) {
	uint64_t mn = 0;

	pair<pair<size_t, size_t>, pair<size_t, size_t>>** parent =
		new pair<pair<size_t, size_t>, pair<size_t, size_t>>*[n + 1];

	bool* visited = new bool[n + 1];

	for (size_t i = 1; i <= n; ++i) {
		visited[i] = 0;
	}

	queue<size_t> q;
	q.push(1);
	visited[1] = 1;

	while (!q.empty()) {
		size_t cur = q.front();
		for (auto& val : GR[cur]) {
			if (!visited[val.first.second] && val.second.first) {
				visited[val.first.second] = 1;
				parent[val.first.second] = &val;
				q.push(val.first.second);
				if (val.first.second == n) {
					cur = n;
					while (cur != 1) {
						auto par = parent[cur];
						if (!mn || par->second.first < mn) {
							mn = par->second.first;
						}
						cur = par->first.first;
					}
					cur = n;
					while (cur != 1) {
						auto par = parent[cur];
						par->second.first -= mn;

						GR[cur][par->second.second].second.first += mn;

						cur = par->first.first;
					}
					delete[] visited;
					delete[] parent;
					return mn;
				}
			}
		}
		q.pop();
	}

	delete[] visited;
	delete[] parent;
	return mn;
}

uint64_t Edmonds_Karp(vector<pair<pair<size_t, size_t>,
	pair<size_t, size_t>>>*& GR, size_t n) {
	uint64_t res = 0;
	while (true) {
		uint64_t add = FindPath(GR, n);
		res += add;
		if (!add) {
			return res;
		}
	}


}


int main()
{
	size_t n = 0, m = 0;
	cin >> n >> m;
	list<pair<pair<size_t, size_t>, pair<size_t, size_t>>>* G =
		new list<pair< pair<size_t, size_t>, pair<size_t, size_t>>>[n+m+3];
	

	for (size_t i = 2; i <= n + 1; ++i) {

		G[1].push_back({ {1,i},{1,G[i].size()} });
		G[i].push_back({ {i,1},{0,G[1].size() - 1} });

		for (size_t j = n+2; j <= n+m+1; ++j) {
			size_t present = 0;

			cin >> present;
			if (present) {
				G[i].push_back({ {i,j},{present,G[j].size()} });
				G[j].push_back({ {j,i},{0,G[i].size() - 1} });
			}
		}
	}

	for (size_t j = n + 2; j <= n + m + 1; ++j) {
		G[j].push_back({ {j,n + m + 2},{1,G[n + m + 2].size()} });
		G[n + m + 2].push_back({ {n + m + 2,j},{0,G[j].size() - 1} });
	}




	vector<pair<pair<size_t, size_t>, pair<size_t, size_t>>>* GR =
		new vector<pair< pair<size_t, size_t>, pair<size_t, size_t>>>[n + m + 3];
	for (size_t i = 1; i <= n+m+2; ++i) {
		GR[i] = vector<pair<pair<size_t, size_t>,
			pair<size_t, size_t>>>(G[i].begin(), G[i].end());
	}
	delete[] G;

	uint64_t res = Edmonds_Karp(GR, n + m + 2);

	for (size_t i = 2; i <= n + 1; ++i) {
		bool b = 1;
		for (const auto& val : GR[i]) {
			if (val.first.second <= n + m + 1 && val.first.second >= n + 2 && !val.second.first) {
				b = 0;
				cout << val.first.second- n-1 << " ";
				break;
			}
		}
		if (b) {
			cout << -1 << " ";
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
