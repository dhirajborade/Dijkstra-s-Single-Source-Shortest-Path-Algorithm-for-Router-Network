/*
 * Fibonacci.h
 *
 *  Created on: Sep 26, 2017
 *      Author: Dhiraj Borade
 */

#ifndef FIBONACCI_H
#define FIBONACCI_H
#include <iostream>
#include <cmath>

struct node {
	int degree;
	int vertex;
	int data;
	node* child;
	node* left;
	node* right;
	node* parent;
	bool childcut;
	bool mark;
	node(int x, int y) {   // Constructor for node structure.
		vertex = x;
		data = y;
		degree = 0;
		child = NULL;
		left = NULL;
		right = NULL;
		parent = NULL;
		childcut = false;
		mark = false;
	}
};

class Fibonacci_heap {

public:
	node* root;
	int num;
	Fibonacci_heap() {
		root = NULL;
		num = 0;
	}
	node* Insert(int, int);
	node* RemoveMin();
	void DecreaseKey(int, int, int);
	void DecreaseKey(node*, int);
	bool empty();
	void Link(node*, node*);
	void Consolidate();
	node* Find(node*, int, int);
	void Cut(node*, node*);
	void Cascade_Cut(node*);
	bool Treechecker();
	bool checker(node*, int, int);

};

#endif
