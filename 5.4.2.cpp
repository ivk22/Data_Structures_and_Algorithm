// 5.4.2.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include <list>
#include <queue>
#include <limits>
#include <limits.h>

using namespace std;

int64_t CalcFun(size_t i, vector<int64_t>& D,
vector<list<size_t>>& childs, vector<size_t>& fun) {

	if (D[i] == -1) {

		int64_t m1 = fun[i];
		int64_t m2 = 0;

		for (const auto& ch : childs[i]) {
			m2 += CalcFun(ch, D, childs, fun);
			for (const auto& gch : childs[ch]) {
				m1 += CalcFun(gch,D,childs, fun);
			}
		}

		D[i] = max(m1,m2);

	}

	return D[i];
}


int main()
{
	size_t n = 0;
	cin >> n;
	vector<size_t> fun(n+1,0);

	for (size_t i = 1; i <= n; ++i) {
		cin >> fun[i];
	}

	vector<list<size_t>> G(n + 1, list<size_t>());

	for (size_t i = 1; i <= n-1; ++i) {
		size_t u = 0, v = 0;
		cin >> u >> v;
		G[u].push_back(v);
		G[v].push_back(u);
	}

	queue<size_t> q;
	q.push(1);

	vector<size_t> parent(n+1, 0);
	parent[1] = 1;

	vector<list<size_t>> childs(n + 1, list<size_t>());

	while (!q.empty()) {
		size_t cur = q.front();
		q.pop();

		for (const auto& val : G[cur]) {
			if (!parent[val]) {
				parent[val] = cur;
				q.push(val);
				childs[cur].push_back(val);
			}
			
		}
	}

	vector<int64_t> D(n + 1, -1);

	int64_t mx = 0;

	for (size_t i = 1; i <= n; ++i) {
		CalcFun(i, D, childs, fun);
		if (D[i] > mx) mx = D[i];
	}

	cout << mx;
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
