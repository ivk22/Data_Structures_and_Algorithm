// 5.4.4.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include <list>
#include <queue>
#include <string>
#include <sstream>
#include <map>
#include <set>
#include <limits>
#include <limits.h>
#include <cmath>
#include <math.h>

using namespace std;

int neg(int a, int V) {

	if (a <= V) {
		return a + V;
	}
	return ((a % V) ? (a % V) : V);

}


void Explore(size_t i, vector<list<size_t>>& G,
	vector<size_t>& post, vector<bool>& visited, size_t& p) {
	visited[i] = 1;
	for (const auto& val : G[i]) {
		if (!visited[val]) {
			visited[val] = 1;
			Explore(val, G, post, visited, p);
		}
	}

	++p;
	post[p] = i;
}

void Explore2(size_t i, vector<list<size_t>>& G,
	vector<size_t>& SCC, vector<bool>& visited, size_t& cc) {
	visited[i] = 1;
	SCC[i] = cc;
	for (const auto& val : G[i]) {
		if (!visited[val]) {
			visited[val] = 1;
			Explore2(val, G, SCC, visited, cc);
		}
	}
}


void Explore3(size_t i, vector<list<size_t>>& G,
	vector<int>& assign, vector<bool>& visited) {
	visited[i] = 1;
	int V = assign.size() - 1;

	if (i > V) {
		if (assign[neg(i, V)] == -1) assign[neg(i, V)] = 0;
	}
	else {
		if (assign[i] == -1) assign[i] = 1;
	}
	for (const auto& val : G[i]) {
		if (!visited[val]) {
			visited[val] = 1;
			Explore3(val, G, assign, visited);
		}
	}
}

void DFS(vector<list<size_t>>& G, vector<list<size_t>>& GR,
	vector<size_t>& SCC, vector<size_t>& post,
	vector<bool>& visited) {
	size_t cc = 0, p = 0;

	for (size_t i = 1; i < G.size(); ++i) {
		if (!visited[i]) {
			Explore(i, GR, post, visited, p);
		}
	}

	visited = vector<bool>(visited.size(), 0);

	for (size_t i = post.size() - 1; i > 0; --i) {
		if (!visited[post[i]]) {
			Explore2(post[i], G, SCC, visited, cc);
			++cc;
		}
	}

}



int main()
{
	size_t n = 0, m = 0;
	cin >> n >> m;

	map<char, size_t> mp;

	mp['R'] = 1;
	mp['G'] = 2;
	mp['B'] = 3;

	string col;
	getline(cin, col);
	getline(cin, col);


	size_t V = 3 * n;

	vector<list<size_t>> G(2* V + 1, list<size_t>());

	vector<list<size_t>> GR(2 * V + 1, list<size_t>());

	size_t p = 0;
	for (size_t i = 1; i <= V;i+=3) {

		size_t var = mp[col[p]];

		++p;

		if (var == 1) {
			size_t u = i, v = i + 1, k = i + 2;

			G[u].push_back(neg(u, V));
			G[neg(v, V)].push_back(k);
			G[neg(k, V)].push_back(v);


			G[v].push_back(neg(k, V));
			G[k].push_back(neg(v, V));


			GR[neg(u, V)].push_back(u);
			GR[k].push_back(neg(v, V));
			GR[v].push_back(neg(k, V));

			GR[neg(k, V)].push_back(v);
			GR[neg(v, V)].push_back(k);


		}

		if (var == 2) {
			size_t u = i, v = i + 1, k = i + 2;


			G[v].push_back(neg(v, V));
			G[neg(u, V)].push_back(k);
			G[neg(k, V)].push_back(u);

			G[u].push_back(neg(k, V));
			G[k].push_back(neg(u, V));


			GR[neg(v, V)].push_back(v);
			GR[k].push_back(neg(u, V));
			GR[u].push_back(neg(k, V));


			GR[neg(k, V)].push_back(u);
			GR[neg(u, V)].push_back(k);

		}

		if (var == 3) {
			size_t u = i, v = i + 1, k = i + 2;

			G[k].push_back(neg(k, V));
			G[neg(v, V)].push_back(u);
			G[neg(u, V)].push_back(v);

			G[u].push_back(neg(v, V));
			G[v].push_back(neg(u, V));

			GR[neg(k, V)].push_back(k);
			GR[u].push_back(neg(v, V));
			GR[v].push_back(neg(u, V));

			GR[neg(v, V)].push_back(u);
			GR[neg(u, V)].push_back(v);

		}

	}


	for (size_t i = 1; i <= m; ++i) {
		size_t u = 0, v = 0;
		cin >> u >> v;

		size_t s1 = 3 * (u - 1), s2 = 3*(v-1);


		size_t var11 = neg(s1 + 1, V), var12 = neg(s1 + 2, V), var13 = neg(s1 + 3, V);
		size_t var21 = neg(s2 + 1, V), var22 = neg(s2 + 2, V), var23 = neg(s2 + 3, V);


		G[neg(var11, V)].push_back(var21);
		G[neg(var21, V)].push_back(var11);

		G[neg(var12, V)].push_back(var22);
		G[neg(var22, V)].push_back(var12);


		G[neg(var13, V)].push_back(var23);
		G[neg(var23, V)].push_back(var13);


		GR[var11].push_back(neg(var21, V));
		GR[var21].push_back(neg(var11, V));

		GR[var12].push_back(neg(var22, V));
		GR[var22].push_back(neg(var12, V));

		GR[var13].push_back(neg(var23, V));
		GR[var23].push_back(neg(var13, V));

	}




	vector<size_t> SCC(2 * V + 1, 0);
	vector<size_t> post(2 * V + 1, 0);

	vector<bool> visited(2 * V + 1, false);

	DFS(G, GR, SCC, post, visited);

	bool sat = true;

	for (size_t i = 1; i <= V; ++i) {
		if (SCC[i] == SCC[neg(i, V)]) {
			sat = false;
			cout << "Impossible";
			break;
		}
	}
	if (sat) {

		vector<int> assign(V + 1, -1);
		visited = vector<bool>(visited.size(), 0);
		for (size_t i = post.size() - 1; i < post.size(); --i) {
			if (!visited[post[i]]) {
				Explore3(post[i], G, assign, visited);
			}
		}

		
		for (int i = 1; i < assign.size(); i+=3) {
			if (assign[i]) {
				cout << 'R';
			}
			if (assign[i+1]) {
				cout << 'G';
			}
			if (assign[i + 2]) {
				cout << 'B';
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
