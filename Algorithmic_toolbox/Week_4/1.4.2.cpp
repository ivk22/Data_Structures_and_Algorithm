// 1.4.2.cpp : This file contains the 'main' function. Program execution begins and ends there.

#include <iostream>
using namespace std;

int64_t Bin_Search(size_t*& arr, size_t begin, size_t end) {
	if (begin == end) {
		return arr[begin];
	}

	if (end == begin + 1) {
		if (arr[begin] == arr[end]) {
			return arr[begin];
		}
		return -1;
	}

	size_t mid = (begin + end) / 2;

	int64_t l = Bin_Search(arr, begin, mid);

	int64_t r = Bin_Search(arr, mid + 1, end);

	if (l != -1) {
		size_t res = 0;
		for (size_t i = begin; i <= end; ++i) {
			if (arr[i] == l) {
				++res;
			}
		}
		if (res > (end - begin + 1) / 2) {
			return l;
		}
	}
	if (r != -1) {
		size_t res = 0;
		for (size_t i = begin; i <= end; ++i) {
			if (arr[i] == r) {
				++res;
			}
		}
		if (res > (end - begin + 1) / 2) {
			return r;
		}
	}
	return -1;
}



int main()
{
	size_t n = 0;
	cin >> n;
	size_t* arr = new size_t[n];

	for (size_t i = 0; i < n; ++i) {
		cin >> arr[i];
	}

	int64_t res = Bin_Search(arr,0,n-1);
	cout << (res != -1);
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
