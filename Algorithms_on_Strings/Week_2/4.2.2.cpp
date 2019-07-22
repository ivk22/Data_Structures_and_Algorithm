// 4.2.2.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <map>
#include <algorithm>
#include <list>

using namespace std;

int main()
{

	string T,S;
	getline(cin, T);
	S = T;

	sort(S.begin(), S.end());


	size_t * arr_first = new size_t[S.size()];

	size_t * arr_second = new size_t[T.size()];

	map<char, vector<size_t>> m_first;
	map<char, vector<size_t>> m_second;



	for (size_t i = 0; i < T.size(); ++i) {
		
		arr_first[i] = m_first[S[i]].size();
		m_first[S[i]].push_back(i);

		
		arr_second[i] = m_second[T[i]].size();
		m_second[T[i]].push_back(i);

	}

	string res;

	bool t = true;
	bool add = true;

	size_t k = 0;
	char next;
	size_t pos = 0;
	size_t cnt = 0;


	while (cnt<S.size()) {
		res += S[k];
		next = T[k];
		pos = arr_second[k];
		k = m_first[next][pos];
		++cnt;
	}

	reverse(res.begin(),res.end());

	cout << res;

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
