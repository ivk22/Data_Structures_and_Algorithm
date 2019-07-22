// ConsoleApplication63.cpp : This file contains the 'main' function. Program execution begins and ends there.
//


#include <iostream>
#include <algorithm>
#include <queue>

using namespace std;

void Swap(size_t i, size_t j, size_t* arr) {
	size_t temp = arr[j];
	arr[j] = arr[i];
	arr[i] = temp;
}


void Siftdown(int i, size_t* arr, int n, queue<pair<int,int>> & s) {
	int child = -1;
	if (2 * i + 1 < n && 2 * i + 2 == n) {
		child = 2 * i + 1;
		if (arr[i] > arr[child]) {
			Swap(i, child, arr);
			s.push({i,child});
		}
	}
	else if (2 * i + 1 < n && 2 * i + 2 < n) {
		int child1 = 2 * i + 1;
		int child2 = 2 * i + 2;
		if (arr[child1] <= arr[child2]) {
			child = child1;
		}
		else {
			child = child2;
		}
		if (arr[i] > arr[child]) {
			Swap(i, child, arr);
			s.push({ i,child });
			Siftdown(child, arr, n,s);
		}
	}


}


int main()
{
	int n = 0;
	cin >> n;
	size_t * arr = new size_t[n];

	for (size_t i = 0; i < n; ++i) {
		cin >> arr[i];
	}

	queue <pair<int,int>> s;

	for (int i = max(n / 2 - 1, 0); i >=0 ; --i) {
		Siftdown(i, arr,n,s);
	}
	cout << s.size() << endl;
	while (!s.empty()) {
		pair<int, int> temp = s.front();
		cout << temp.first << " " << temp.second << endl;
		s.pop();
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
