#include <algorithm>
#include <iostream>
#include <iomanip>
#include <vector>
#include <cmath>
#include <list>
#include <string>


using namespace std;


class Tries {
public:
	char c;
	list<Tries*> ptrs;
	Tries() {
	}

	bool Is_Not_Empty() {
		return (!ptrs.empty());
	}

	void Add(string::iterator s,size_t n) {

		if (n == 0) {
			return;
		}

		for (const auto& val : ptrs) {
			if (s[0] == val->c) {
				val->Add(s + 1, n - 1);
				return;
			}
		}

		Tries* new_val = new Tries();
		new_val->c = s[0];
		ptrs.push_back(new_val);
		new_val->Add(s + 1, n - 1);

	}
};


void PrintTrie(Tries & tr, size_t& n) {
	
	size_t cur = n;

	for (const auto& val : tr.ptrs) {
		++n;
		cout << cur << "->" << n << ":" << val->c <<endl;

		PrintTrie(*val, n);

	}
}

int main() {
	

	Tries tr;

	size_t n = 0;
	cin >> n;
	string name;

	getline(cin, name);


	for (size_t i = 0; i < n; ++i) {

		getline(cin, name);

		tr.Add(name.begin(), name.size());

	}
	size_t num = 0;
	PrintTrie(tr, num);
}
