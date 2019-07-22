// 2.3.4.cpp : This file contains the 'main' function. Program execution begins and ends there.
//


#include <iostream>
#include <algorithm>
#include <queue>
using namespace std;


class Disjoint_Sets {
public:
	Disjoint_Sets(size_t n) {
		rank = new size_t[n];
		parent = new size_t[n];
		mx = 0;
	}
	void MakeSet(size_t i,size_t rk) {
		rank[i] = rk;
		parent[i] = i;
		if (rk > mx) {
			mx = rk;
		}
	}
	size_t Find(size_t i) {
		if (i != parent[i]) {
			parent[i] = Find(parent[i]);
		}
		return parent[i];
	}
	void Union(size_t i, size_t j) {
		size_t parent_i = Find(i);
		size_t parent_j= Find(j);
		if (parent_i == parent_j) {
			return;
		}
		if (rank[parent_i] >= rank[parent_j]) {
			parent[parent_j] = parent_i;
			rank[parent_i] += rank[parent_j];
		}
		else {
			parent[parent_i] = parent_j;
			rank[parent_j] += rank[parent_i];
		}

		mx = max(max(rank[parent_j], rank[parent_i]), mx);
	}

	size_t GetMx() {
		return mx;
	}

private:
	size_t* rank;
	size_t* parent;
	size_t mx;
};



int main()
{
	size_t n = 0,m=0,temp=0;
	cin >> n >> m;

	Disjoint_Sets ds(n);
	for (size_t i = 0; i < n; ++i) {
		cin >> temp;
		ds.MakeSet(i, temp);
	}

	size_t i = 0, j = 0;
	queue <size_t> q;
	for (size_t k = 0; k < m; ++k) {
		cin >> i >> j;
		--i;
		--j;
		ds.Union(i, j);
		q.push(ds.GetMx());
	}
	while (!q.empty()) {
		cout << q.front() << endl;
		q.pop();
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
