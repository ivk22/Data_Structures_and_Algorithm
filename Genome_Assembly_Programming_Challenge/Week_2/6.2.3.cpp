// 6.2.3.cpp : This file contains the 'main' function. Program execution begins and ends there.
//


#include <iostream>
#include <vector>
#include <list>
#include <string>
#include <cmath>
#include <math.h>
using namespace std;


list<size_t> Eulerian_cycle(vector<list<size_t>>& G,
	size_t m) {

	size_t start_vertex = 0;
	for (size_t i = 0; i < G.size(); +i) {
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
			path.push_back(path.front());
			return path;
		}

		while (!G[cycle.front()].size()) {
			size_t temp = cycle.front();
			cycle.pop_front();
			cycle.push_back(temp);
		}

		start_vertex = cycle.front();

		path.splice(path.end(), cycle);

	}

}

void Init(string &s,size_t x,size_t k) {

	for (size_t i = 0; i < k; ++i) {
		s.push_back((x % 2)+'0');
		x = (x >> 1);
	}

}


void Add(string &s, size_t start, size_t next, size_t k) {
	
	start = (start >> 1);
	size_t bits = 1;
	while (true) {
		if ((start&next) == start || !start) break;
		start = (start >> 1);
		++bits;
	}
	next = (next >> (k - bits));

	Init(s, next, bits);
}


int main()
{
	size_t k = 0;
	cin >> k;
	
	size_t n_subsets = pow(2, k), n_mers = pow(2, k-1);

	vector<list<size_t>> G(n_mers);

	for (size_t i = 0; i < n_subsets; ++i) {
		size_t left = 0,right =0;

		for (size_t j = 0; j < k - 1; ++j) {
			if (j) {
				if ((1 << j) & i) {
					left += (1 << j); 
					right += (1 << j);
				}
			}
			else {
				if ((1 << j) & i) left += (1 << j);
			}
		}
		if ((1 << (k - 1)) & i) right += (1 << (k - 1));

		right = (right >> 1);

		G[left].push_back(right);
	}

	list<size_t> lst = Eulerian_cycle(G, n_subsets);

	size_t start = lst.front();
	lst.pop_front();
	string s;
	s.reserve(n_subsets*k);

	Init(s,start,k-1);

	while (!lst.empty()) {
		size_t next = lst.front();
		lst.pop_front();
		Add(s,start, next,k-1);
		start = next;
	}

	cout << s;

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
