#include "prototypes.h"


void main()
{
	cout << "Enter size of input matrix: ";
	int size;
	cin >> size;

	cout << "1 - Read matrix from file " << endl;
	cout << "2 - Generate random matrix " << endl;
	cout << "1/2: ";
	char answer;
	cin >> answer;

	inputMatrix matrix;
	if (answer == '1')
	{
		cout << "Enter file name for input matrix: ";
		string file;
		cin >> file;
		matrix = readMatrix(file, size);
	}
	else if (answer == '2')
	{
		matrix = fillRandomMatrix(size);
		cout << "Random matrix" << endl;
		printMatrix(matrix);
		cout << endl;
	}
	else
	{
		cout << "Error input";
		exit(1);
	}

	extendMatrix matrixExtend = extendedMatrix(matrix);

	vector<int> paths = solve(matrixExtend, matrix);

	int sum = 0;
	for (int i = 0; i < paths.size(); i++)
	{
		sum += paths[i];
	}
	cout << "Max flow = " << sum;
	cin >> answer;
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

void printMatrix(extendMatrix& matrix) {
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

extendMatrix extendedMatrix(inputMatrix& matrix)
{
	extendMatrix result;

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

int getMaxNode(int index, extendMatrix& matrix, set<int>& visited)
{
	int min = 0, node = -1;
	for (int i = 0; i < matrix[index].size(); i++)
	{
		if (visited.count(i))
		{
			continue;
		}
		if (get<2>(matrix[index][i]) == 1)
		{
			if (min < get<0>(matrix[index][i]))
			{
				min = get<0>(matrix[index][i]);
				node = i;
			}
		}
		else
		{
			if (min < get<1>(matrix[index][i]))
			{
				min = get<1>(matrix[index][i]);
				node = i;
			}
		}
	}

	return node;
}

int getMaxFlow(vector<tuple<int, int, int>>& row)
{
	vector<int> flows;
	for (int i = 0; i < row.size(); i++)
	{
		flows.push_back(get<0>(row[i]));
	}

	return *min_element(flows.begin(), flows.end());
}

void updateNodesWeights(extendMatrix& matrix, vector<tuple<int, int, int>>& row, int num)
{
	for (auto elem : row)
	{
		if (get<1>(elem) == -1)
		{
			continue;
		}

		int direction = get<2>(matrix[get<2>(elem)][get<1>(elem)]);

		matrix[get<1>(elem)][get<2>(elem)] = make_tuple(get<0>(matrix[get<1>(elem)][get<2>(elem)]) - (num * direction),
			get<1>(matrix[get<1>(elem)][get<2>(elem)]) + (num * direction),
			get<2>(matrix[get<1>(elem)][get<2>(elem)]));

		matrix[get<2>(elem)][get<1>(elem)] = make_tuple(get<0>(matrix[get<2>(elem)][get<1>(elem)]) - (num * direction),
			get<1>(matrix[get<2>(elem)][get<1>(elem)]) + (num * direction),
			get<2>(matrix[get<2>(elem)][get<1>(elem)]));
	}
}

vector<int> solve(extendMatrix& matrixExtend, inputMatrix& matrix)
{
	vector<int> paths;
	int source = 0, drain = matrix.size() - 1;
	tuple<int, int, int> startNode = make_tuple(INT_MAX, -1, source);

	int j = source;
	while (j != -1)
	{
		int startPoint = source;
		vector<tuple<int, int, int>> pathBranches = { startNode };
		set<int> visited = { source };

		while (startPoint != drain)
		{
			j = getMaxNode(startPoint, matrixExtend, visited);
			if (j == -1)
			{
				if (startPoint == source)
				{
					break;
				}
				else
				{
					startPoint = get<2>(pathBranches[pathBranches.size() - 1]);
					pathBranches.pop_back();
					continue;
				}
			}

			int flow;
			if (get<2>(matrixExtend[startPoint][j]) == 1)
			{
				flow = get<0>(matrixExtend[startPoint][j]);
			}
			else
			{
				flow = get<1>(matrixExtend[startPoint][j]);
			}

			pathBranches.push_back(make_tuple(flow, j, startPoint));
			visited.insert(j);

			if (j == drain)
			{
				paths.push_back(getMaxFlow(pathBranches));
				updateNodesWeights(matrixExtend, pathBranches, paths[paths.size() - 1]);
				break;
			}

			startPoint = j;
		}
	}

	return paths;
}