// 6.2.1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>
#include <list>
using namespace std;


bool Admissible(size_t n, size_t elem, 
	vector<vector<string>>& v,
	vector<vector<int>>& matr, size_t i , size_t j) {



	if (i == n - 1) if (v[elem][2]!= "black") return false;
	if (i == 0) if (v[elem][0]!= "black") return false;
	if (j == n - 1) if (v[elem][3]!= "black") return false;
	if (j == 0) if (v[elem][1]!= "black") return false;

	if (i+1 < n) if(matr[i + 1][j]!=-1) if (v[elem][2]!=v[matr[i+1][j]][0]) return false;

	if (j + 1 < n) if (matr[i][j + 1] != -1) if (v[elem][3]!=v[matr[i][j + 1]][1]) return false;

	if (i) if (matr[i-1][j] != -1) if (v[elem][0]!=v[matr[i-1][j]][2]) return false;

	if (j) if (matr[i][j - 1] != -1) if (v[elem][1]!=v[matr[i][j - 1]][3]) return false;


	return true;
}


void Puzzle_Solver(vector<vector<int>>& real_matr,
	vector<vector<int>> matr,
	vector<vector<string>>& v,
	vector<bool> visited, size_t i, size_t j, size_t n, bool& end) {

	if (i == n - 1 && j == n - 1) {
		end = true;
		real_matr=matr;
		return;
	}

	if (matr[i][j] != -1) {
		if (j == n - 1) {
			Puzzle_Solver(real_matr,matr, v, visited, i+1, 0,n, end);
			return;
		}
		Puzzle_Solver(real_matr,matr, v, visited, i, j+1, n, end);
		return;
	}

	for (size_t k = 0; k < v.size(); ++k) {
		if (!visited[k]) {
			if (Admissible(n, k, v, matr, i, j)) {
				matr[i][j] = k;
				visited[k] = 1;
				if (j == n - 1) {
					Puzzle_Solver(real_matr, matr, v, visited, i + 1, 0, n, end);
					
				}
				else {
					Puzzle_Solver(real_matr, matr, v, visited, i, j + 1, n, end);
				}
				
				if (end) return;
				matr[i][j] = -1;
				visited[k] = 0;
			}
		}
	}

}


int main()
{
	size_t n = 5;
	vector<vector<string>> v(n*n);
	vector<string> initial(n*n);

	vector<vector<int>> matr(n, vector<int>(n,-1));

	vector<bool> visited(n*n,0);

	for (size_t i = 0; i < n*n; ++i) {
		v[i] = vector<string>(4);
		string temp;
		getline(cin, temp);
		initial[i] = temp;
		temp = temp.substr(1,temp.size()-2);

		stringstream stream(temp);
		string side;
		size_t j = 0;

		while (getline(stream, side, ',')) {
			v[i][j] = side; 
			++j;
		}


		if (v[i][0] == "black" && v[i][1] == "black") {
			matr[0][0] = i;
			visited[i] = 1;
			continue;
		}
		if (v[i][0] == "black" && v[i][3] == "black") {
			matr[0][n-1] = i;
			visited[i] = 1;
			continue;
		}
		if (v[i][1] == "black" && v[i][2] == "black") {
			matr[n - 1][0] = i;
			visited[i] = 1;
			continue;
		}		
		if (v[i][2] == "black" && v[i][3] == "black") {
			matr[n - 1][n - 1] = i;
			visited[i] = 1;
			continue;
		}


	}

	vector<vector<int>> matr_copy = matr;
	bool end = false;

	Puzzle_Solver(matr, matr_copy,v,visited,0,1,n,end);

	for (size_t i = 0; i < n; ++i) {
		for (size_t j = 0; j < n; ++j) {
			cout << initial[matr[i][j]] << (j == n - 1 ? "" : ";");
		}
		cout << endl;
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
