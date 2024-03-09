#pragma once

#include <iostream>
#include <vector>
#include <tuple>
#include <fstream>

using namespace std;

typedef vector<vector<int>> inputMatrix;
typedef vector<vector<tuple<int, int, int>>> culcMatrix;

// Function for print matrix 
void printMatrix(inputMatrix&);
// Function for print matrix
void printMatrix(culcMatrix&);
// Function for read matrix from .txt file
inputMatrix readMatrix(string, int);
// Function for fill random matrix
inputMatrix fillRandomMatrix(int);
culcMatrix solveMatrix(inputMatrix&);