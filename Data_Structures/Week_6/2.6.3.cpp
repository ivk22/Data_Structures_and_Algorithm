// 2.6.2.cpp : This file contains the 'main' function. Program execution begins and ends there.
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

using namespace std;


pair<int64_t, int64_t> InOrder(int64_t * arr, int64_t * left,
	int64_t * right, int64_t root, bool & res) {

	if (left[root] == -1) {
		if (right[root] == -1) {
			return pair<int64_t, int64_t>{arr[root], arr[root]};
		}

		pair<int64_t, int64_t> right_pair = InOrder(arr, left, right, right[root], res);

		if (res) {
			return pair<int64_t, int64_t>{};
		}

		if (arr[root] > right_pair.first) {
			res = 1;
			return pair<int64_t, int64_t>{};
		}

		return pair<int64_t, int64_t>{arr[root], right_pair.second};
	}
	if (right[root] == -1) {
		pair<int64_t, int64_t> left_pair = InOrder(arr, left, right, left[root], res);

		if (res) {
			return pair<int64_t, int64_t>{};
		}

		if (arr[root] <= left_pair.second) {
			res = 1;
			return pair<int64_t, int64_t>{};
		}
		return pair<int64_t, int64_t>{left_pair.first, arr[root]};
	}

	pair<int64_t, int64_t> left_pair = InOrder(arr, left, right, left[root], res);
	pair<int64_t, int64_t> right_pair = InOrder(arr, left, right, right[root], res);

	if (res) {
		return pair<int64_t, int64_t>{};
	}

	if (arr[root] <= left_pair.second || arr[root] > right_pair.first) {
		res = 1;
		return pair<int64_t, int64_t>{};
	}

	return pair<int64_t, int64_t> {left_pair.first, right_pair.second};

}


int main()
{
	size_t n = 0;
	cin >> n;
	if (n == 0) {
		cout << "CORRECT";
	}
	else {
		int64_t * arr = new int64_t[n];
		int64_t * parents = new int64_t[n];

		int64_t * left = new int64_t[n];
		int64_t * right = new int64_t[n];


		for (int64_t i = 0; i < n; ++i) {
			parents[i] = -1;
			left[i] = -1;
			right[i] = -1;
		}
		string name;
		getline(cin, name);
		for (int64_t i = 0; i < n; ++i) {
			getline(cin, name);
			stringstream ss(name);
			istream_iterator<string> begin(ss);
			istream_iterator<string> end;
			vector<string> vstrings(begin, end);
			vector<int64_t> v(3);
			v[0] = stoi(vstrings[0]);
			v[1] = stoi(vstrings[1]);
			v[2] = stoi(vstrings[2]);
			arr[i] = v[0];
			parents[v[1]] = i;
			parents[v[2]] = i;
			left[i] = v[1];
			right[i] = v[2];
		}

		int64_t root = 0;
		for (int64_t i = 0; i < n; ++i) {
			if (parents[i] == -1) {
				root = i;
				break;
			}
		}

		bool res = 0;

		InOrder(arr, left, right, root, res);
		if (res) {
			cout << "INCORRECT";
		}
		else {
			cout << "CORRECT";
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
