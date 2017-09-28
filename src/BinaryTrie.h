/*
 * BinaryTrie.h
 *
 *  Created on: Sep 26, 2017
 *      Author: Dhiraj Borade
 */

#ifndef BINARY_TRIE_H
#define BINARY_TRIE_H
#include <unordered_map>

using namespace std;

struct tnode {
	int hop;		// stores next hop information if it is element node
	int type;		// specifies whether node is branch node or element node
	tnode* left;
	tnode* right;
	tnode* parent;
	tnode(int x) {	// Constructor
		type = x;
		hop = -1;
		left = NULL;
		right = NULL;
		parent = NULL;
	}
};

class BTrie {
private:
	tnode* root;
public:
	BTrie() {
		root = NULL;
	}
	void AddRoute(unordered_map<int, int>, int);
	int FindRoute(unordered_map<int, int>);
	void PostOrderTraversal();
	void Add(tnode*, unordered_map<int, int>, int, int, int);
	int Find(tnode*, unordered_map<int, int>, int, int);
	void pst(tnode*);

};

#endif
