// 2.1.3.cpp : This file contains the 'main' function. Program execution begins and ends there.
//


#include <iostream>

#include <algorithm>

#include <list>

#include <queue>

#include <string>

#include <sstream>

#include <ostream>

#include <iterator>


using namespace std;


class Custom_Stack {
public:
	Custom_Stack() {

	}
	void Push(int a) {

		l.push_back(a);
		if (maxes.size() == 0) {
			maxes.push_back(a);
		}
		else {
			maxes.push_back(max(a, maxes.back()));
		}
		
	}
	void Pop() {
		l.pop_back();
		maxes.pop_back();
	}

	int Max() {
		return maxes.back();
	}
private:
	list <int> l;
	list <int> maxes;
};





int main()
{
	Custom_Stack s;
	int q = 0;
	cin >> q;
	queue <string> que;
	string temp;
	getline(cin, temp);

	for (int i = 0; i < q; ++i) {
		getline(cin, temp);
		que.push(temp);
	}

	while (!que.empty()) {
		temp = que.front();
		que.pop();
		istringstream iss(temp);
		vector<string> results((istream_iterator<string>(iss)),
			istream_iterator<string>());
		if (results.size() == 1) {
			if (results[0] == "max") {
				cout << s.Max() << endl;
			}
			else {
				s.Pop();
			}
		}
		else {
			s.Push(stoi(results[1]));
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
