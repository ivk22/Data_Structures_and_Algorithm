// 5.3.1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//


#include <iostream>
#include <vector>
#include <list>

using namespace std;

int main()
{
	int n = 0, m = 0;
	cin >> n >> m;
	list<int>* G = new list<int>[n+1];

	for (int i = 0; i < m; ++i) {
		int v = 0, u = 0;

		cin >> u >> v;
		G[u].push_back(v);

	}
	cout << n+3*n+3*m << " " << n * 3 << endl;

	for (int i = 1; i <= n; ++i) {
		cout << 3 * (i - 1) + 1 << " " << 3 * (i - 1) + 2
			<< " " << 3 * (i - 1) + 3 << " " << 0 << endl;
		cout << -(3 * (i - 1) + 1) << " " << -(3 * (i - 1) + 2) << " " << 0 << endl;
		cout << -(3 * (i - 1) + 2) << " " << -(3 * (i - 1) + 3) << " " << 0 << endl;
		cout << -(3 * (i - 1) + 1) << " " << -(3 * (i - 1) + 3) << " " << 0 << endl;
		
		for (const auto& val : G[i]) {
			cout << -(3 * (i - 1) + 1) << " " << -(3 * (val - 1) + 1) << " " << 0 << endl;
			cout << -(3 * (i - 1) + 2) << " " << -(3 * (val - 1) + 2) << " " << 0 << endl;
			cout << -(3 * (i - 1) + 3) << " " << -(3 * (val - 1) + 3) << " " << 0 << endl;
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
