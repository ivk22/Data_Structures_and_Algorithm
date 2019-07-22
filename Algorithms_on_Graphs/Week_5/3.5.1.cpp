#include <algorithm>
#include <iostream>
#include <iomanip>
#include <vector>
#include <cmath>

using namespace std;
class Disjoint_Sets {

	size_t* rank;
	size_t* parent;


public:
	Disjoint_Sets(size_t n) {
		rank = new size_t[n + 1];
		parent = new size_t[n + 1];
		for (size_t i = 1; i <= n; ++i) {
			rank[i] = 1;
			parent[i] = i;
		}

	}

	size_t Find(size_t x) {
		if (parent[x] != x) {
			parent[x] = Find(parent[x]);
			return parent[x];
		}
		else {
			return x;
		}
	}

	void Union(size_t x, size_t y) {

		size_t x_id = Find(x);
		size_t y_id = Find(y);


		if (x_id != y_id) {
			if (rank[x_id] <= rank[y_id]) {
				parent[x_id] = y_id;
				if (rank[x_id] == rank[y_id]) {
					++rank[y_id];
				}
			}
			else {
				parent[y_id] = x_id;
			}
		}


	}

};

double dist(pair<double, double> a, pair<double, double> b) {

	double dx = (a.first - b.first)*(a.first - b.first);
	double dy = (a.second - b.second)*(a.second - b.second);

	return sqrt(dx + dy);
}

double Krust(size_t n,
	vector<pair<double, pair<size_t, size_t>>>& E) {
	double res = 0;
	Disjoint_Sets DS(n);
	for (size_t i = 0; i < E.size(); ++i) {
		pair<double, pair<size_t, size_t>> val = E[i];
		
		if (DS.Find(val.second.first) != DS.Find(val.second.second)) {
			
			res += val.first;
			DS.Union(val.second.first, val.second.second);
		}
	}
	return res;
}


int main() {
	size_t n = 0;
	cin >> n;

	pair<int, int>* points = new pair<int, int>[n + 1];

	for (size_t i = 1; i <= n; ++i) {
		cin >> points[i].first >> points[i].second;
	}

	vector<pair<double, pair<size_t, size_t>>> E((n*(n - 1)) / 2);

	size_t k = 0;

	for (size_t i = 1; i <= n - 1; ++i) {
		for (size_t j = i + 1; j <= n; ++j) {
			double val = dist(points[i], points[j]);

			E[k] = pair<double, pair<size_t, size_t>>{ val ,
				pair<size_t,size_t>{i,j} };
			++k;
		}
	}

	sort(E.begin(), E.end());



	std::cout << std::setprecision(10) << (double)Krust(n, E) << std::endl;
}
