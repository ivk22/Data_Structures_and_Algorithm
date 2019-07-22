#include <algorithm>
#include <iostream>
#include <iomanip>
#include <vector>
#include <cmath>
#include <list>
#include <string>
#include <map>

using namespace std;


class Tries {

public:
	char c;
	map <char, Tries*> m;

	Tries() {
	}

	Tries( char ch) {
		c = ch;
	}

	bool Is_Not_Empty() {
		return (!m.empty());
	}

	void Add(string::iterator s, size_t n) {

		if (n == 0) {
			return;
		}

		auto ptr = m.find(s[0]);

		if (ptr == m.end()) {
			Tries* new_trie = new Tries(s[0]);
			m[s[0]] = new_trie;
			new_trie->Add(s + 1, n - 1);
		}
		else {
			ptr->second->Add(s + 1, n - 1);
		}

	}

	bool Find(string::iterator s, size_t n) {
		if (!Is_Not_Empty()) {
			return true;
		}

		if (n == 0) {
			return false;
		}

		auto ptr = m.find(s[0]);

		if (ptr == m.end()) {
			return false;
		}

		else {
			return ptr->second->Find(s + 1, n - 1);
		}
	}

};


void PrintTrie(Tries & tr, size_t& n) {

	size_t cur = n;

	for (const auto& val : tr.m) {
		++n;
		cout << cur << "->" << n << ":" << val.first << endl;

		PrintTrie(*val.second, n);

	}
}

int main() {


	Tries tr;
	string name,Text;
	
	getline(cin, Text);

	size_t n = 0;
	cin >> n;


	getline(cin, name);
	for (size_t i = 0; i < n; ++i) {

		getline(cin, name);
		tr.Add(name.begin(), name.size());

	}

	for (size_t i = 0; i < Text.size(); ++i) {
		if (tr.Find(Text.begin() + i, Text.size() - i)) {
			cout << i << " ";
		}
	}
}
