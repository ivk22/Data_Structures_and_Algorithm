// 3.2.1.cpp : This file contains the 'main' function. Program execution begins and ends there.
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


void Explore(size_t v, bool*& visited, 
	list<size_t>*& arr, 
	size_t& post_order, size_t*& post_orders) {
	visited[v] = 1;
	for (const auto & val : arr[v]) {
		if (visited[val] == 0) {
			
			Explore(val, visited, arr, post_order, post_orders);
		}

	}
	++post_order;
	post_orders[post_order] = v;
}

void Explore_cnt(size_t v, bool*& visited,
	list<size_t>*& arr) {
	visited[v] = 1;
	for (const auto & val : arr[v]) {
		if (visited[val] == 0) {

			Explore_cnt(val, visited, arr);
		}

	}

}


void DFS(size_t n,
	list<size_t>*& arr, size_t*& post_orders) {
	bool * visited = new bool[n + 1];
	for (size_t i = 1; i <= n; ++i) {
		visited[i] = 0;
		post_orders[i] = 0;
	}
	size_t post_order = 0;
	for (size_t i = 1; i <= n; ++i) {
		if (visited[i] == 0) {
			Explore(i, visited, arr, post_order, post_orders);
		}
	}
}



size_t SCC(size_t n,
	list<size_t>*& G, list<size_t>*& GR) {

	size_t* post_orders = new size_t[n + 1];
	DFS(n, GR, post_orders);

	bool * visited = new bool[n + 1];

	for (size_t i = 1; i <= n; ++i) {
		visited[i] = 0;
	}

	size_t post_order = 0;
	for (size_t i = n; i >= 1; --i) {
		if (visited[post_orders[i]] == 0) {
			++post_order;
			Explore_cnt(post_orders[i], visited, G);
			
		}
	}
	return post_order;
}


int main()
{
	size_t n = 0, m = 0;
	cin >> n >> m;

	list<size_t>* G = new list<size_t>[n + 1];
	list<size_t>* GR = new list<size_t>[n + 1];

	bool* visited = new bool[n + 1];

	

	size_t v1 = 0, v2 = 0;

	for (size_t i = 0; i < m; ++i) {
		cin >> v1 >> v2;
		G[v1].push_back(v2);
		GR[v2].push_back(v1);
	}

	cout << SCC(n,G,GR);

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
