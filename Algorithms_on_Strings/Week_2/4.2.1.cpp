#include <algorithm>
#include <iostream>
#include <iomanip>
#include <vector>
#include <cmath>
#include <list>
#include <string>
#include <map>
#include <algorithm>
#include <set>

using namespace std;


int main() {

	string s;
	
	getline(cin, s);
	char** p = new char*[s.size()];

	for (int i = 0; i < s.size(); ++i) {
		p[i] = new char[s.size()+1];

		for (int j = 0; j < i; ++j) {
			p[i][j] = s[s.size()-i+j];
		}

		for (int j = i; j < s.size(); ++j) {
			p[i][j] = s[j - i];
		}
		p[i][s.size()] = '\0';
	}


	set<string> st;
	for (int i = 0; i < s.size(); ++i) {
		string t(p[i]);
		st.insert(t);
	}
	string res;
	for (const auto & val : st) {
		res += val[val.size() - 1];
	}
	cout << res;
}
