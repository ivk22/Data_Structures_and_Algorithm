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
class AVL_tree {
	T key, sm;
	size_t size, height;
	AVL_tree* left;
	AVL_tree* right;
	AVL_tree* parent;

	void Update_params() {
		size = 1 + right->size + left->size;
		height = 1 + max(right->height, left->height);
		sm = key + right->sm + left->sm;
	}

	void RotateLeft() {

		AVL_tree* rr = right->right;

		AVL_tree* new_left = new AVL_tree();

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

		AVL_tree* ll = left->left;

		AVL_tree* new_right = new AVL_tree();


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





	AVL_tree* Find(T x) {
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


	AVL_tree* LeftDescendant() {
		if (left->size == 0) {
			return this;
		}
		return left->LeftDescendant();
	}

	AVL_tree* RightAncestor() {
		if (parent == nullptr) {
			return nullptr;
		}
		if (parent->key > key) {
			return parent;
		}
		return parent->RightAncestor();
	}

	AVL_tree* Next() {
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



	AVL_tree* Prev() {
		if (!Is_Empty()) {
			if (!(left->Is_Empty())) {
				AVL_tree* cur = left;
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
				AVL_tree* cur = parent;
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
			AVL_tree* cur = parent;
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

	void Add(T x) {
		if (size == 0) {
			key = x;
			size = 1;
			height = 1;
			left = new AVL_tree();
			left->parent = this;
			right = new AVL_tree();
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

	AVL_tree() {
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

	bool AVL_Find(T x) {
		AVL_tree* res = Find(x);

		if (res->size == 0) {
			return 0;
		}
		return 1;
	}



	void AVL_Add(T x) {
		Add(x);
		AVL_tree* N = Find(x);
		N->Rebalance();

	}


	void AVL_Delete(T x) {
		AVL_tree* res = Find(x);
		if (res->size != 0) {
			if (res->left->size == 0 && res->right->size == 0) {


				AVL_tree* par = res->parent;

				delete res->left;
				delete res->right;
				if (par == nullptr) {
					res->size = 0;
					res->height = 0;
					res->left = nullptr;
					res->right = nullptr;
					return;
				}

				AVL_tree* nw = new AVL_tree();

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
				AVL_tree* old_left_left = res->left->left;
				AVL_tree* old_left_right = res->left->right;

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

			AVL_tree* nxt = res->Next();


			res->key = nxt->key;
			if (nxt->right->size > 0) {
				AVL_tree* old_next_right = nxt->right->right;
				nxt->key = nxt->right->key;
				nxt->size = nxt->right->size;
				nxt->height = nxt->right->height;
				nxt->sm = nxt->right->sm;
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


	size_t Get_Size() {
		return size;
	}

	size_t Get_Height() {
		return height;
	}

	T Range_sum(T mn, T mx) {
		T l = 0;
		AVL_tree* start = Find(mn);
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


};


// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
