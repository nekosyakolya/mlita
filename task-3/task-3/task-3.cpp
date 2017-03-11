// task-3.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <string>


void InitArray(std::vector<std::vector<int>> & field, int n, int m)
{
	for (size_t i = 0; i < n; ++i)
	{
		field[i].resize(m);

		for (size_t j = 0; j < m; ++j)
		{
			field[i][j] = 0;
		}
	}
}


void InitVector(std::vector<std::vector<bool>> & field, int n, int m)
{
	for (size_t i = 0; i < n; ++i)
	{
		field[i].resize(m);

		for (size_t j = 0; j < m; ++j)
		{
			field[i][j] = false;
		}
	}
}



void FillArray(std::vector<std::vector<int>> & field, std::ifstream &input, int n, int m)
{
	int value = 0;
	for (size_t i = 0; i < n; ++i)
	{
		field[i].resize(m);
		for (size_t j = 0; j < m; ++j)
		{
			input >> value;
			field[i][j] = value;
		}
		input.get();
	}
}



void CountMinCost(std::vector<std::vector<int>> & field, std::vector<std::vector<bool>> & right, std::vector<std::vector<int>> & minCost, int n, int m)
{

	minCost[n - 1][m - 1] = field[n - 1][m - 1];

	for (int j = m - 2; j >= 0; --j)
	{
		minCost[n - 1][j] = field[n - 1][j] + minCost[n - 1][j + 1];
		right[n - 1][j] = true;
	}

	for (int j = n - 2; j >= 0; --j)
	{
		minCost[j][m - 1] = field[j][m - 1] + minCost[j + 1][m - 1];
	}


	for (int i = n - 2; i >= 0; --i)
	{
		for (int j = m - 2; j >= 0; --j)
		{


			if (minCost[i + 1][j] < minCost[i][j + 1])
			{
				// идем вправо
				minCost[i][j] = field[i][j] + minCost[i + 1][j];
				right[i][j] = true;
			}
			else
			{
				minCost[i][j] = field[i][j] + minCost[i][j + 1];
			}

		}

	}

}



void OutputResult(std::vector<std::vector<bool>> & right, std::vector<std::vector<int>> & minCost, int n, int m)
{
	std::ofstream output("output.txt");
	output << minCost[0][0] << std::endl;


	for (size_t i = 0, j = 0; i < n || j < m;)
	{
		output << "(";

		if (i < n && j < m)
		{
			(right[i][j]) ? ++i : ++j;
			output << std::to_string(i + 1) + ", " + std::to_string(j + 1);
		}

		if (i == n)
		{

			++j;
			//output << std::to_string(i) + ", " + std::to_string(j + 1);

		}
		if (j == m)
		{

			++i;
			//output << std::to_string(i + 1) + ", " + std::to_string(j);
		}
		output << ")" << std::endl;
		
	}
}


int main()
{


	int n = 0;
	int m = 0;

	std::ifstream input("input.txt");


	input >> n;
	input >> m;
	input.get();


	std::vector<std::vector<int>> field(n);
	FillArray(field, input, n, m);


	std::vector<std::vector<int>> minCost(n);
	InitArray(minCost, n, m);


	std::vector<std::vector<bool>> right(n);
	InitVector(right, n, m);

	CountMinCost(field, right, minCost, n, m);

	OutputResult(right, minCost, n, m);


	return 0;
}

