// task-2.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <string>

void InitArray(std::vector<std::vector<char>> & field, int n, int m)
{
	char dot = '.';
	for (size_t i = 0; i < n; ++i)
	{
		field[i].resize(m);

		for (size_t j = 0; j < m; ++j)
		{
			field[i][j] = dot;
		}
	}
}


void FillArray(std::vector<std::vector<char>> & field, std::ifstream &input, int n, int m)
{
	char ch = ' ';
	for (size_t i = 1; i < n; ++i)
	{
		for (size_t j = 1; j < m; ++j)
		{
			input >> ch;
			field[i][j] = ch;
		}
		input.get();
	}
}



void Check(std::vector<std::vector<char>> & field, int i, int j)
{
	if (field[i][j] == '#')
	{
		field[i][j] = '.';
		Check(field, i - 1, j);
		Check(field, i + 1, j);
		Check(field, i, j - 1);
		Check(field, i, j + 1);
	}
}

int SearchBeds(std::vector<std::vector<char>> & field, int n, int m)
{
	int num = 0;
	for (size_t i = 1; i < n; ++i)
	{
		for (size_t j = 1; j < m; ++j)
		{
			if (field[i][j] == '#')
			{
				++num;
			}
			Check(field, i, j);
		}
	}
	return num;
}

int main()
{

	int n = 0;
	int m = 0;

	std::ifstream input("input.txt");

	std::ofstream output("output.txt");

	input >> n;
	input >> m;
	input.get();

	std::vector<std::vector<char>> field(n + 2);

	InitArray(field, n + 2, m + 2);

	FillArray(field, input, n + 1, m + 1);


	int numBeds = SearchBeds(field, n + 1, m + 1);

	output << std::to_string(numBeds);

	output << std::endl;

	return EXIT_SUCCESS;
}

