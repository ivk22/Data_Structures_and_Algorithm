// 6.1.1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <algorithm>
#include <iostream>
#include <iomanip>
#include <vector>
#include <cmath>
#include <list>
#include <string>
#include <set>

using namespace std;


class Tries {
public:
	char c;
	list<size_t> id;
	list<Tries*> ptrs;
	Tries() {
	}

	bool Is_Not_Empty() {
		return (!ptrs.empty());
	}

	void Add(char* s, size_t n, size_t ind) {

		if (!n) {
			id.push_back(ind);
			return;
		}

		for (const auto& val : ptrs) {
			if (s[0] == val->c) {
				val->Add(s + 1, n - 1, ind);
				return;
			}
		}

		Tries* new_val = new Tries();
		new_val->c = s[0];
		ptrs.push_back(new_val);
		new_val->Add(s + 1, n - 1, ind);
	}



	void Match(string::iterator s, size_t n, size_t& init_n,
		vector<pair<size_t, size_t>>& v, size_t error_count) {

		if (error_count <= 0.05*(init_n - n)) {
			for (const auto& val : id) {
				v.push_back({ init_n - n,val });
			}
		}

		if (!n) {
			return;
		}

		for (const auto& val : ptrs) {
			if (s[0] == val->c) {
				val->Match(s + 1, n - 1, init_n, v, error_count);
			}
			else {
				if (error_count < 5) val->Match(s + 1, n - 1, init_n, v, error_count+1);
			}
			
		}

	}


};


size_t Overlap(string& l, string& r) {


	for (size_t i = 0; i < l.size(); ++i) {
		size_t cur = 0;
		for (size_t j = 0; j < l.size() - i; ++j) {
			if (l[i + cur] == r[j]) ++cur;
			else {
				cur = 0;
				break;
			}
		}
		if (cur) return cur;
	}

	return 0;
}


int main()
{

	Tries tr;

	size_t n = 1618, m = 100;
	vector<string> v(n, "");

	char* chr = new char[m];

	string s;
	for (size_t i = 0; i < n; ++i) {
		getline(cin, s);

		v[i] = s;

		for (size_t j = 0; j < m; ++j) {
			chr[m - j - 1] = s[j];
			tr.Add(chr + m - j - 1, j + 1, i);
		}
	}

	vector<vector<pair<size_t, size_t>>> GR(n);

	for (size_t i = 0; i < n; ++i) {
		GR[i].reserve(m*n);
		string rev = v[i];
		reverse(rev.begin(), rev.end());
		size_t cnt = 0;
		tr.Match(rev.begin(), m, m, GR[i], cnt);
		sort(GR[i].begin(), GR[i].end());
	}

	vector<bool> visited(n, 0);

	visited[0] = 1;
	size_t cur = 0, k = 1;

	string result = v[cur];

	while (true) {

		if (k == n - 1) {
			size_t last = Overlap(v[cur], v[0]);
			result = result.substr(0, result.size() - last);
			break;
		}

		for (size_t i = GR[cur].size() - 1; i < GR[cur].size(); --i) {

			if (!visited[GR[cur][i].second]) {

				visited[GR[cur][i].second] = 1;
				size_t len = GR[cur][i].first;
				cur = GR[cur][i].second;
				string temp(v[cur].begin() + len, v[cur].end());
				result += temp;
				++k;
				break;
			}

			if (!i) {
				for (size_t j = 0; j < n; ++j) {
					if (!visited[j]) {
						visited[j] = 1;
						cur = j;
						++k;
						result += v[cur];
						break;
					}
				}
			}

		}
	}

	cout << result;

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
