// 2.1.3.cpp : This file contains the 'main' function. Program execution begins and ends there.
//


#include <iostream>
#include <queue>
using namespace std;

int main()
{
	int n = 0, S = 0, k=0,A=0,P=0,last=0;
	cin >> S >> n;

	queue<pair<int, int>> q,p;
	pair<int, int> temp;

	for (size_t i = 0; i < n; ++i) {
		cin >> temp.first >> temp.second;
		q.push(temp);
	}

	while (!q.empty()) {

		A = q.front().first;
		P = q.front().second;
		q.pop();
		
		while (!p.empty()) {
			temp = p.front();

			if (temp.first==-1) {
				cout << temp.first << endl;
				--k;
				p.pop();
			}
			else if (temp.first + temp.second <= A) {
				cout << temp.first << endl;
				p.pop();
			}
			else {
				break;
			}
		}

		if (p.size() - k >= S) {
			p.push({ -1,P });
			++k;
		}
		else {
			int T = max(last, A);
			last = T + P;
			p.push({ T,P });
		}

	}

	while (!p.empty()) {
		cout << p.front().first << endl;
		p.pop();
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
