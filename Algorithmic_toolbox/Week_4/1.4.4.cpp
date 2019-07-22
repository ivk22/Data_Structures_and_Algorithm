// 1.4.4.cpp : This file contains the 'main' function. Program execution begins and ends there.
//


#include <iostream>
#include <vector>
#include <cstdlib>
#include <random>
#include <algorithm>
using namespace std;

size_t InvCount(size_t*& arr, size_t l , size_t r) {
	if (r == l) {
		return 0;
	}
	if (r == l + 1) {
		if (arr[l] > arr[r]) {
			swap(arr[l], arr[r]);
			return 1;
		}
		return 0;
	}

	size_t mid = (r + l) / 2;

	size_t res_left = InvCount(arr, l, mid);

	size_t res_right = InvCount(arr, mid+1, r);

	size_t res = res_left + res_right;

	size_t size_left = mid - l + 1;

	size_t size_right = r - mid;

	size_t* left = new size_t[size_left];
	size_t* right = new size_t[size_right];


	for (size_t i = 0; i < size_left; ++i) {
		left[i] = arr[i + l];
	}

	for (size_t i = 0; i < size_right; ++i) {
		right[i] = arr[i + mid + 1];
	}

	size_t pos_right = 0,nw=0,prev=0;


	for (size_t i = 0; i < size_left; ++i) {

		if (pos_right == size_right) {
			arr[l+pos_right+i] = left[i];
			res += prev;
			continue;
		}
		while (right[pos_right] < left[i] && pos_right< size_right) {
			arr[l + i + pos_right] = right[pos_right];
			++nw;
			++pos_right;
			if (pos_right == size_right) {
				prev += nw;
				res += prev;
				nw = 0;
			}
		}
		arr[l + i + pos_right] = left[i];
		if (pos_right < size_right) {
			prev += nw;
			res += prev;
			nw = 0;
		}
	}

	while (pos_right < size_right) {

		arr[l+size_left + pos_right] = right[pos_right];
		++pos_right;

	}

	delete[] left;
	delete[] right;

	return res;

}


int main()
{
	size_t n = 0;
	cin >> n;
	size_t* arr = new size_t[n];

	for (size_t i = 0; i < n; ++i) {
		cin >> arr[i];
	}

	cout << InvCount(arr, 0, n - 1);

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
