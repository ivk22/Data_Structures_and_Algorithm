// 2.4.3.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include <queue>
#include <ostream>
#include <sstream>
#include <iterator>
#include <cmath>
#include <list>
#include <algorithm>
#include <vector>


using namespace std;
uint64_t Power(uint64_t x, size_t n, size_t p) {
	uint64_t res = 1;
	while (n >= 1) {
		res = (res*x) % p;
		--n;
	}
	return res;
}


uint64_t power(uint64_t x, int64_t n, size_t p)
{
	uint64_t res = 1;      // Initialize result 

	x = x % p;  // Update x if it is more than or  
				// equal to p 

	while (n > 0)
	{
		// If y is odd, multiply x with result 
		if (n & 1)
			res = (res*x) % p;

		// y must be even now 
		n = n >> 1; // y = y/2 
		x = (x*x) % p;
	}
	return res;
}


uint64_t PolyHash(string::iterator s, size_t len, size_t p, uint64_t x) {
	uint64_t sm = 0;
	uint64_t mult = 1;
	for (size_t i = 0; i < len; ++i) {

		sm = (sm + mult *s[i]) % p;
		mult=(mult*x) % p;
	}

	return sm;
}

uint64_t* PrecompH(string & s, size_t P, uint64_t x, size_t p) {
	uint64_t* H=new uint64_t[s.size() - P + 1];
	uint64_t y = power(x, P, p);
	H[s.size() - P] = PolyHash(s.begin() + s.size() - P, P, p, x);
	for (int i = s.size() - P - 1; i >= 0; --i) {
		uint64_t v1 = ((x * H[i + 1]) % p)+s[i],v2 =(s[i + P] * y)%p;
		if (v2 > v1) {
			H[i] = p-((v2 - v1) % p);
		}
		else {
			H[i] = (v1 - v2) % p;
		}
		
	}
	return H;
}

bool AreEqual(string::iterator s, string P) {
	for (size_t i = 0; i < P.size(); ++i) {
		if (s[i] != P[i]) { return false; }
	}
	return true;
}


void Rubin_Karp(string s, string P, 
	uint64_t x, size_t p) {
	list<size_t> lst;
	uint64_t* H = PrecompH(s,P.size(),x,p);
	uint64_t pHash = PolyHash(P.begin(), P.size(),p,x);
	for (size_t i = 0; i <= s.size() - P.size(); ++i) {
		if (pHash == H[i]) {
			if (AreEqual(s.begin() + i, P)) {
				cout << i << " ";
			}
		}
	}

}


int main()
{


	size_t x = 263, p = 1000000007;
	string P, T;

	getline(cin, P);
	getline(cin, T);

	Rubin_Karp(T,P, x,p);


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
