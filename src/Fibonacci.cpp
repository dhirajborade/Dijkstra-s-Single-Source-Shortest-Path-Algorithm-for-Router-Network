/*
 * Fibonacci.cpp
 *
 *  Created on: Sep 26, 2017
 *      Author: Dhiraj Borade
 */

#include <iostream>
#include <cmath>
#include <stack>
#include <vector>
#include <unordered_map>
#include "Fibonacci.h"

using namespace std;

node* Fibonacci_heap::Insert(int vertex, int dist) {
	if (root == NULL) {
		root = new node(vertex, dist);	// Allocate memory for root
		root->left = root;
		root->right = root;
		num++;
		return root;
	} else {
		node* n = new node(vertex, dist); // Allocate memory for the element to be inserted
		root->left->right = n;	// Insert node into root's doubly linked list
		n->right = root;
		n->left = root->left;
		root->left = n;
		if (n->data < root->data) { // Change root if the inserted element is the minimum.
			root = n;
		}
		num++;
		return n;
	}
}

void Fibonacci_heap::Link(node* p2, node* p1) {
	p2->left->right = p2->right; // sever connections of p2
	p2->right->left = p2->left;

	p2->parent = p1;		// Make p1 parent of p2
	if (p1->child == NULL) {	// Insert p2 into its child circular list
		p1->child = p2;
		p2->left = p2;
		p2->right = p2;
	} else {				// Insert p2 into p1's child circular linked list
		p2->right = p1->child;
		p2->left = p1->child->left;
		p1->child->left->right = p2;
		p1->child->left = p2;
	}

	p1->degree++; // Incriment the degree of p1
}

void Fibonacci_heap::Consolidate() {
	unordered_map<int, node*> mp;
	int d;

	node* r = root;
	node* p1 = root;

	stack<node*> s;
	s.push(r);
	r = r->right;
	while (r != root) {    		// Push all the subtrees into a stack
		s.push(r);
		r = r->right;
	}

	while (!s.empty()) {
		p1 = s.top();
		s.pop();
		d = p1->degree;
		while (mp.count(d) != 0) { // Check if array contains any subtree with same degree
			node* p2 = mp[d];
			if (p1->data > p2->data) {
				node* temp = p1;
				p1 = p2;
				p2 = temp;
			}
			Link(p2, p1);	// Link subtree with root p2 to subtree with root p1
			mp.erase(d);
			d++;
		}
		mp[d] = p1;
	}
	root = NULL;
	for (auto i : mp) {
		if (root == NULL) {
			root = i.second;
			root->left = root;
			root->right = root;
		} else {
			i.second->right = root;
			i.second->left = root->left;
			root->left->right = i.second;
			root->left = i.second;
			if (i.second->data < root->data) {
				root = i.second;
			}
		}
	}

}

node* Fibonacci_heap::RemoveMin() {
	if (root == NULL) {			// If heap is empty return NULL
		return NULL;
	}
	if (root->child == NULL && root->right == root) { // Only one element is present in the heap
		node* ptr = root;
		root = NULL;
		num--;
		return ptr;
	}
	node* r = root; // Store address of min node to return it at the end of function.
	node* child = root->child;
	node* rootend = root;
	node* childend = child;

	node* temp = root;
	if (root->child != NULL) {
		while (temp->right != root) {
			temp = temp->right;
			rootend = temp;
		}
		temp = root->child;
		child->parent = NULL;
		while (temp->right != child) {
			temp = temp->right;
			childend = temp;
			childend->parent = NULL;
		}
		if (child == childend) {
			root->left = child;
			child->right = root;
			rootend->right = childend;
			childend->left = rootend;

		} else if (root == rootend) {
			root->right = child;
			child->left = root;
			rootend->left = childend;
			childend->right = rootend;
		} else {
			rootend->right = child;
			child->left = rootend;
			childend->right = root;
			root->left = childend;
		}
	}

	r->left->right = r->right;  // Remove the min from the list.
	r->right->left = r->left;
	if (root == r) {
		root = root->right;
	}

	Consolidate();

	num--;
	return r;
}

node* Fibonacci_heap::Find(node* ptr, int vertex, int data) {

	if (ptr == NULL)
		return NULL;
	ptr->mark = true;
	if (ptr->vertex == vertex) {
		ptr->mark = false;
		return ptr;
	}
	node *p = NULL;
	if (ptr->child != NULL) {
		if (ptr->data == data && ptr->vertex < vertex) {

			p = Find(ptr->child, vertex, data);
		} else if (ptr->data < data) {
			p = Find(ptr->child, vertex, data);
		}

	}
	if (p == NULL) {
		if (ptr->right->mark != true) {
			p = Find(ptr->right, vertex, data);
		}

	}
	ptr->mark = false;
	return p;
}

void Fibonacci_heap::DecreaseKey(node* ptr, int newdata) {
	if (root == NULL)
		return;

	if (ptr == NULL) {
		cout << "Not found in the heap!!" << endl;
		return;
	}

	if (ptr->data < newdata) {
		cout << "New value is less than actual value!!" << endl;
	}

	if (ptr == root) {
		root->data = newdata;
	}

	ptr->data = newdata;
	node *par = ptr->parent;

	if (par != NULL && ptr->data < par->data) {
		Cut(ptr, par);
		Cascade_Cut(par);
	}

	if (ptr->data < root->data) {
		root = ptr;
	}
}

void Fibonacci_heap::DecreaseKey(int vertex, int data, int newdata) {
	if (root == NULL)
		return;

	node *ptr = Find(root, vertex, data);

	if (ptr == NULL) {
		cout << "Not found in the heap!!" << endl;
		return;
	}

	if (ptr->data < newdata) {
		cout << "New value is less than actual value!!" << endl;
	}

	if (ptr == root) {
		root->data = newdata;
	}

	ptr->data = newdata;
	node *par = ptr->parent;

	if (par != NULL && ptr->data < par->data) {
		Cut(ptr, par);
		Cascade_Cut(par);
	}

	if (ptr->data <= root->data) {
		if (ptr->data == root->data && ptr->vertex < root->vertex) {
			root = ptr;
		} else if (ptr->data < root->data) {
			root = ptr;
		}
	}

}

void Fibonacci_heap::Cut(node* ptr, node* par) {
	if (ptr->right == ptr) {
		par->child = NULL;
	}
	ptr->left->right = ptr->right;
	ptr->right->left = ptr->left;
	if (ptr == par->child) {
		par->child = ptr->right;
	}

	par->degree--;

	root->left->right = ptr;
	ptr->right = root;
	ptr->left = root->left;
	root->left = ptr;

	ptr->parent = NULL;
	ptr->childcut = false;
}

void Fibonacci_heap::Cascade_Cut(node* ptr) {
	node *par = ptr->parent;
	if (par != NULL) {
		if (ptr->childcut == false) {
			ptr->childcut = true;
		} else {
			Cut(ptr, par);
			Cascade_Cut(par);
		}
	}
}

bool Fibonacci_heap::empty() {
	if (root == NULL) {
		return true;
	} else {
		return false;
	}
}

bool Fibonacci_heap::Treechecker() {
	return checker(root, -1, -1);
}

bool Fibonacci_heap::checker(node* ptr, int data, int vertex) {
	if (ptr == NULL) {
		return true;
	} else {
		if (ptr->data < data) {
			return false;
		} else if (ptr->data == data && ptr->vertex < vertex) {
			return false;
		} else {
			return checker(ptr->child, ptr->data, ptr->vertex);
		}
	}
}

