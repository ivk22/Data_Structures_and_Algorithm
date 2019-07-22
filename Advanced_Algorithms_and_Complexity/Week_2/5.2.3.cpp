// Simplex_open.cpp : This file contains the 'main' function. Program execution begins and ends there.
//


#include <vector>
#include <iostream>
#include <list>
#include <iomanip>
#include <cmath>
#include <math.h>


using namespace std;

vector<vector<double>> Simplex_table(vector<vector<double>>& A,
	vector<double>& b, vector<double>& maxFunc) {
	size_t num_Vars = maxFunc.size();
	size_t num_Ineq = A.size();

	vector<vector<double>> Simplex(num_Ineq + 1);
	for (size_t i = 0; i < num_Ineq; ++i) {
		Simplex[i] = vector<double>(num_Vars + num_Ineq + 2, 0);

		Simplex[i][0] = num_Vars+i+1;

		for (size_t j = 1; j <= num_Vars; ++j) {
			Simplex[i][j] = A[i][j-1];
		}

		Simplex[i][num_Vars + i+1] = 1;

		Simplex[i][Simplex[i].size() - 1] = b[i];
	}

	Simplex[num_Ineq] = vector<double>(num_Vars + num_Ineq + 2, 0);



	for (size_t i = 1; i <= num_Vars; ++i) {
		Simplex[num_Ineq][i] = maxFunc[i-1];
	}

	return Simplex;
}


pair<int, int> Next(vector<vector<double>>& Simplex) {

	size_t numRows = Simplex.size(), numCols = Simplex[0].size();

	int pivotCol = -1;

	for (size_t i = 1; i < numCols - 1; ++i) {
		if (Simplex[numRows - 1][i] > 0) {
			pivotCol = i;
			break;
		}
	}

	if (pivotCol == -1) {
		return { 0,-1 };
	}

	int pivotRow = -1;

	pair<double, size_t> mn = { 0.0 , 0};

	for (size_t i = 0; i < numRows - 1; ++i) {
		if (Simplex[i][pivotCol] > 0) {
			pair<double, size_t> ratio = { Simplex[i][numCols - 1] / Simplex[i][pivotCol] , Simplex[i][0] };
			if (ratio < mn || pivotRow == -1) {
				pivotRow = i;
				mn = ratio;
			}
		}
	}

	return{ pivotRow , pivotCol };

}

void Printtable(vector<vector<double>>& Simplex) {
	for (size_t i = 0; i < Simplex.size(); ++i) {
		for (size_t j = 0; j < Simplex[0].size(); ++j) {
			cout << Simplex[i][j] << "\t";
		}
		cout << endl;
	}
	cout << endl;
}

void Pivoting(vector<vector<double>>& Simplex, size_t PivotRow,
	size_t PivotCol) {

	Simplex[PivotRow][0] = PivotCol;

	double pivot = Simplex[PivotRow][PivotCol];


	for (size_t i = 1; i < Simplex[PivotRow].size(); ++i) {
		Simplex[PivotRow][i] /= pivot;
	}

	

	for (size_t i = 0; i < Simplex.size(); ++i) {
		if (i != PivotRow) {
			double ratio = Simplex[i][PivotCol];
			for (size_t j = 1; j < Simplex[i].size(); ++j) {
				if (i == Simplex.size() - 1 && j == Simplex[i].size() - 1) {
					Simplex[i][j] += ratio * Simplex[PivotRow][j];
				}
				else {
					Simplex[i][j] -= ratio * Simplex[PivotRow][j];
				}

			}
		}
		
	}

}




bool Simplex_Solver(vector<vector<double>>& Simplex) {
	pair<int, int> p;

	while (true) {

		p = Next(Simplex);

		if (p.first == -1) {
			return 0;
		}
		if (p.second == -1) {
			return 1;
		}

		Pivoting(Simplex, p.first, p.second);

	}
}



vector<vector<double>>
Initialize_Simplex(vector<vector<double>>& A,
	vector<double>& b, vector<double>& maxFunc) {

	size_t num_Vars = maxFunc.size();
	size_t num_Ineq = A.size();

	bool negative = false;
	double mn = 0;
	size_t min_ind = 0;
	for (size_t i = 0; i < num_Ineq; ++i) {
		if (b[i] < 0) {
			if (b[i] < mn || !negative) {
				negative = true;
				mn = b[i];
				min_ind = i;
			}
		}
	}


	if (!negative) {
		vector<vector<double>> Simplex = Simplex_table(A, b, maxFunc);
		return Simplex;
	}

	vector<vector<double>> A_adj(A.size());

	for (size_t i = 0; i < A_adj.size(); ++i) {

		A_adj[i] = vector<double>(num_Vars + 1, 0);
		A_adj[i][0] = -1;
		for (size_t j = 1; j <= num_Vars; ++j) {
			A_adj[i][j] = A[i][j - 1];
		}

	}


	vector<double> maxFunc_adj(num_Vars + 1, 0);
	maxFunc_adj[0] = -1;


	vector<vector<double>> Simplex_adj = Simplex_table(A_adj, b, maxFunc_adj);


	Pivoting(Simplex_adj, min_ind, 1);

	Simplex_Solver(Simplex_adj);


	double result = Simplex_adj[Simplex_adj.size() - 1][Simplex_adj[0].size() - 1];

	double denom = pow(10, -5);

	if (abs(result) < denom) {

		bool zero_basis = true;

		bool first = 0;

		size_t ind = 0;
		for (size_t i = 0; i < Simplex_adj.size() - 1; ++i) {

			if (Simplex_adj[i][1]) {
				if (first || Simplex_adj[i][1] != 1.0) {
					zero_basis = false;
					break;
				}
				else {
					first = 1;
					ind = i;
				}
			}

		}

		if (zero_basis) {
			size_t col = 0;

			for (size_t i = 2; i < Simplex_adj[ind].size(); ++i)
			{
				if (Simplex_adj[ind][i]) {
					col = i;
					Pivoting(Simplex_adj, ind, col);
					break;
				}
			}
		}

		vector<vector<double>> res(Simplex_adj.size());

		for (size_t i = 0; i < res.size() - 1; ++i) {

			res[i] = vector<double>(Simplex_adj[i].size() - 1);

			res[i][0] = Simplex_adj[i][0]-1;

			for (size_t j = 1; j < res[i].size(); ++j) {
				res[i][j] = Simplex_adj[i][j + 1];
			}

		}

		res[res.size() - 1] = vector<double>(Simplex_adj[0].size() - 1, 0);

		for (size_t j = 1; j <= maxFunc.size(); ++j) {

			double val = maxFunc[j-1];

			bool first = false;
			size_t ind = 0;

			for (size_t i = 0; i < res.size() - 1; ++i) {
				if (res[i][j]) {

					if (res[i][j] != 1.0 || first) {
						res[res.size() - 1][j] += val;
						break;
					}

					if (!first && res[i][j] == 1.0) {
						first = true;
						ind = i;
					}

				}
				if (i == res.size() - 2) {
					for (size_t k = 1; k < res[0].size() - 1; ++k) {
						if (k != j) {
							res[res.size() - 1][k] -= val * res[ind][k];
						}
					}
					res[res.size() - 1][res[0].size() - 1] += val * res[ind][res[0].size() - 1];
				}
			}
		}



		return res;
	}
	return vector<vector<double>>();

}


void General_Simplex_Solver(vector<vector<double>>& A,
	vector<double>& b, vector<double>& maxFunc) {

	vector<vector<double>> Simplex = Initialize_Simplex(A, b, maxFunc);

	if (!Simplex.size()) {
		cout << "No solution";
		return;
	}

	bool res = Simplex_Solver(Simplex);



	if (!res) {
		cout << "Infinity";
		return;
	}

	list<double> lst;

	for (size_t i = 1; i <= maxFunc.size(); ++i) {

		bool first = false;
		size_t ind = 0;

		for (size_t j = 0; j < Simplex.size(); ++j) {
			if (Simplex[j][i]) {

				if (Simplex[j][i] != 1.0 || first) {
					lst.push_back(0);
					break;
				}

				if (!first && Simplex[j][i] == 1.0) {
					first = true;
					ind = j;
				}

			}
			if (j == Simplex.size() - 1) {
				lst.push_back(Simplex[ind][Simplex[0].size() - 1]);
			}
		}
	}

	cout << "Bounded solution" << endl;

	for (const auto& val : lst) {
		cout << setprecision(20) << val << " ";
	}


}



int main()
{
	size_t n = 0, m = 0;
	cin >> n >> m;

	vector<vector<double>> A(n);
	vector<double> b(n);
	vector<double> maxFunc(m);

	for (size_t i = 0; i < n; ++i) {
		A[i] = vector<double>(m);
		for (size_t j = 0; j < m; ++j) {
			cin >> A[i][j];
		}
	}

	for (size_t i = 0; i < n; ++i) {
		cin >> b[i];
	}

	for (size_t i = 0; i < m; ++i) {
		cin >> maxFunc[i];
	}

	General_Simplex_Solver(A, b, maxFunc);

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
