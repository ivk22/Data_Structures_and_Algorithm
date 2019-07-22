// 1.3.2.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include <algorithm>
#include <vector>
#include <iostream>
#include <iomanip>
using namespace std;

int main()
{
	size_t N = 0, W = 0;
	cin >> N >> W;
	double res = 0;
	vector < pair<double, size_t>> v(N);
	double val = 0;
	size_t w = 0;
	for (size_t i = 0; i < N; ++i) {
		cin >> val >> w;
		val /= w;
		v[i] = { val,w };
	}

	sort(v.begin(), v.end());

	for (size_t i = v.size() - 1; i < v.size(); --i) {

		size_t mn = min(W, v[i].second);
		res += mn * v[i].first;
		W -= mn;
		if (!W) {
			break;
		}
		
	}
	cout <<setprecision(9)<< res;
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
