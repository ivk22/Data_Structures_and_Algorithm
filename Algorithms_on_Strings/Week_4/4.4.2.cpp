// 4.4.2.cpp : This file contains the 'main' function. Program execution begins and ends there.
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

size_t* SortChar(string& S) {
	size_t n = 'z' + 1;

	size_t* chars = new size_t[n];

	size_t* order = new size_t[S.size()];

	for (size_t i = 0; i < n; ++i) {
		chars[i]=0;
	}
	for (size_t i = 0; i < S.size(); ++i) {
		++chars[S[i]];
	}

	for (size_t i = 1; i < n; ++i) {
		chars[i] += chars[i-1];
	}

	for (size_t i = S.size()-1; i < S.size(); --i) {
		--chars[S[i]];
		order[chars[S[i]]]=i;
	}
	return order;
}

size_t* ComputeClasses(string& S, size_t*& order) {
	
	size_t n = S.size();

	size_t* classes = new size_t[n];

	classes[order[0]] = 0;
	for (size_t i = 1; i < n; ++i) {
		if (S[order[i]] > S[order[i - 1]]) {
			classes[order[i]] = classes[order[i-1]]+1;
		}
		else {
			classes[order[i]] = classes[order[i - 1]];
		}
	}
	return classes;
}

size_t* SortDoubled(size_t L, string& S, size_t*& order,
	size_t* classes) {
	size_t n = S.size();

	size_t* Neworder = new size_t[n];

	size_t* counts = new size_t[n];

	for (size_t i = 0; i < n; ++i) {
		counts[i] = 0;
	}

	for (size_t i = 0; i < n; ++i) {
		++counts[classes[i]];
	}

	for (size_t i = 1; i < n; ++i) {
		counts[i]+= counts[i-1];
	}

	for (size_t i = n - 1; i < n; --i) {
		size_t start = (order[i]+n-L) % n;
		--counts[classes[start]];
		Neworder[counts[classes[start]]] = start;
	}
	return Neworder;

}

size_t* MakeClasses(size_t n, size_t* Neworder, size_t* classes,size_t L) {

	size_t* Newclasses = new size_t[n];

	Newclasses[Neworder[0]] = 0;
	for (size_t i = 1; i < n; ++i) {
		if (classes[Neworder[i]] > classes[Neworder[i - 1]] || classes[(Neworder[i] + L) % n] > classes[(Neworder[i-1] + L) % n]) {
			Newclasses[Neworder[i]] = Newclasses[Neworder[i - 1]]+1;
		}
		else {
			Newclasses[Neworder[i]] = Newclasses[Neworder[i - 1]];
		}
	}
	return Newclasses;
}

size_t* SortPrefix(string & S) {
	size_t n = S.size();
	size_t*order = SortChar(S);
	size_t*classes=ComputeClasses(S, order);
	size_t L = 1;
	while (L < S.size()) {
		order = SortDoubled(L,S,order, classes);
		classes = MakeClasses(n, order, classes,L);
		L *= 2;
	}
	return order;
}

int main()
{
	string S;
	getline(cin, S);
	size_t* order = SortPrefix(S);
	for (size_t i = 0; i < S.size(); ++i) {
		cout << order[i] << " ";
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
