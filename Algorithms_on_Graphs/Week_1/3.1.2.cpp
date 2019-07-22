// 2.6.6.cpp : This file contains the 'main' function. Program execution begins and ends there.
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


void Explore(size_t v, bool*& visited, list<size_t>*& arr) {
	visited[v] = 1;
	for (const auto & val : arr[v]) {
		if (visited[val] == 0) {
			Explore(val, visited, arr);
		}
	}
}


size_t DFS(size_t n, bool*& visited, list<size_t>*& arr) {
	
	for (size_t i = 1; i <= n; ++i) {
		visited[i] = 0;
	}
	size_t cc = 0;

	for (size_t i = 1; i <= n; ++i) {
		if (visited[i] == 0) {
			Explore(i, visited, arr);
			++cc;
		}
	}
	return cc;

}

int main()
{
	size_t n = 0, m = 0;
	cin >> n >> m;

	list<size_t>* arr = new list<size_t>[n + 1];

	bool* visited = new bool[n + 1];

	size_t v1 = 0, v2 = 0;

	for (size_t i = 0; i < m; ++i) {
		cin >> v1 >> v2;
		arr[v1].push_back(v2);
		arr[v2].push_back(v1);
	}

	cout << DFS(n, visited, arr);


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
