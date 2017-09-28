/*
 * BinaryTrie.cpp
 *
 *  Created on: Sep 26, 2017
 *      Author: Dhiraj Borade
 */

#include <iostream>
#include "BinaryTrie.h"

using namespace std;

void BTrie::Add(tnode* ptr, unordered_map<int, int> des, int hop, int part,
		int bit) {

	int ip = des[part];				// part tells which btye in the IP address
	int flag = (ip & (1 << (7 - bit)));	// bit gives the exact position in the byte

	if (part == 4) {		// check if it is the last byte in the IP
		ptr->hop = hop;	// copy the next hop value
		ptr->type = 1;	// And mark the node as element node
		return;
	}

	if (bit < 7) {	// update the bit and part values for checking in next node
		bit++;
	} else {
		bit = 0;
		part++;
	}

	if (flag == 0) { // bit is 1
		if (ptr->left == NULL) {
			ptr->left = new tnode(0);
			ptr->left->parent = ptr;
		}
		Add(ptr->left, des, hop, part, bit);
	} else {	 // bit is 0
		if (ptr->right == NULL) {
			ptr->right = new tnode(0);
			ptr->right->parent = ptr;
		}
		Add(ptr->right, des, hop, part, bit);
	}
}

void BTrie::AddRoute(unordered_map<int, int> des, int hop) {

	if (root == NULL) {
		root = new tnode(0);
	}

	Add(root, des, hop, 0, 0); // Helper function

}

int BTrie::Find(tnode* ptr, unordered_map<int, int> des, int part, int bit) {
	int ip = des[part];				// part tells which btye in the IP address
	int flag = (ip & (1 << (7 - bit)));	// bit gives the exact position in the byte

	if (ptr->type == 1) {// if we reach an element node, return the next hop information
		return ptr->hop;
	}

	if (bit < 7) {	// update the bit and part values for checking in next node
		bit++;
	} else {
		bit = 0;
		part++;
	}

	if (flag == 0) { // bit is 1
		cout << 0;
		return Find(ptr->left, des, part, bit);
	} else {	 // bit is 0
		cout << 1;
		return Find(ptr->right, des, part, bit);
	}
}

int BTrie::FindRoute(unordered_map<int, int> des) {
	return Find(root, des, 0, 0); // helper function
}

void BTrie::pst(tnode* ptr) {
	if (ptr->left != NULL) {
		pst(ptr->left);
	}
	if (ptr->right != NULL) {
		pst(ptr->right);
	}

	// if we reach a element node, check for its sibling
	// if sibling exists and have same hop node, merge them and
	// store the hop information in parent node(previously parent node was branch node)
	if (ptr->left == NULL && ptr->right == NULL && ptr->type == 1) {
		if (ptr->parent->left == ptr) { // left child to parent
			if (ptr->parent->right != NULL) { // sibling exists
				if (ptr->parent->right->type == 1) { // sibling is an element node
					if (ptr->parent->right->hop == ptr->hop) { // check if hop node is same
						ptr->parent->type = 1; // make the parent node an element node
						ptr->parent->hop = ptr->hop;
						ptr->parent->right = NULL;
						ptr->parent->left = NULL;
					}
				}
			} else {
				ptr->parent->type = 1;
				ptr->parent->hop = ptr->hop;
				ptr->parent->right = NULL;
				ptr->parent->left = NULL;
			}

		} else { // right child to parent
			if (ptr->parent->left != NULL) {
				if (ptr->parent->left->type == 1) {
					if (ptr->parent->left->hop == ptr->hop) {
						ptr->parent->type = 1;
						ptr->parent->hop = ptr->hop;
						ptr->parent->left = NULL;
						ptr->parent->right = NULL;
					}
				}
			} else {
				ptr->parent->type = 1;
				ptr->parent->hop = ptr->hop;
				ptr->parent->left = NULL;
				ptr->parent->right = NULL;
			}
		}
	}

}

void BTrie::PostOrderTraversal() {
	pst(root); // helper function to trim the subtries with same hop information
}
