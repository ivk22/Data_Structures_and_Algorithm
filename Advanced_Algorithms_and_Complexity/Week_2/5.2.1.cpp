// 5.2.1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iomanip>
#include <iostream>
using namespace std;

void Single_Elimination(size_t& i, double**& matr, double*& E, size_t n) {
	if (!matr[i][i]) {
		for (size_t j = i + 1; j < n; ++j) {
			if (matr[j][i]) {
				swap(matr[i], matr[j]);
				swap(E[i], E[j]);
				break;
			}
		}
	}
	double frac = matr[i][i];

	for (size_t j = i; j < n; ++j) {
		matr[i][j] /= frac;
	}
	E[i]/= frac;

	for (size_t j = 0; j < n; ++j) {
		if (j != i) {
			double val = matr[j][i];

			for (size_t k = i; k < n; ++k) {
				matr[j][k] -= val * matr[i][k];
			}

			E[j] -= val * E[i];

		}
	}
}

void Gaussian_Elimination(double**& matr, double*& E,size_t& n) {
	for (size_t i = 0; i < n; ++i) {
		Single_Elimination(i,matr,E,n);
	}
}

int main()
{
	size_t n = 0;
	cin >> n;
	double** matr = new double*[n];
	double* E = new double[n];

	for (size_t i = 0; i < n; ++i) {
		matr[i]= new double[n];
		for (size_t j = 0; j < n; ++j) {
			cin >> matr[i][j];
		}
		cin >> E[i];
	}

	Gaussian_Elimination(matr,E,n);



	for (size_t i = 0; i < n; ++i) {
		cout << setprecision(9)<< E[i] << " ";
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
