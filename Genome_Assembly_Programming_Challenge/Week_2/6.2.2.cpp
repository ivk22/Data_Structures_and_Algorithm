// 6.2.2.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>
#include <list>
using namespace std;

list<size_t> Eulerian_cycle(vector<list<size_t>>& G,
	vector<vector<size_t>>& InOut, size_t m) {
	for (size_t i = 1; i < InOut.size(); ++i) {
		if (InOut[i][0] != InOut[i][1]) {

			return list<size_t>();
		}
	}

	size_t start_vertex = 0;
	for (size_t i = 1; i < G.size(); +i) {
		if (G.size()) {
			start_vertex = i;
			break;
		}
	}


	list<size_t> path;


	while (true) {

		list<size_t> cycle;
		
		cycle.push_back(start_vertex);

		while (true) {
			size_t next = G[start_vertex].back();
			G[start_vertex].pop_back();
			if (next == cycle.front()) {
				break;
			}
			cycle.push_back(next);
			start_vertex = next;
		}

		if (path.size() + cycle.size() == m) {
			path.splice(path.end(), cycle);
			return path;
		}

		while (!G[cycle.front()].size()) {
			size_t temp = cycle.front();
			cycle.pop_front();
			cycle.push_back(temp);
		}

		start_vertex=cycle.front();

		path.splice(path.end(), cycle);

	}

}



int main()
{
	size_t n = 0, m = 0;
	cin >> n >> m;

	vector<list<size_t>> G(n+1);

	vector<vector<size_t>> InOut(n + 1, vector<size_t>(2,0));

	for (size_t i = 0; i < m; ++i) {
		size_t u = 0, v = 0;
		cin >> u >> v;

		if (u != v) {
			++InOut[u][0];
			++InOut[v][1];
		}

		G[u].push_back(v);

	}



	list<size_t> lst= Eulerian_cycle(G, InOut,m);
	
	if (lst.size()) {
		cout << 1 << endl;
		for (const auto & val : lst) {
			cout << val << " ";
		}
	}
	else {
		cout << 0;
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
