// 1.6.3.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <algorithm>
#include <iostream>
#include <list>
#include <vector>
#include <sstream>
#include <string>
#include <iomanip>
#include <stack>

using namespace std;

int64_t Operation(int64_t a,char op, int64_t b) {
	if (op == '+') {
		return a + b;
	}
	if (op == '-') {
		return a - b;
	}
	if (op == '*') {
		return a * b;
	}
}

pair<int64_t, int64_t> MinAndMax(size_t i, size_t j,
	int64_t*& digits, char*& operations,
	int64_t**& M, int64_t**& m) {

	pair<int64_t, int64_t> p;
	p.first = numeric_limits<int64_t>::max();
	p.second = numeric_limits<int64_t>::min();

	for (size_t k = i; k < j; ++k) {
		int64_t a = Operation(M[i][k], operations[k], M[k + 1][j]);
		if (a < p.first) {
			p.first = a;
		}
		if (a > p.second) {
			p.second = a;
		}
		int64_t b = Operation(M[i][k], operations[k], m[k + 1][j]);
		if (b < p.first) {
			p.first = b;
		}
		if (b > p.second) {
			p.second = b;
		}
		int64_t c = Operation(m[i][k], operations[k], M[k + 1][j]);
		if (c < p.first) {
			p.first = c;
		}
		if (c > p.second) {
			p.second = c;
		}

		int64_t d = Operation(m[i][k], operations[k], m[k + 1][j]);
		if (d < p.first) {
			p.first = d;
		}
		if (d > p.second) {
			p.second = d;
		}
	}
	return p;
}


int64_t Paranthesees(int64_t*& digits, char*& operations,
	size_t n) {
	int64_t** M = new int64_t*[n];
	int64_t** m = new int64_t*[n];

	for (size_t i = 0; i < n; ++i) {
		M[i] = new int64_t[n];
		m[i]= new int64_t[n];
		M[i][i] = digits[i];
		m[i][i] = digits[i];
	}
	for (size_t d = 1; d < n; ++d) {
		for (size_t i = 0; i < n - d; ++i) {
			size_t j = i + d;
			pair<int64_t, int64_t> p = MinAndMax(i, j, 
				digits, operations,M,m);
			m[i][j] = p.first;
			M[i][j] = p.second;
		}
	}
	return M[0][n - 1];
}


int main()
{
	string s;

	getline(cin, s);

	int64_t* digits = new int64_t[s.size() / 2 + 1];
	char* operations = new char[s.size() / 2];

	size_t k = 0;
	size_t opk = 0;

	for (size_t i = 0; i < s.size(); ++i) {

		if (s[i] <= '9' && s[i] >= '0') {
			digits[k] = s[i]-'0';
			++k;
		}
		else {
			operations[opk] = s[i];
			++opk;
		}
	}

	cout << Paranthesees(digits, operations, s.size() / 2 + 1);


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
