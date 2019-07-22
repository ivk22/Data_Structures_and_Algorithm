// 2.4.2.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include <queue>
#include <ostream>
#include <sstream>
#include <iterator>
#include <cmath>
#include <list>
#include <algorithm>

using namespace std;



uint64_t Power(uint64_t x, size_t n, size_t p) {
	uint64_t res = 1;
	while (n >= 1) {
		res = (res*x)%p;
		--n;
	}
	return res;
}

size_t PolyHash(string & s, size_t p, uint64_t x, size_t m) {
	uint64_t sm = 0;
 	for (size_t i = 0; i < s.size(); ++i) {
		
		sm = (sm + Power(x, i, p)*s[i]) % p;
	}
	return sm % m;
}



int main()
{
	size_t n = 0, m = 0,p=1000000007,x=263;
	cin >> m >> n;
	list<string>* arr = new list<string>[m];

	

	queue<string> q;
	string name;
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
		string action = v[0],value = v[1];
		
		if (action == "add") {
			size_t phash = PolyHash(value,p,x,m);
			auto it = find(arr[phash].begin(), arr[phash].end(), value);
			if (it == arr[phash].end()) {
				arr[phash].push_front(value);
			}
		}
		else if (action == "del") {
			size_t phash = PolyHash(value, p, x, m);
			arr[phash].remove(value);
		}
		else if (action == "find") {
			size_t phash = PolyHash(value, p, x, m);

			auto it = find(arr[phash].begin(), arr[phash].end(), value);
			if (it == arr[phash].end()) {
				cout << "no" <<endl;
			}
			else {
				cout << "yes" << endl;
			}
		}
		else {
			size_t ind = stoi(value);
			for (const auto & val : arr[ind]) {
				cout << val << " ";
			}
			cout << endl;
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
