// 1.4.5.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include <iostream>
#include <vector>
#include <cstdlib>
#include <random>
#include <algorithm>

using namespace std;

template <class T>
class Heap {
	T* arr;
	size_t n;

	void MakeHeap() {
		if (n >= 2) {
			for (size_t i = n / 2 - 1; i < n; --i) {
				SiftDown(i);
			}
		}

	}
	void SiftDown(size_t i) {

		if (2 * i + 1 < n) {

			T l = arr[2 * i + 1];

			if (2 * i + 2 < n) {
				T r = arr[2 * i + 2];
				if (r > l) {
					if (arr[i] < r) {
						swap(arr[i], arr[2 * i + 2]);
						SiftDown(2 * i + 2);
					}
				}
				else {
					if (arr[i] < l) {
						swap(arr[i], arr[2 * i + 1]);
						SiftDown(2 * i + 1);
					}
				}
			}
			else {
				if (arr[i] < l) {
					swap(arr[i], arr[2 * i + 1]);
					SiftDown(2 * i + 1);
				}
			}

		}
	}
public:

	Heap(T* a,size_t m) {
		arr = a;
		n = m;
		MakeHeap();
	}

	T ExtractMax() {
		T val = arr[0];
		swap(arr[0], arr[n - 1]);
		--n;
		SiftDown(0);
		return val;
	}
	bool Empty() {
		return (n == 0);
	}
};



template <class T>
void HeapSort(T*& arr, size_t& n) {
	Heap<T> hp(arr, n);
	while (!hp.Empty()) {
		hp.ExtractMax();

	}
}


template <class T>
pair<size_t, size_t> Partition(T*& arr, size_t l, size_t r, size_t& count, size_t& n) {
	size_t j = l;
	size_t k = l;
	T x = arr[l];
	for (size_t i = l + 1; i <= r; ++i) {
		if (arr[i] == x) {
			++k;
			swap(arr[k], arr[i]);
		}
		else if (arr[i] < x) {

			swap(arr[i], arr[k + 1]);

			swap(arr[k + 1], arr[j]);

			++j;
			++k;

		}
		++count;

		if (count > 3*n*log2(n)) {
			HeapSort(arr,n);
			return { l,r };
		}
	}
	return { j,k };
}



template <class T>
void RDQS(T*& arr, size_t l, size_t r, size_t& count, size_t& n) {

	if (r == l) {
		return;
	}
	if (r == l + 1) {
		if (arr[l] > arr[r]) {
			swap(arr[r], arr[l]);
		}
	}

	size_t rd = l + (rand() % (r - l + 1));

	swap(arr[rd], arr[l]);

	pair<size_t, size_t> p = Partition(arr, l, r,count,n);

	if (p.first > l) {
		RDQS(arr, l, p.first - 1, count,n);
	}
	if (r > p.second) {
		RDQS(arr, p.second + 1, r, count,n);
	}
}


template <class T>
size_t Bin_Search(T& x, T*& arr, size_t begin, size_t end) {
	if (begin == end) {
		if (arr[begin] <= x) {
			return begin + 1;
		}
		return begin;
	}
	if (end <= begin + 1) {

		if (arr[end] <= x) {
			return end+1;
		}
		if (arr[begin] <= x) {
			return begin + 1;
		}
		return begin;
	}

	size_t mid = (begin + end) / 2;


	if (x < arr[mid]) {
		return Bin_Search(x, arr, begin, mid - 1);
	}
	if (x >= arr[mid]) {
		return Bin_Search(x, arr, mid, end);
	}
}


template <class T>
size_t Bin_Search2(T& x, T*& arr, size_t begin, size_t end) {
	if (begin == end) {
		if (arr[begin] < x) {
			return begin + 1;
		}
		return begin;
	}
	if (end == begin + 1) {

		if (arr[end] < x) {
			return end + 1;
		}
		if (arr[begin] < x) {
			return begin + 1;
		}
		return begin;
	}

	size_t mid = (begin + end) / 2;


	if (x <= arr[mid]) {
		return Bin_Search2(x, arr, begin, mid);
	}
	if (x > arr[mid]) {
		return Bin_Search2(x, arr, mid+1, end);
	}
}



int main()
{
	size_t s = 0,p=0;
	cin >> s>>p;

	int64_t*A = new int64_t[s];
	int64_t*B = new int64_t[s];

	int64_t*P = new int64_t[p];

	for (size_t i = 0; i < s; ++i) {
		cin >> A[i] >> B[i];
	}

	for (size_t i = 0; i < p; ++i) {
		cin >> P[i];
	}


	size_t count = 0;
	RDQS(A,0,s-1,count,s);

	count = 0;
	RDQS(B, 0, s - 1, count, s);

	for (size_t i = 0; i < p; ++i) {
		int64_t l = Bin_Search(P[i], A, 0, s - 1);
		int64_t r = Bin_Search2(P[i], B, 0, s - 1);
		cout << l-r << " ";
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
