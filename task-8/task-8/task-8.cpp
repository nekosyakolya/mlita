// task-8.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <vector>


struct Point
{
	int x = 0;
	int y = 0;
};


std::vector<Point> GetCoordinates(std::ifstream &input)
{
	std::vector<Point> tmp;
	int tmpNum;
	input >> tmpNum;
	input.get();

	while (input)
	{
		Point point;
		input >> point.x;
		input >>point.y;
		tmp.push_back(point);
		input.get();
	}
	return tmp;
}

int GetResult(const std::vector<Point> & coordinates)
{
	int result = 0;
	for (size_t i = 0; i < coordinates.size() - 2; ++i)
	{
		int tmp = ((coordinates[i + 2].x - coordinates[i].x) * (coordinates[i + 1].y - coordinates[i].y) -
			((coordinates[i + 2].y - coordinates[i].y) * (coordinates[i + 1].x - coordinates[i].x)));

		if (tmp < 0)
		{
			++result;
		}
	}

	return result;
}


int main()
{
	std::ifstream input("input.txt");
	std::ofstream output("output.txt");

	std::vector<Point> coordinates = GetCoordinates(input);

	int result = GetResult(coordinates);

	output << result << std::endl;

	return EXIT_SUCCESS;
}

