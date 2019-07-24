// 5.1.1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//


#include <iostream>
#include <list>
#include <queue>
#include <stack>
#include <tuple>
#include <vector>
#include <map>
using namespace std;

uint64_t FindPath(vector<pair<pair<size_t, size_t>,
	pair<size_t, size_t>>>*& GR, size_t n) {
	uint64_t mn = 0;

	pair<pair<size_t, size_t>, pair<size_t, size_t>>** parent =
		new pair<pair<size_t, size_t>, pair<size_t, size_t>>*[n + 1];

	bool* visited = new bool[n + 1];

	for (size_t i = 0; i <= n; ++i) {
		visited[i] = 0;
	}

	queue<size_t> q;
	q.push(0);
	visited[0] = 1;

	while (!q.empty()) {
		size_t cur = q.front();
		for (auto& val : GR[cur]) {
			if (!visited[val.first.second] && val.second.first) {
				visited[val.first.second] = 1;
				parent[val.first.second] = &val;
				q.push(val.first.second);
				if (val.first.second == n) {
					cur = n;
					while (cur != 0) {
						auto par = parent[cur];
						if (!mn || par->second.first < mn) {
							mn = par->second.first;
						}
						cur = par->first.first;
					}
					cur = n;
					while (cur != 0) {
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
		new list<pair< pair<size_t, size_t>, pair<size_t, size_t>>>[n + 2];

	vector<int> demand(n+1,0);

	vector<size_t> edges(m, 0);

	map<size_t,pair<size_t, size_t>> mp;

	for (size_t i = 0; i < m; ++i) {
		size_t u = 0, v = 0,l=0, c = 0;
		cin >> u >> v >> l >> c;
		edges[i] += l;

		demand[v] -= l;
		demand[u] += l;

		if (u != v && c > l) {
			
			G[u].push_back({ {u,v},{c-l,G[v].size()} });
			G[v].push_back({ {v,u},{0,G[u].size() - 1} });

			mp[i] = { v, G[v].size()-1};

		}
		else {
			mp[i] = { 0, 0 };
		}

	}





	size_t D = 0;

	for (size_t i = 1; i <= n; ++i) {
		if (demand[i] > 0) {
			D += demand[i];
			G[i].push_back({ {i,n + 1},{demand[i],G[n + 1].size()} });
			G[n + 1].push_back({ {n + 1,i},{0,G[i].size() - 1} });
		}
		if (demand[i] < 0) {
			G[0].push_back({ {0,i},{abs(demand[i]),G[i].size()} });
			G[i].push_back({ {i,0},{0,G[0].size() - 1} });
		}
	}


	vector<pair<pair<size_t, size_t>, pair<size_t, size_t>>>* GR =
		new vector<pair< pair<size_t, size_t>, pair<size_t, size_t>>>[n + 2];
	for (size_t i = 0; i <= n+1; ++i) {
		GR[i] = vector<pair<pair<size_t, size_t>,
			pair<size_t, size_t>>>(G[i].begin(), G[i].end());
	}

	delete[] G;

	uint64_t res =  Edmonds_Karp(GR, n+1);




	
	if (res == D) {
		cout << "YES" << endl;
		for (size_t i = 0; i < m; ++i) {
			if (mp[i].first!=0) {
				edges[i]+=GR[mp[i].first][mp[i].second].second.first;
			}
			cout << edges[i] << endl;
		}
	}
	else {
		cout << "NO" << endl;
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
