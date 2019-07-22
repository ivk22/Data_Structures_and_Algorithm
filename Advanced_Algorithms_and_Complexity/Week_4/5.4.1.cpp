// ConsoleApplication4.cpp : This file contains the 'main' function. Program execution begins and ends there.
//


#include <iostream>
#include <vector>
#include <list>
#include <cmath>
#include <math.h>

using namespace std;

int neg(int a, int V) {

	if (a <= V) {
		return a+V;
	}
	return ((a % V) ? (a % V): V);

}


void Explore(size_t i,vector<list<size_t>>& G, 
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
	int V = assign.size()-1;
	
	if (i > V) {
		if (assign[neg(i, V)]==-1) assign[neg(i, V)] = 0;
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
	size_t cc = 0,p=0;

	for (size_t i = 1; i < G.size(); ++i) {
		if (!visited[i]) {
			Explore(i, GR, post, visited, p);
		}
	}

	visited = vector<bool>(visited.size(),0);

	for (size_t i = post.size() - 1; i > 0; --i) {
		if (!visited[post[i]]) {
			Explore2(post[i], G, SCC, visited, cc);
			++cc;
		}
	}

}

int main()
{
	size_t V = 0, C = 0;
	cin >> V >> C;

	vector<list<size_t>> G(2*V+1, list<size_t>());

	vector<list<size_t>> GR(2 * V + 1, list<size_t>());

	for (size_t i = 0; i < C; ++i) {
		int u = 0, v = 0;

		cin >> u >> v;

		if (u < 0) u = V + abs(u);
		if (v < 0) v = V + abs(v);
		G[neg(u,V)].push_back(v);
		G[neg(v, V)].push_back(u);
		GR[v].push_back(neg(u, V));
		GR[u].push_back(neg(v, V));

	}

	vector<size_t> SCC(2 * V + 1,0);
	vector<size_t> post(2 * V + 1, 0);

	vector<bool> visited(2 * V + 1, false);

	DFS(G,GR,SCC,post,visited);

	bool sat = true;

	for (size_t i = 1; i <= V; ++i) {
		if (SCC[i] == SCC[neg(i, V)]) {
			sat = false;
			cout << "UNSATISFIABLE";
			break;
		}
	}
	if (sat) {

		vector<int> assign(V + 1 ,-1);
		visited=vector<bool>(visited.size(),0);
		for (size_t i = post.size() - 1; i < post.size(); --i) {
			if (!visited[post[i]]) {
				Explore3(post[i], G, assign, visited);
			}
		}
		cout << "SATISFIABLE"<<endl;
		for (int i = 1; i < assign.size(); ++i) {
			if (!assign[i]) {
				cout << -i << (i< assign.size()-1 ? " ":"");
			}
			else {
				cout << i << (i < assign.size() - 1 ? " " : "");
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
