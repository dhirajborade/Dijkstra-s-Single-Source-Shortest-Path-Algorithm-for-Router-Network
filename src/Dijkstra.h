/*
 * Dijkstra.h
 *
 *  Created on: Sep 26, 2017
 *      Author: Dhiraj Borade
 */

#ifndef DIJKSTRA_H
#define DIJKSTRA_H

#include <unordered_map>
#include <vector>
#include <climits>
#include <algorithm>
#include "Fibonacci.h"

using namespace std;

vector<int> dijkstra(unordered_map<int, unordered_map<int, int>>&, int, int);

#endif
