/*
 * SSSP.cpp
 *
 *  Created on: Sep 26, 2017
 *      Author: Dhiraj Borade
 */

#include <iostream>
#include <fstream>
#include <unordered_map>
#include <string>
#include <cstdlib>
#include <vector>
#include <ctime>
#include "Fibonacci.h"
#include "dijkstra.h"

using namespace std;

int main(int argc, char *argv[]) {

	// clock_t start = clock();
	string filename = argv[1];       // store file name with vertices
	int src = atoi(argv[2]);         // store source node value as integer
	int des = atoi(argv[3]);         // store destination node value as integer

	int n, m;
	// map to store node values and corresponding adjacency lists
	unordered_map<int, unordered_map<int, int>> G;

	string line;
	ifstream myfile(filename);
	myfile >> n; 		// Vertices
	myfile >> m;		// Edges
	int a, b, c;
	while (myfile >> a) {   // populate the adjacency lists
		myfile >> b >> c;
		G[a][b] = c;
		G[b][a] = c;
	}

	vector<int> spath;
	int sval = 0;

	spath = dijkstra(G, src, des);  // Run dijkstra to find shortest path

	// traverse through shortest path to find path weight
	for (int i = 0; i < spath.size() - 1; i++) {
		int s = spath[i];
		int d = spath[i + 1];
		sval += G[s][d];
	}

	cout << sval << endl;   // Print the path weight

	for (int i = 0; i < spath.size(); i++) { // print the path
		cout << spath[i] << " ";
	}
	cout << endl;

	// clock_t end = clock();
	// double msecs = ((double) (end - start)) * 1000 / CLOCKS_PER_SEC;
	// cout << "Time taken to run spp = " << msecs << " milliseconds" << endl;

	return 0;
}
