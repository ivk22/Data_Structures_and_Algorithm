// 5.5.1_final.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <vector>
#include <iostream>
#include <set>
#include <cmath>
#include <math.h>
#include <algorithm>
#include <functional>
using namespace std;


int64_t int_hash(int64_t x , int64_t p , int64_t m, int64_t a, int64_t b) {
	return ((a*x + b) % p) % m;
}


int64_t sign_hash(int64_t x, int64_t p, int64_t a, int64_t b) {
	int64_t res = ((a*x + b) % p) % 2;
	if (res) {
		return res;
	}
	return -1;
}


int main()
{
	
	int64_t p = 100000004987;

	int64_t N = 0,t=0;
	cin >> N >> t;

	int64_t T = ceil(log2(N) + 1);

	int64_t m = pow(10, 6) / T;

	pair<int64_t, int64_t>*  int_hashes = new  pair<int64_t, int64_t>[T];

	pair<int64_t, int64_t>*  sign_hashes = new  pair<int64_t, int64_t>[T];

	int64_t** C = new int64_t*[T];

	for (size_t i = 1; i <= T; ++i) {
		int_hashes[i - 1] = { rand(),rand() };
		sign_hashes[i - 1] = { rand(),rand() };
		C[i - 1] = new int64_t[m];
		for (size_t j = 0; j < m; ++j) {
			C[i - 1][j] = 0;
		}
	}

	for (size_t i = 0; i < N; ++i) {
		int64_t k = 0 , g = 0;
		cin >> k >> g;
		for (size_t j = 0; j < T; ++j) {
			int64_t pos = int_hash(k, p, m,
				int_hashes[j].first, int_hashes[j].second);
			int64_t sign = sign_hash(k, p,
				sign_hashes[j].first, sign_hashes[j].second);

			C[j][pos] += sign * g;

		}
	}

	for (size_t i = 0; i < N; ++i) {
		int64_t k = 0, b = 0;
		cin >> k >> b;
		for (size_t j = 0; j < T; ++j) {
			int64_t pos = int_hash(k, p, m,
				int_hashes[j].first, int_hashes[j].second);
			int64_t sign = sign_hash(k, p,
				sign_hashes[j].first, sign_hashes[j].second);

			C[j][pos] -= sign * b;

		}
	}

	size_t q = 0;
	cin >> q;
	vector<int64_t> qv(q);
	for (size_t i = 0; i < q; ++i) {
		cin >> qv[i];
	}


	for (size_t i = 0; i < q; ++i) {
		int64_t k = qv[i];

		vector<int64_t> pred(T);

		for (size_t j = 0; j < T; ++j) {

			int64_t pos = int_hash(k, p, m,
				int_hashes[j].first, int_hashes[j].second);
			int64_t sign = sign_hash(k, p,
				sign_hashes[j].first, sign_hashes[j].second);

			pred[j] = sign * C[j][pos];

		}


		sort(pred.begin(), pred.end());
		int64_t res = pred[pred.size() / 2];

		if (res >= t) {
			cout << 1 << " ";
		}
		else {
			cout << 0 << " ";
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
