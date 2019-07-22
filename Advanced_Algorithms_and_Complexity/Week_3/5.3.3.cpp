// 5.3.3.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <vector>
#include <iostream>
#include <list>
#include <iomanip>
#include <cmath>
#include <math.h>
#include <string>
#include <set>
#include <map>
#include <algorithm>

using namespace std;

int main()
{
	int n = 0, m = 0;
	cin >> n >> m;

	vector<vector<int>> A(n);
	vector<int> b(n);
	vector<bool> vars(m+1,0);

	vector<vector<int>> lst(n);

	for (size_t i = 0; i < n; ++i) {
		A[i] = vector<int>(m);
		lst[i].reserve(3);
		for (size_t j = 0; j < m; ++j) {
			cin >> A[i][j];
			if (A[i][j]) lst[i].push_back(j + 1);
		}
	}

	for (size_t i = 0; i < n; ++i) {
		cin >> b[i];
	}

	
	set<vector<int>> restrictions;


	for (int i = 0; i < n; ++i) {
		if (0 > b[i]) {
			vector<int> v;
			v.reserve(3);
			for (int p = 0; p < lst[i].size(); ++p) {
				v.push_back(lst[i][p]);
				vars[lst[i][p]]=1;
			}
			sort(v.begin(), v.end());
			restrictions.insert(v);
		}

		for (int j = 0; j < lst[i].size(); ++j) {

			if (A[i][lst[i][j]-1] > b[i]) {
				vector<int> v;
				v.reserve(3);

				v.push_back(-lst[i][j]);
				vars[lst[i][j]]=1;
				for (int p = 0; p < lst[i].size(); ++p) {
					if (p != j) {
						v.push_back(lst[i][p]);
						vars[lst[i][p]] = 1;
					}
				}
				sort(v.begin(), v.end());
				restrictions.insert(v);

			}

			for (int k = j + 1; k < lst[i].size(); ++k) {

				if (A[i][lst[i][j]-1] + A[i][lst[i][k] - 1] > b[i]) {
	
					vector<int> v;
					v.reserve(3);
					v.push_back(-lst[i][j]);
					v.push_back(-lst[i][k]);

					vars[lst[i][j]]=1;
					vars[lst[i][k]] = 1;
					for (int p = 0; p < lst[i].size(); ++p) {
						if (p != j && p!=k) {
							v.push_back(lst[i][p]);
							vars[lst[i][p]]=1;
						}
					}
					sort(v.begin(), v.end());
					restrictions.insert(v);
				}

				for (int s = k + 1; s < lst[i].size(); ++s) {
					if (A[i][lst[i][j] - 1] + A[i][lst[i][k] - 1] + A[i][lst[i][s] - 1] > b[i]) {

						vector<int> v(3);
						v[0] = -lst[i][j];
						v[1] = -lst[i][k];
						v[2] = -lst[i][s];
						vars[lst[i][j]] = 1;
						vars[lst[i][k]] = 1;
						vars[lst[i][s]] = 1;
						sort(v.begin(), v.end());
						restrictions.insert(v);
					}
				}
			}
		}
	}

	if (!(restrictions.size())) {
		cout << 1 << " " << 1 << endl;
		cout << 1 << " " << -1 << " " << 0;
	}
	else {
		int cnt = 0;
		for (int i = 1; i < vars.size(); ++i) {
			cnt += vars[i];
		}
		cout << restrictions.size() << " " << cnt << endl;
		map<int, int> m;

		int k = 1;
		for (int i = 1; i < vars.size(); ++i) {
			if (vars[i]) {
				m[i] = k;
				++k;
			}
		}

		for (const auto& val : restrictions) {
			for (int i = 0; i < val.size(); ++i) {
				if (val[i] < 0) {
					cout << -m[-val[i]] << " ";
				}
				else {
					cout << m[val[i]] << " ";
				}
				
			}
			cout << 0 << endl;
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
