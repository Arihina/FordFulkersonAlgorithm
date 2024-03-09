#include "prototypes.h"


void main()
{
	auto matrix = readMatrix("matrix.txt", 5);
	printMatrix(matrix);

	cout << endl;

	auto extendedMatrix = solveMatrix(matrix);
	printMatrix(extendedMatrix);
}


void printMatrix(inputMatrix& matrix) {
	for (int i = 0; i < matrix.size(); i++)
	{
		for (int j = 0; j < matrix[i].size(); j++)
		{
			cout << matrix[i][j] << " ";
		}
		cout << endl;
	}
}

void printMatrix(culcMatrix& matrix) {
	for (int i = 0; i < matrix.size(); i++)
	{
		for (int j = 0; j < matrix[i].size(); j++)
		{
			cout << get<0>(matrix[i][j]) << " " << get<1>(matrix[i][j]) << " " << get<2>(matrix[i][j]) << "   ";
		}
		cout << endl;
	}
}

inputMatrix readMatrix(string fileName, int size) {
	if (fileName.substr(fileName.find_last_of(".") + 1) != "txt")
	{
		cout << "Error. You cannot open a file with a non-txt extension";
		exit(1);
	}

	ifstream fin(fileName);
	inputMatrix matrix;
	int num;

	for (int i = 0; i < size; i++)
	{
		vector<int> row;
		for (int i = 0; i < size; i++)
		{
			fin >> num;
			row.push_back(num);
		}
		matrix.push_back(row);
	}

	fin.close();

	return matrix;
}

inputMatrix fillRandomMatrix(int size) {
	inputMatrix matrix(size, vector<int>(size, 0));

	for (int i = 0; i < size; i++)
	{
		vector<int> row(size, 0);
		for (int j = 0; j < size; j++)
		{
			row[j] = rand() % 10;
		}
		matrix[i] = row;;
	}

	return matrix;
}

culcMatrix solveMatrix(inputMatrix& matrix)
{
	culcMatrix result;

	for (int i = 0; i < matrix.size(); i++)
	{
		vector<tuple<int, int, int>> row;
		for (int j = 0; j < matrix[i].size(); j++)
		{
			row.push_back(make_tuple(matrix[i][j], 0, 1));
		}
		result.push_back(row);
	}


	for (int i = 0; i < matrix.size(); i++)
	{
		for (int j = i; j < matrix[i].size(); j++)
		{
			if (matrix[i][j] > 0)
			{
				result[i][j] = make_tuple(matrix[i][j], 0, 1);
				result[j][i] = make_tuple(matrix[i][j], 0, -1);
			}
		}
	}

	return result;
}