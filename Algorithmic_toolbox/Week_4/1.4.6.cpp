// 1.4.6.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include <cstdlib>
#include <random>
#include <algorithm>
#include <list>
#include <iomanip>
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

	Heap(T* a, size_t m) {
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

		if (count > 4 * n*log2(n)) {
			HeapSort(arr, n);
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

	pair<size_t, size_t> p = Partition(arr, l, r, count, n);

	if (p.first > l) {
		RDQS(arr, l, p.first - 1, count, n);
	}
	if (r > p.second) {
		RDQS(arr, p.second + 1, r, count, n);
	}
}



double dist(pair<double, double>& x1, pair<double, double>& x2) {
	double x_diff = x1.first - x2.first;
	double y_diff = x1.second - x2.second;
	double res = sqrt(x_diff*x_diff + y_diff * y_diff);
	return res;
}



double MinDist(pair<double, double>*arr , size_t l , size_t r) {
	
	if (r == l) {
		return numeric_limits<double>::max();
	}
	if (r == l + 1) {
		double val = dist(arr[l], arr[r]);
		if (arr[l].second > arr[r].second) {
			swap(arr[l], arr[r]);
		}
		return val;
	}
	size_t n = (r - l + 1);
	size_t mid = (r+l) / 2;

	double x = arr[mid].first;

	double mndst = min(MinDist(arr, l, mid), MinDist(arr, mid+1, r));

	pair<double, double>* massive = new pair<double, double>[n];
	size_t pos_right = mid + 1;

	for (size_t i = l; i <= mid; ++i) {
		while (pos_right <= r && arr[i].second > arr[pos_right].second) {
			massive[i + pos_right - l - mid - 1] = arr[pos_right];
			++pos_right;
		}
		massive[i + pos_right - l - mid - 1] = arr[i];
	}
	while (pos_right <= r) {
		massive[pos_right - l] = arr[pos_right];
		++pos_right;
	}


	vector<size_t> v;
	v.reserve(n);

	for (size_t i = l; i <= r; ++i) {
		arr[i] = massive[i - l];
		if (abs(arr[i].first - x) <= mndst) {
			v.push_back(i);
		}
	}

	delete[] massive;


	for (size_t i = 0; i < v.size(); ++i) {
		for (size_t j = i + 1; j < min(v.size(), i + 8); ++j) {
			double val = dist(arr[v[i]], arr[v[j]]);
			if (val < mndst) {
				mndst = val;
			}
		}
	}
	return mndst;
}

int main()
{

	size_t n = 0;
	cin >> n;

	pair<double, double>*arr = new pair<double, double>[n];

	for (size_t i = 0; i < n; ++i) {
		cin >> arr[i].first>> arr[i].second;
	}

	size_t count = 0;

	RDQS(arr, 0, n - 1, count, n);

	cout <<setprecision(9)<< MinDist(arr, 0, n - 1);
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
