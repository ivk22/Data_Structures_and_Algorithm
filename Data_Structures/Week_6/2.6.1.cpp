// 2.5.1.cpp : This file contains the 'main' function. Program execution begins and ends there.
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


template <class T>
class Custom_Set {
	T key;
	size_t size,height;
	Custom_Set* left;
	Custom_Set* right;
	Custom_Set* parent;

	Custom_Set(T val, Custom_Set* par) {
		key = val;
		parent = par;
		size = 1;
		height = 1;
		left = nullptr;
		right= nullptr;
	}

	void Update_params() {
		if (left == nullptr) {
			if (right == nullptr) {
				size = 1;
				height = 1;
			}
			else {
				size = 1+ right->size;
				height= 1+ right->height;
			}
		}
		else {
			if (right == nullptr) {
				size = 1 + left->size;
				height = 1 + left->height;
			}
			else {
				size = 1 + right->size + left->size;
				height = 1 + max(right->height, left->height);
			}
		}
	}

public:
	Custom_Set() {
		key = NULL;
		parent = nullptr;
		size = 0;
		height = 0;
		left = nullptr;
		right = nullptr;
	}



	void Add(T x) {
		if (key == NULL) {
			key = x;
			size = 1;
			height = 1;
			return;
		}
		if (key == x) {
			return;
		}
		if (x < key) {
			if (left == nullptr) {
				left = new Custom_Set(x, this);
				++size;
				height = max((size_t)2, height);
				return;
			}
			left->Add(x);
		}
		else {
			if (right == nullptr) {
				right = new Custom_Set(x, this);
				++size;
				height = max((size_t)2, height);
				return;
			}
			right->Add(x);

		}

		Update_params();
		
	}

	size_t Get_Size() {
		return size;
	}
	size_t Get_Height() {
		return height;
	}

	void InOrder() {
		if (left != nullptr) {
			left->InOrder();
		}
		if (key != NULL) {
			cout << key << " ";
		}
		if (right != nullptr) {
			right->InOrder();
		}
		
	}

	void PreOrder() {

		if (key != NULL) {
			cout << key << " ";
		}

		if (left != nullptr) {
			left->PreOrder();
		}

		if (right != nullptr) {
			right->PreOrder();
		}

	}

	void PostOrder() {

		if (left != nullptr) {
			left->PostOrder();
		}

		if (right != nullptr) {
			right->PostOrder();
		}

		if (key != NULL) {
			cout << key << " ";
		}

	}

};


void InOrder(size_t * arr, int64_t * left, 
	int64_t * right, int64_t root) {
	if (root == -1) {
		return;
	}
	InOrder(arr, left, right, left[root]);
	cout << arr[root] << " ";
	InOrder(arr, left, right, right[root]);
}


void PreOrder(size_t * arr, int64_t * left,
	int64_t * right, int64_t root) {
	if (root == -1) {
		return;
	}
	cout << arr[root] << " ";
	PreOrder(arr, left, right, left[root]);
	PreOrder(arr, left, right, right[root]);
}

void PostOrder(size_t * arr, int64_t * left,
	int64_t * right, int64_t root) {
	if (root == -1) {
		return;
	}
	
	PostOrder(arr, left, right, left[root]);
	PostOrder(arr, left, right, right[root]);
	cout << arr[root] << " ";
}


int main()
{
	size_t n = 0;
	cin >> n;
	size_t * arr = new size_t[n];
	int64_t * parents = new int64_t[n];

	int64_t * left = new int64_t[n];
	int64_t * right = new int64_t[n];

	for (size_t i = 0; i < n; ++i) {
		parents[i] = -1;
		left[i] = -1;
		right[i] = -1;
	}
	string name;
	getline(cin, name);
	for (size_t i = 0; i < n; ++i) {
		getline(cin, name);
		stringstream ss(name);
		istream_iterator<string> begin(ss);
		istream_iterator<string> end;
		vector<string> vstrings(begin, end);
		vector<int> v(3);
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
	for (size_t i = 0; i < n; ++i) {
		if (parents[i] == -1) {
			root = i;
			break;
		}
	}

	InOrder(arr, left, right, root);
	cout << endl;
	PreOrder(arr, left, right, root);
	cout << endl;
	PostOrder(arr, left, right, root);

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
