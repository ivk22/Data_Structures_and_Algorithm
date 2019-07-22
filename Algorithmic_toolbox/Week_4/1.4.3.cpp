

#include <iostream>
#include <vector>
#include <cstdlib>
#include <random>
#include <algorithm>
using namespace std;


pair<size_t, size_t> Partition(size_t*& arr, size_t l, size_t r) {
	size_t j = l;
	size_t k = l;
	size_t x = arr[l];
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
	}
	return {j,k};
}

void RDQS(size_t*& arr, size_t l , size_t r) {

	if (r == l) {
		return;
	}
	if (r == l + 1) {
		if (arr[l] > arr[r]) {
			swap(arr[r], arr[l]);
		}
	}

	size_t rd = l +(rand()%(r-l+1));

	swap(arr[rd], arr[l]);

	pair<size_t, size_t> p = Partition(arr,l,r);

	if (p.first > l) {
		RDQS(arr, l, p.first - 1);
	}
	if (r>p.second) {
		RDQS(arr, p.second + 1, r);
	}
	

}


int main() {

	size_t n = 0;
	cin >> n;

	size_t* arr = new size_t[n];

	for (size_t i = 0; i < n; ++i) {
		cin >> arr[i];
	}

	RDQS(arr, 0, n - 1);

	for (size_t i = 0; i < n; ++i) {
		cout << arr[i] << " ";
	}
}
