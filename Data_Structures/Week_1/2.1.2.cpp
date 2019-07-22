// ConsoleApplication63.cpp : This file contains the 'main' function. Program execution begins and ends there.
//


#include <iostream>
#include <queue>
#include <algorithm>


using namespace std;
int main()
{
	size_t n = 0;
	cin >> n;

	int* arr = new int[n];

	int* levels = new int[n];

	for (size_t i = 0; i < n; ++i) {
		levels[i] = 0;
	}


	for (size_t i = 0; i < n; ++i) {
		cin >> arr[i];
	}

	queue<int> path;

	for (size_t i = 0; i < n; ++i) {
		queue<int> path;
		int k = arr[i];
		
		size_t lev = 0;
		
		while (k != -1) {
			if (!levels[k]) {
				path.push(k);
				k = arr[k];
				++lev;
				if (k == -1) {
					++lev;
					levels[k] = 1;
				}
			}
			else {
				lev += levels[k];
				break;
			}
		}
		while (!path.empty()) {
			levels[path.front()] = lev;
			--lev;
			path.pop();
		}
	}
	

	cout << max(1,*(max_element(levels, levels + n)));
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
