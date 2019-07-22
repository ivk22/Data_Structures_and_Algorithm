// 2.6.5.cpp : This file contains the 'main' function. Program execution begins and ends there.
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
#include <random>
using namespace std;

template <class T>
class Custom_Set {
	T key,sm;
	size_t size, height;
	Custom_Set* left;
	Custom_Set* right;
	Custom_Set* parent;

	void Update_params() {
		size = 1 + right->size + left->size;
		height = 1 + max(right->height, left->height);
		sm=key+right->sm + left->sm;
	}

	void RotateLeft() {

		Custom_Set* rr = right->right;

		Custom_Set* new_left = new Custom_Set();

		new_left->right = left->right;
		new_left->left = left->left;

		if (left->size != 0) {
			new_left->key = left->key;
			left->left->parent = new_left;
			left->right->parent = new_left;
		}


		new_left->size = left->size;
		new_left->height = left->height;
		new_left->sm = left->sm;
		new_left->parent = left;


		left->key = key;
		left->left = new_left;
		left->right = right->left;

		right->left->parent = left;

		left->Update_params();

		key = right->key;

		delete right;

		right = rr;
		rr->parent = this;

		Update_params();

	}

	void RotateRight() {

		Custom_Set* ll = left->left;

		Custom_Set* new_right = new Custom_Set();


		new_right->right = right->right;
		new_right->left = right->left;

		if (right->size != 0) {
			new_right->key = right->key;
			right->left->parent = new_right;
			right->right->parent = new_right;
		}


		new_right->size = right->size;
		new_right->sm = right->sm;
		new_right->height = right->height;
		new_right->parent = right;

		right->key = key;
		right->right = new_right;
		right->left = left->right;

		left->right->parent = right;

		right->Update_params();

		key = left->key;

		delete left;

		left = ll;
		ll->parent = this;

		Update_params();

	}

	void RebalanceLeft() {
		if (left->right->height > left->left->height) {
			left->RotateLeft();
		}
		RotateRight();
	}

	void RebalanceRight() {
		if (right->left->height > right->right->height) {
			right->RotateRight();
		}
		RotateLeft();
	}


	void Rebalance() {

		if (left->height > right->height + 1) {
			RebalanceLeft();
		}
		else if (right->height > left->height + 1) {
			RebalanceRight();
		}

		Update_params();

		if (parent != nullptr) {
			parent->Rebalance();
		}

	}





	Custom_Set* Find(T x) {
		if (key == x || size == 0) {
			return this;
		}
		if (x > key) {
			right->Find(x);
		}
		else {
			left->Find(x);
		}
	}


	Custom_Set* LeftDescendant() {
		if (left->size == 0) {
			return this;
		}
		return left->LeftDescendant();
	}

	Custom_Set* RightAncestor() {
		if (parent == nullptr) {
			return nullptr;
		}
		if (parent->key > key) {
			return parent;
		}
		return parent->RightAncestor();
	}

	Custom_Set* Next() {
		if (size != 0) {
			if (right->size != 0) {
				return right->LeftDescendant();
			}
			else {
				return RightAncestor();
			}
		}
		else {
			if (parent != nullptr) {
				if (this == parent->right) {
					return parent->Next();
				}
				else {
					return parent;
				}

			}
			else {
				return nullptr;
			}

		}

	}



	Custom_Set* Prev() {
		if (!Is_Empty()) {
			if (!(left->Is_Empty())) {
				Custom_Set* cur = left;
				while (!(cur->right->Is_Empty())) {
					cur = cur->right;
				}
				return cur;
			}
			else {
				if (parent == nullptr) {
					return nullptr;
				}
				if (parent->key < key) {
					return parent;
				}
				Custom_Set* cur = parent;
				while (true) {
					if (cur->parent == nullptr) {
						return nullptr;
					}
					if (cur->parent->key > cur->key) {
						cur = cur->parent;
					}
					else {
						return cur->parent;
					}
				}
			}

		}
		else {
			if (parent == nullptr) {
				return nullptr;
			}
			if (parent->right == this) {
				return parent;
			}
			Custom_Set* cur = parent;
			while (true) {
				if (cur->parent == nullptr) {
					return nullptr;
				}
				if (cur->parent->key > cur->key) {
					cur = cur->parent;
				}
				else {
					return cur->parent;
				}
			}
		}


	}


	int Case() {
		if (parent == nullptr) {
			return 0;
		}
		if (parent->parent == nullptr) {
			if (parent->key > key) {
				return -1;
			}
			return 1;
		}
		if (parent->parent->key > parent->key) {
			if (parent->key > key) {
				return -2;
			}
			return -3;
		}

		if (parent->parent->key < parent->key) {
			if (parent->key < key) {
				return 2;
			}
			return 3;
		}
	}


	void Local_splay(int res) {
		if (res == 1) {

			Custom_Set* one = parent->left;
			Custom_Set* two = left;
			Custom_Set* three = right;
			T old_key = key;

			key = parent->key;
			parent->key= old_key;
			parent->right = three;

			three->parent = parent;
			parent->left = this;
			right = two;
			left = one;
			one->parent = this;
			Update_params();
			parent->Update_params();
		}
		if (res == 2) {

			Custom_Set* Q = parent->parent;
			Custom_Set* P = parent;
			Custom_Set* one = Q->left;
			Custom_Set* two = P->left;
			Custom_Set* three = left;
			Custom_Set* four = right;
			T old_key = key;

			key = Q->key;
			Q->key=old_key;
			Q->right = four;
			four->parent = Q;
			Q->left = P;
			P->right= three;
			three->parent = P;
			P->left = this;
			left = one;
			one->parent= this;
			right = two;
			two->parent= this;
			Update_params();
			P->Update_params();
			Q->Update_params();
		}
		if (res == -3) {

			Custom_Set* Q = parent->parent;
			Custom_Set* P = parent;
			Custom_Set* one = Q->right;
			Custom_Set* two = P->left;
			Custom_Set* three = left;
			Custom_Set* four = right;
			T old_key = key;

			key = Q->key;
			Q->key = old_key;

			P->right = three;
			three->parent = P;

			Q->right = this;
			parent = Q;

			left = four;
			right = one;
			one->parent = this;
			Update_params();
			P->Update_params();
			Q->Update_params();

		}
		if (res == -1) {
			Custom_Set* one = left;
			Custom_Set* two = right;
			Custom_Set* three = parent->right;
			T old_key = key;

			key=parent->key;
			parent->key = old_key;

			parent->left = one;
			one->parent = parent;
			parent->right = this;
			left = two;
			right = three;
			three->parent = this;
			Update_params();
			parent->Update_params();
		}
		if (res == -2) {
			Custom_Set* P = parent;
			Custom_Set* Q = parent->parent;
			Custom_Set* one = left;
			Custom_Set* two = right;
			Custom_Set* three = P->right;
			Custom_Set* four = Q->right;
			T old_key = key;

			key = Q->key;
			Q->key= old_key;
			Q->left = one;
			one->parent = Q;
			Q->right = P;
			P->left = two;
			two->parent = P;
			P->right = this;
			left = three;
			three->parent = this;
			right = four;
			four->parent = this;
			Update_params();
			P->Update_params();
			Q->Update_params();
		}
		if (res == 3) {
			Custom_Set* Q = parent->parent;
			Custom_Set* P = parent;
			Custom_Set* one = Q->left;
			Custom_Set* two = P->right;
			Custom_Set* three = right;
			Custom_Set* four = left;
			T old_key = key;
			key = Q->key;
			Q->key = old_key;
			Q->left = this;
			parent = Q;
			left = one;
			one->parent= this;
			right = four;
			P->left = three;
			three->parent = P;
			Update_params();
			P->Update_params();
			Q->Update_params();
		}
	}

	void Splay() {
		if (Is_Empty()) {
			if (parent != nullptr) {
				int res = parent->Case();
				
				if (res != 0) {
					T val = parent->key;
					parent->Local_splay(res);
					Custom_Set* cur = parent;
					while (cur->key != val) {
						cur = cur->parent;
					}
					cur->Splay();
				}
			}
		}
		else {
			int res = Case();
			if (res != 0) {
				T val = key;
				Local_splay(res);
				if (parent->key != val) {
					parent->parent->Splay();
				}
				else {
					parent->Splay();
				}
			}
		}
	}

	void Add(T x) {
		if (size == 0) {
			key = x;
			size = 1;
			height = 1;
			left = new Custom_Set();
			left->parent = this;
			right = new Custom_Set();
			right->parent = this;
			return;
		}
		if (key == x) {
			return;
		}
		if (x < key) {
			left->Add(x);
		}
		else {
			right->Add(x);

		}
		Update_params();

	}


public:

	Custom_Set() {
		parent = nullptr;
		size = 0;
		height = 0;
		key = 0;
		sm = 0;
		left = nullptr;
		right = nullptr;


	}

	bool Is_Empty() {
		if (size == 0) {
			return 1;
		}
		return 0;
	}

	bool Find_(T x) {
		Custom_Set* res = Find(x);

		if (res->size == 0) {
			return 0;
		}
		return 1;
	}



	void AVL_Add(T x) {
		Add(x);
		Custom_Set* N = Find(x);
		N->Rebalance();

	}

	void ST_Add(T x) {
		if (size == 0) {
			key = x;
			sm = key;
			size = 1;
			height = 1;
			left = new Custom_Set();
			left->parent = this;
			right = new Custom_Set();
			right->parent = this;
			if (parent != nullptr) {
				parent->Update_params();
			}
			Splay();
			return;
		}
		if (key == x) {
			return;
		}
		if (x < key) {
			left->ST_Add(x);
		}
		else {
			right->ST_Add(x);

		}


	}



	bool STFind(T x) {
		Custom_Set* res = Find(x);
		bool f = (!(res->Is_Empty()));
		res->Splay();
		return f;
	}

	void STDelete(T x) {
		if (!Is_Empty()) {
			bool res = STFind(x);
			if (res) {
				if (!(right->Is_Empty())) {
					Custom_Set* ptr = Next();

					right->parent = nullptr;
					ptr->Splay();

					Custom_Set* old_right = right;

					delete old_right->left;

					key = right->key;

					right = right->right;
					right->parent = this;
					delete old_right;
					Update_params();
				}
				else {
					delete right;
					if (left->Is_Empty()) {
						delete left;
						size = 0;
						height = 0;
						sm = 0;
						key = 0;
						left = nullptr;
						right = nullptr;
						return;
					}
					Custom_Set* old_left = left;

					key = left->key;
					
					right = left->right;
					right->parent = this;
					left = left->left;
					left->parent = this;

					delete old_left;
					Update_params();

				}

			}
		}
	}

	void Delete(T x) {
		Custom_Set* res = Find(x);
		if (res->size != 0) {
			if (res->left->size == 0 && res->right->size == 0) {


				Custom_Set* par = res->parent;

				delete res->left;
				delete res->right;
				if (par == nullptr) {
					res->size = 0;
					res->height = 0;
					res->left = nullptr;
					res->right = nullptr;
					return;
				}

				Custom_Set* nw = new Custom_Set();

				if (par->key > res->key) {

					par->left = nw;
					nw->parent = par;
				}
				else {
					par->right = nw;
					nw->parent = par;
				}
				delete res;
				par->Rebalance();
				return;



			}

			if (res->right->size == 0)
			{
				Custom_Set* old_left_left = res->left->left;
				Custom_Set* old_left_right = res->left->right;

				res->key = res->left->key;
				res->size = res->left->size;
				res->height = res->left->height;
				res->sm = res->left->sm;
				delete res->left;
				res->left = old_left_left;
				res->right = old_left_right;

				old_left_left->parent = res;

				old_left_right->parent = res;

				if (res->parent != nullptr) {
					res->parent->Rebalance();
				}
				return;
			}

			Custom_Set* nxt = res->Next();


			res->key = nxt->key;
			if (nxt->right->size > 0) {
				Custom_Set* old_next_right = nxt->right->right;
				nxt->key = nxt->right->key;
				nxt->size = nxt->right->size;
				nxt->height = nxt->right->height;
				nxt->sm= nxt->right->sm;
				delete nxt->left;

				nxt->left = nxt->right->left;
				nxt->right->left->parent = nxt;

				delete nxt->right;
				nxt->right = old_next_right;
				old_next_right->parent = nxt;

				if (nxt->parent != nullptr) {
					nxt->parent->Rebalance();
				}

				return;
			}

			nxt->size = 0;
			nxt->height = 0;

			delete nxt->right;
			nxt->right = nullptr;

			delete nxt->left;
			nxt->left = nullptr;

			if (nxt->parent != nullptr) {
				nxt->parent->Rebalance();
			}

		}
	}




	T Ragne_Search(T mn, T mx) {
		if (Is_Empty()) {
			return 0;
		}
		T val=0;

		STFind(mn);

		if (key > mx) {
			return val;
		}

		if (key < mn) {
			if (right->Is_Empty()) {
				return val;
			}
			STFind(Next()->key);

			if (key > mx) {
				return val;
			}

		}

		val = key;
		if (right->Is_Empty()) {
			return val;
		}

		right->parent = nullptr;

		right->STFind(mx);

		if (right->key > mx) {
			if (right->left->Is_Empty()) {
				right->parent = this;
				return val;
			}
			right->Prev()->Splay();
		}

		val += right->key+ right->left->sm;
		right->parent = this;
		return val;
		
	}

	size_t Get_Size() {
		return size;
	}

	size_t Get_Height() {
		return height;
	}

	T List_Search(T mn, T mx) {
		T l=0;
		Custom_Set* start = Find(mn);
		while (true) {
			if (start != nullptr) {
				if (start->size > 0) {
					if (start->key <= mx) {
						l+=start->key;
					}
					else {
						break;
					}
				}
			}
			else {
				break;
			}
			start = start->Next();
		}
		return l;
	}

	void InOrder() {
		if (left != nullptr) {
			left->InOrder();
		}
		if (size != 0) {
			cout << key << " ";
		}
		if (right != nullptr) {
			right->InOrder();
		}

	}

	void PreOrder() {

		if (size != 0) {
			cout << key << " ";
		}

		if (left != nullptr) {
			left->PreOrder();
		}

		if (right != nullptr) {
			right->PreOrder();
		}

	}

	void PostOrder() {

		if (left != nullptr) {
			left->PostOrder();
		}

		if (right != nullptr) {
			right->PostOrder();
		}

		if (size != 0) {
			cout << key << " ";
		}

	}

	T Get_Key() {
		return key;
	}

	T Get_Sum() {
		return sm;
	}

	bool Check_Sum() {
		if (Is_Empty()) {
			if (sm != 0) {
				return 1;
			}
			return 0;
		}

		if (sm != key + left->sm + right->sm) {
			return 1;
		}
		bool v1 = left->Check_Sum();
		bool v2 = right->Check_Sum();
		return (v1 || v2);
	}


};



int main()
{



	uint64_t x = 0;

	Custom_Set<uint64_t> Set;
	
	uint64_t M = 1000000001, n = 0;
	cin >> n;

	queue<string> q;

	string s;
	getline(cin, s);
	for (size_t i = 0; i < n; ++i) {
		getline(cin, s);
		q.push(s);
	}

	while (!q.empty()) {
		s = q.front();
		stringstream ss(s);
		istream_iterator<string> begin(ss);

		istream_iterator<string> end;

		vector<string> v(begin, end);

		if (v[0] == "+") {
			Set.ST_Add((stoi(v[1]) + x) % M);
		}
		if (v[0] == "-") {
			Set.STDelete((stoi(v[1]) + x) % M);
		}
		if (v[0] == "?") {
			if (Set.STFind((stoi(v[1]) + x) % M)) {
				cout << "Found" << endl;
			}
			else {
				cout << "Not found" << endl;
			}
		}
		if (v[0] == "s") {
			x = Set.Ragne_Search((stoi(v[1]) + x) % M, (stoi(v[2]) + x) % M);

			cout << x << endl;

		}

		q.pop();
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
