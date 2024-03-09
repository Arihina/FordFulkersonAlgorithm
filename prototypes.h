#pragma once

#include <iostream>
#include <vector>
#include <tuple>
#include <fstream>
#include <set>
#include <string>

using namespace std;

typedef vector<vector<int>> inputMatrix;
typedef vector<vector<tuple<int, int, int>>> extendMatrix;

// Function for printing matrix 
void printMatrix(inputMatrix&);
// Function for printing matrix
void printMatrix(extendMatrix&);
// Function for reading matrix from .txt file
inputMatrix readMatrix(string, int);
// Function for filling random matrix
inputMatrix fillRandomMatrix(int);
// Function for extending input matrix
extendMatrix extendedMatrix(inputMatrix&);
// Function for getting node with max bandwidth
int getMaxNode(int, extendMatrix&, set<int>&);
// Function for getting max flow
int getMaxFlow(vector<tuple<int, int, int>>&);
// Function for updating weights of nodes
void updateNodesWeights(extendMatrix&, vector<tuple<int, int, int>>&, int);

vector<int> solve(extendMatrix&, inputMatrix&);