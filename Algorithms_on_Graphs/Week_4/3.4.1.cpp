// 3.4.1.cpp : This file contains the 'main' function. Program execution begins and ends there.
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

class Heap {
	pair<size_t, size_t> * arr;
	size_t * parent;
	int64_t * positions;
	size_t size;

	void Swap(size_t x, size_t y) {
		pair<size_t, size_t> temp = arr[x];
		arr[x] = arr[y];
		arr[y] = temp;
		positions[arr[x].second] = x;
		positions[arr[y].second] = y;
	}

	void SiftUp(size_t x) {
		while (arr[parent[x]] > arr[x]) {
			Swap(x, parent[x]);
			x = parent[x];
		}
	}

	void SiftDown(size_t x) {
		if (2 * x + 1 < size) {
			if (2 * x + 2 < size) {
				if (arr[x] > arr[2 * x + 1]|| arr[x] > arr[2 * x + 2]) {
					if (arr[2 * x + 1] <= arr[2 * x + 2]) {
						Swap(x, 2 * x + 1);
						SiftDown(2 * x + 1);
					} else{
						Swap(x, 2 * x + 2);
						SiftDown(2 * x + 2);
					}
				}
			}
			if (arr[x] > arr[2 * x + 1]) {
				Swap(x, 2 * x + 1);
				SiftDown(2 * x + 1);
			}
		}
	}


public:
	Heap(size_t n) {
		size = 0;
		arr = new pair<size_t, size_t>[n];
		parent = new size_t[n];
		positions = new int64_t[n];
		for (size_t i = 0; i < n; ++i) {
			positions[i] = -1;
		}
	}

	void Add(pair<size_t, size_t> x) {
		arr[size] = x;
		positions[x.second] = size;
		if (Is_Empty()) {
			parent[size] = size;
			++size;
		}
		else {
			parent[size] = (size-1)/2;
			SiftUp(size);
			++size;
		}
	}

	bool Is_Empty() {
		return (size == 0);
	}

	pair<size_t, size_t> ExtractMin() {
		if (!Is_Empty()) {
			pair<size_t, size_t> val = arr[0];
			positions[arr[0].second] = -1;

			arr[0] = arr[size - 1];

			positions[arr[0].second] = 0;

			--size;
			SiftDown(0);
			return val;
		}
	}

	size_t Top() {
		if (!Is_Empty()) {
			return arr[0].first;
		}
		
	}

	void ChangePriority(pair<size_t, size_t> x) {
		if (positions[x.second] == -1) {
			Add(x);
		}
		else {
			if (arr[positions[x.second]] > x) {
				arr[positions[x.second]] = x;
				SiftUp(positions[x.second]);
			}
			else {
				arr[positions[x.second]] = x;
				SiftDown(positions[x.second]);
			}
		}
	}

};


int64_t Dijkstra(size_t n, list<pair<size_t, 
	size_t>>*& G, size_t u, size_t v) {

	uint64_t inf = std::numeric_limits<uint64_t>::max();

	uint64_t * dist = new uint64_t[n+1];



	for (int i = 1; i <= n; ++i) {
		dist[i] = inf;

	}

	dist[u] = 0;
	Heap H(n);
	H.Add(pair<size_t, size_t>{0,u-1});


	pair<size_t, size_t> cur;
	size_t temp;
	while (!H.Is_Empty()) {
		size_t min_dist=0;

		min_dist = H.Top();

		while (H.Top() == min_dist && !H.Is_Empty()) {
			cur = H.ExtractMin();
			temp = cur.second;
			if (temp == v-1) {
				return cur.first;
			}
			for (const auto& val : G[temp+1]) {
				if (dist[val.second] > dist[temp + 1] + val.first) {
					dist[val.second] = dist[temp + 1] + val.first;
					H.ChangePriority(pair<size_t, size_t>{dist[val.second], val.second-1});
				}
			}

		}

	}
	return -1;
}


int main()
{
	size_t n = 0, m = 0;
	cin >> n >> m;

	list<pair<size_t, size_t>>* G = new list<pair<size_t, size_t>>[n + 1];
	size_t u = 0, v = 0, c=0;

	for (size_t i = 0; i < m; ++i) {
		cin >> u >> v >> c;
		G[u].push_back(pair<size_t, size_t>{ c, v});
	}
	cin >> u >> v;


	cout << Dijkstra(n, G, u, v);

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
