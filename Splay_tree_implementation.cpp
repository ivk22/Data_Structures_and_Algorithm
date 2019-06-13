// 2.6.5.cpp : This file contains the 'main' function. Program execution begins and ends there.
//


#include <iostream>
#include <string>
#include <queue>
#include <ostream>
#include <sstream>
#include <iterator>
#include <list>
#include <algorithm>
#include <vector>
#include <random>

using namespace std;

template <class T>
class Splay_Tree {
	T key, sm;
	size_t size, height;
	Splay_Tree* left;
	Splay_Tree* right;
	Splay_Tree* parent;

	void Update_params() {
		size = 1 + right->size + left->size;
		height = 1 + max(right->height, left->height);
		sm = key + right->sm + left->sm;
	}


	Splay_Tree* Find(T x) {
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


	Splay_Tree* LeftDescendant() {
		if (left->size == 0) {
			return this;
		}
		return left->LeftDescendant();
	}

	Splay_Tree* RightAncestor() {
		if (parent == nullptr) {
			return nullptr;
		}
		if (parent->key > key) {
			return parent;
		}
		return parent->RightAncestor();
	}

	Splay_Tree* Next() {
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

	Splay_Tree* Prev() {
		if (!Is_Empty()) {
			if (!(left->Is_Empty())) {
				Splay_Tree* cur = left;
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
				Splay_Tree* cur = parent;
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
			Splay_Tree* cur = parent;
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

			Splay_Tree* one = parent->left;
			Splay_Tree* two = left;
			Splay_Tree* three = right;
			T old_key = key;

			key = parent->key;
			parent->key = old_key;
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

			Splay_Tree* Q = parent->parent;
			Splay_Tree* P = parent;
			Splay_Tree* one = Q->left;
			Splay_Tree* two = P->left;
			Splay_Tree* three = left;
			Splay_Tree* four = right;
			T old_key = key;

			key = Q->key;
			Q->key = old_key;
			Q->right = four;
			four->parent = Q;
			Q->left = P;
			P->right = three;
			three->parent = P;
			P->left = this;
			left = one;
			one->parent = this;
			right = two;
			two->parent = this;
			Update_params();
			P->Update_params();
			Q->Update_params();
		}
		if (res == -3) {

			Splay_Tree* Q = parent->parent;
			Splay_Tree* P = parent;
			Splay_Tree* one = Q->right;
			Splay_Tree* two = P->left;
			Splay_Tree* three = left;
			Splay_Tree* four = right;
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
			Splay_Tree* one = left;
			Splay_Tree* two = right;
			Splay_Tree* three = parent->right;
			T old_key = key;

			key = parent->key;
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
			Splay_Tree* P = parent;
			Splay_Tree* Q = parent->parent;
			Splay_Tree* one = left;
			Splay_Tree* two = right;
			Splay_Tree* three = P->right;
			Splay_Tree* four = Q->right;
			T old_key = key;

			key = Q->key;
			Q->key = old_key;
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
			Splay_Tree* Q = parent->parent;
			Splay_Tree* P = parent;
			Splay_Tree* one = Q->left;
			Splay_Tree* two = P->right;
			Splay_Tree* three = right;
			Splay_Tree* four = left;
			T old_key = key;
			key = Q->key;
			Q->key = old_key;
			Q->left = this;
			parent = Q;
			left = one;
			one->parent = this;
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
					Splay_Tree* cur = parent;
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
			left = new Splay_Tree();
			left->parent = this;
			right = new Splay_Tree();
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

	Splay_Tree() {
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

	void ST_Add(T x) {
		if (size == 0) {
			key = x;
			sm = key;
			size = 1;
			height = 1;
			left = new Splay_Tree();
			left->parent = this;
			right = new Splay_Tree();
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

	bool ST_Find(T x) {
		Splay_Tree* res = Find(x);
		bool f = (!(res->Is_Empty()));
		res->Splay();
		return f;
	}

	void ST_Delete(T x) {
		if (!Is_Empty()) {
			bool res = ST_Find(x);
			if (res) {
				if (!(right->Is_Empty())) {
					Splay_Tree* ptr = Next();

					right->parent = nullptr;
					ptr->Splay();

					Splay_Tree* old_right = right;

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
					Splay_Tree* old_left = left;

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

	T Range_Sum(T mn, T mx) {
		if (Is_Empty()) {
			return 0;
		}
		T val = 0;

		ST_Find(mn);

		if (key > mx) {
			return val;
		}

		if (key < mn) {
			if (right->Is_Empty()) {
				return val;
			}
			ST_Find(Next()->key);

			if (key > mx) {
				return val;
			}

		}

		val = key;
		if (right->Is_Empty()) {
			return val;
		}

		right->parent = nullptr;

		right->ST_Find(mx);

		if (right->key > mx) {
			if (right->left->Is_Empty()) {
				right->parent = this;
				return val;
			}
			right->Prev()->Splay();
		}

		val += right->key + right->left->sm;
		right->parent = this;
		return val;

	}

	size_t Get_Size() {
		return size;
	}

	size_t Get_Height() {
		return height;
	}

	T Range_Search(T mn, T mx) {
		T l = 0;
		Splay_Tree* start = Find(mn);
		while (true) {
			if (start != nullptr) {
				if (start->size > 0) {
					if (start->key <= mx) {
						l += start->key;
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


