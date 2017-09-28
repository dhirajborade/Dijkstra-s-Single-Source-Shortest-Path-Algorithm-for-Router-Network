/*
 * Dijkstra.cpp
 *
 *  Created on: Sep 26, 2017
 *      Author: Dhiraj Borade
 */

#include <iostream>
#include "dijkstra.h"

using namespace std;

vector<int> dijkstra(unordered_map<int, unordered_map<int, int>> &G, int src,
		int des) {
	int* dist = new int[G.size()];
	int* prev = new int[G.size()];
	unordered_map<int, node*> addr;
	Fibonacci_heap fh;
	vector<int> path;
	int count = 0;
	for (int i = 0; i < G.size(); i++) {
		if (i == src) {
			dist[i] = 0;
			addr[i] = fh.Insert(i, 0);
		} else {
			dist[i] = INT_MAX;
			addr[i] = fh.Insert(i, INT_MAX);
		}
		count++;
	}

	while (!fh.empty()) {
		node *n = fh.RemoveMin();

		if (n->vertex == des) {
			int temp = des;
			while (prev[temp] != src) {
				path.insert(path.begin(), temp);
				temp = prev[temp];
			}
			path.insert(path.begin(), temp);
			path.insert(path.begin(), src);
			break;
		}
		for (auto i : G[n->vertex]) {  // update dist for neighbours

			int newdist = dist[n->vertex] + i.second;
			if (newdist < dist[i.first]) {
				fh.DecreaseKey(addr[i.first], newdist);
				dist[i.first] = newdist;
				prev[i.first] = n->vertex;
			}
		}
	}
	cout << endl;
	return path;
}
