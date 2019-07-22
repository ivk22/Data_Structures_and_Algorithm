// 4.4.4.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <map>
#include <algorithm>
#include <list>
#include <sstream>
#include <ostream>
#include <iterator>
#include <set>

using namespace std;


size_t prex(string& S, size_t pos1, size_t pos2, size_t skip) {
	if (skip) {
		--skip;
	}
	pos1 += skip;
	pos2 += skip;
	size_t n = S.size();
	size_t res = skip;

	while (pos1 < n && pos2 < n) {
		if (S[pos1] != S[pos2]) {
			break;
		}
		++pos1;
		++pos2;
		++res;
	}
	return res;
}

size_t* CreatePos(size_t n, size_t* order) {
	size_t* pos = new size_t[n];
	for (size_t i = 0; i < n; ++i) {
		pos[order[i]] = i;
	}
	return pos;
}

size_t* LCP(string& S, size_t* SuffixArray) {
	size_t n = S.size();
	size_t* pos = CreatePos(S.size(), SuffixArray);
	size_t* lcparr = new size_t[n - 1];

	size_t cur = SuffixArray[0];

	size_t lcp = 0;


	for (size_t i = 0; i < n; ++i) {
		size_t ind = pos[cur];

		if (ind == n - 1) {
			lcp = 0;
			cur = (cur + 1) % n;
			continue;
		}

		size_t next = SuffixArray[ind+1];

		lcp = prex(S, cur, next,lcp);
		lcparr[ind] = lcp;
		cur = (cur + 1) % n;
	}
	return lcparr;
}


int main()
{
	string T;

	getline(cin, T);

	size_t n = T.size();

	string Patterns;

	getline(cin, Patterns);
	

	stringstream ss(Patterns);

	istream_iterator<string> begin(ss);
	istream_iterator<string> end;
	vector<string> v(begin, end);

	size_t* vex=new size_t[n];

	for (size_t i = 0; i < n; ++i) {
		vex[i] = stoi(v[i]);
	}

	string R;
	getline(cin, R);

	stringstream S(R);

	istream_iterator<string> b(S);
	istream_iterator<string> e;
	vector<string> V(b, e);



	for (size_t i = 0; i < n-1; ++i) {
		cout << V[i] << " ";
	}
	cout << endl;
	size_t* res = LCP(T, vex);

	for (size_t i = 0; i < n - 1; ++i) {
		cout << res[i] << " ";
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
