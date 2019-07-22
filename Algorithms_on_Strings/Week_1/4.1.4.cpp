#include <algorithm>
#include <iostream>
#include <iomanip>
#include <vector>
#include <cmath>
#include <list>
#include <string>
#include <map>
#include <algorithm>

using namespace std;

class Tree {

public:

	size_t pos;
	size_t size;

	map<char, Tree*> m;

	Tree() {

	}

	Tree(size_t p , size_t s) {
		pos = p;
		size = s;
	}



	bool Is_Empty() {
		return (m.empty());
	}


	void Add(size_t p, size_t n,string & str) {

		if (n == 0) {
			return;
		}

		auto ptr = m.find(str[p]);

		if (ptr == m.end()) {

			Tree* new_tree = new Tree(p, n);

			m[str[p]] = new_tree;

		}
		else {
			size_t pp = m[str[p]]->pos;
			size_t sz = m[str[p]]->size;

			for (size_t i = 0; i < min(n,sz); ++i) {
				if (str[p + i] != str[pp + i]) {


					m[str[p]]->size = i;

					map<char, Tree*> m_prev = m[str[p]]->m;

					Tree* right = new Tree(pp + i, sz - i);

					Tree* left = new Tree(p + i, n - i);

					right->m = m_prev;

					m[str[p]]->m = map<char, Tree*>{ {str[pp + i],right},
					{str[p + i],left} };
					return;
				}
			}
	
			if (n > sz) {
				m[str[p]]->Add(p+sz,n-sz, str);
			}

		}

	}


};



void PrintTree(Tree tr,string & str) {
	if (tr.size != 0) {
		string s;

		for (size_t i = tr.pos; i < tr.pos+tr.size; ++i) {
			s+= str[i];
		}


		cout << s << endl;
	}

	for (const auto & val : tr.m) {
		Tree intr = *val.second;
		PrintTree(intr, str);
	}
}



int main() {

	string s;
	getline(cin, s);
	Tree tr;

	for (size_t i = 0; i < s.size(); ++i) {
		tr.Add(i, s.size() - i,s);
	}


	PrintTree(tr,s);
	

}
