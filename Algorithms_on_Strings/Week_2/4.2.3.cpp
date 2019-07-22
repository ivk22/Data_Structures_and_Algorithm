// 4.2.2.cpp : This file contains the 'main' function. Program execution begins and ends there.
//


#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <map>
#include <algorithm>
#include <list>
#include <sstream>
#include <ostream>
#include <iterator>

using namespace std;

size_t Num_Matches(int*& FirstOccurence, string & LastColumn,
	string & Pattern, size_t**& Count,
	size_t*& arr) {

	size_t top = 0;
	int curr_pos = Pattern.size() - 1;
	size_t bottom = LastColumn.size()-1;
	while (curr_pos >= 0) {

		char symb = Pattern[curr_pos];
		--curr_pos;
		size_t k = arr[symb];

		if (k) {
			if (!top) {
				if (Count[k][bottom]) {
					top = FirstOccurence[k];
					bottom = FirstOccurence[k] + Count[k][bottom]-1;
				}
				else {
					return 0;
				}
			}
			else {
				if (Count[k][bottom] - Count[k][top - 1]) {

					top = FirstOccurence[k] + Count[k][top-1];
					bottom = FirstOccurence[k] + Count[k][bottom]-1;

				}
				else {
					return 0;
				}
			}
		}
		else {
			return 0;
		}
	}
	return bottom - top + 1;
}

int main()
{


	size_t len = 'z' + 1;
	size_t* arr = new size_t[len];

	size_t* sort_array = new size_t[len];


	for (size_t i = 0; i < len; ++i) {
		arr[i] = 0;
		sort_array[i] = 0;
	}

	string T, S;
	getline(cin, T);
	S = T;

	size_t n = 0;
	cin >> n;
	string Patterns;

	getline(cin, Patterns);
	getline(cin, Patterns);

	stringstream ss(Patterns);

	istream_iterator<string> begin(ss);
	istream_iterator<string> end;
	vector<string> v(begin, end);




	for (size_t i = 0; i < T.size(); ++i) {
		++sort_array[T[i]];
	}


	size_t curnum = 0;
	for (size_t i = 0; i < len; ++i) {
		for (size_t j = 1; j <= sort_array[i]; ++j) {
			S[curnum] = (char)i;
			++curnum;
		}
		if (curnum == S.size()) {
			break;
		}
	}

	size_t k = 1;

	for (size_t i = 0; i < T.size(); ++i) {
		if (arr[T[i]] == 0) {
			arr[T[i]] = k;
			++k;

		}
	}

	size_t** Count = new size_t*[k];

	char next = T[0];

	for (size_t i = 1; i < k; ++i) {

		Count[i] = new size_t[T.size()];

		if (arr[next] == i) {
			Count[i][0] = 1;
		}
		else {
			Count[i][0] = 0;
		}

	}


	for (size_t i = 1; i < T.size(); ++i) {
		next = T[i];

		for (size_t j = 1; j < k; ++j) {
			if (arr[next] == j) {
				Count[j][i] = Count[j][i - 1] + 1;
			}
			else {
				Count[j][i] = Count[j][i - 1];
			}
		}
	}

	next = S[0];

	int* FirstOccurence = new int[k];

	for (size_t i = 1; i < k; ++i) {
		FirstOccurence[i] = -1;
	}
	FirstOccurence[arr[next]] = 0;


	for (size_t i = 1; i < S.size(); ++i) {
		next = S[i];

		if (FirstOccurence[arr[next]] == -1) {
			FirstOccurence[arr[next]] = i;
		}

	}


	for (auto& val : v) {
		cout << Num_Matches(FirstOccurence,T,val,Count,arr) << " ";
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
