// 2.4.1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//


#include <iostream>
#include <string>
#include <queue>
#include <ostream>
#include <sstream>
#include <iterator>


using namespace std;

void Create_name(char*& c, string & s) {
	c = new char[s.size()];
	for (size_t i = 0; i < s.size(); ++i) {
		c[i] = s[i];
	}
}

void Print_name(pair<char*, size_t> & p) {
	for (size_t i = 0; i < p.second; ++i) {
		cout << p.first[i];
	}
	cout << endl;
}

int main()
{
	size_t n = 0;
	cin >> n;



	pair<char*,size_t>* arr = new pair<char*, size_t>[10000000];

	for (size_t i = 0; i < 10000000; ++i) {
		arr[i].second = 0;
	}
	string name;

	queue <string> q;
	getline(cin, name);
	for (size_t i = 0; i < n; ++i) {
		getline(cin, name);
		q.push(name);
	}



	while (!q.empty()) {

		stringstream ss(q.front());
		istream_iterator<string> begin(ss);
		istream_iterator<string> end;
		vector<string> v(begin, end);
		if (v[0] == "add") {
			arr[stoi(v[1])].second = v[2].size();
			Create_name(arr[stoi(v[1])].first, v[2]);
		}
		else if (v[0] == "find") {
			if (arr[stoi(v[1])].second == 0) {
				cout << "not found" << endl;
			}
			else {
				Print_name(arr[stoi(v[1])]);
			}
		}
		else {
			arr[stoi(v[1])].second = 0;
		}
		q.pop();
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
