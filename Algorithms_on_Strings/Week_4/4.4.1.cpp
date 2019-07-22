// 4.4.1.cpp : This file contains the 'main' function. Program execution begins and ends there.
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

size_t* Prefix(string & S) {
	size_t n = S.size();
	size_t* pref = new size_t[n];
	pref[0] = 0;
	size_t border = 0;

	for (size_t i = 1; i < n; ++i) {
		while (border > 0 && S[i] != S[border]) {
			border = pref[border - 1];
		}
		if (S[i] == S[border]) {
			++border;
		}
		else {
			border = 0;
		}
		pref[i] = border;
	}
	return pref;
}

int main()
{
	string Pattern, Genome,S;
	getline(cin, Pattern);
	getline(cin, Genome);
	S = Pattern + "$" + Genome;
	if (Pattern.size() <= Genome.size()) {
		size_t* res = Prefix(S);
		for (size_t i = 0; i < S.size(); ++i) {

			if (res[i] == Pattern.size()) {
				cout << i - 2 * Pattern.size() <<" ";
			}

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
