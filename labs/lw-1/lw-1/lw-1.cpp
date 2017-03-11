// lw-1.cpp: определ€ет точку входа дл€ консольного приложени€.
//

#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <string>


void InitArray(std::vector<std::vector<bool>> & field, unsigned n, unsigned m)
{
	for (size_t i = 0; i < n; ++i)
	{
		field[i].resize(m);

		for (size_t j = 0; j < m; ++j)
		{
			field[i][j] = (j == 0 || j == m - 1) ? false : true;
			
		}
	}
}


struct Point
{
	unsigned x = 0;
	unsigned y = 0;
};


struct Building
{
	Point first;
	Point second;
};


std::vector<Building> GetBuilding(unsigned n, std::ifstream & input)
{
	std::vector<Building> buildings;
	for (n; n != 0; --n)
	{
		Building tmp;
		input >> tmp.first.x;
		input >> tmp.first.y;
		input >> tmp.second.x;
		input >> tmp.second.y;
		input.get();
		buildings.push_back(tmp);
	}
	return buildings;
}


void BetBuilding(std::vector<std::vector<bool>> & field, const Building &bulding)
{
	for (size_t i = bulding.first.y; i < bulding.second.y; ++i)
	{
		for (size_t j = bulding.first.x + 1; j <= bulding.second.x; ++j)
		{
			field[i][j] = false;
		}
	}
}

void FillArray(std::vector<std::vector<bool>> & field, const std::vector<Building> &buldings)
{
	for (auto bulding : buldings)
	{
		BetBuilding(field, bulding);
	}
}



struct Bed
{
	Point first;
	Point second;
	unsigned area = 0;
};



std::vector<Bed> GetBeds(const std::vector<std::vector<bool>> & field)
{
	std::vector<Bed> tmpBeds;
	for (size_t i = 0; i < field.size(); ++i)
	{
		std::vector<Point> coordinates;
		for (size_t j = 0; j < field[i].size() - 1; ++j)
		{
			if (field[i][j] != field[i][j + 1])
			{
				Point tmp;
				tmp.x = j;//+1
				tmp.y = (!field[i][j]) ? i : i + 1;
				coordinates.push_back(tmp);
			}
		}

		while (coordinates.size() != 0)
		{
			size_t j = 0;
			Bed bed;
			bed.first.x = coordinates[j].x;
			bed.first.y = coordinates[j].y;
			bed.second.x = coordinates[j + 1].x;
			bed.second.y = coordinates[j + 1].y;
			bed.area = bed.second.x - bed.first.x;
			tmpBeds.push_back(bed);

			coordinates.erase(coordinates.begin() + j + 1);
			coordinates.erase(coordinates.begin() + j);
		}
	}
	return tmpBeds;

}

int main()
{
	unsigned n = 0;
	unsigned m = 0;
	unsigned a = 0;
	unsigned b = 0;

	std::ifstream input("input.txt");
	std::ofstream output("output.txt");

	input >> n;//постройки
	input >> m;//гр€дки
	input.get();

	input >> a;//стороны
	input >> b;
	input.get();

	std::vector<std::vector<bool>> field(b);//b= y
	InitArray(field, b, a + 2);//b= y
	std::vector<Building> buldings = GetBuilding(n, input);
	FillArray(field, buldings);


	//while m != 0 && есть свободные
	std::vector<Bed> tmpBeds = GetBeds(field);


	for (auto bed : tmpBeds)
	{

	}

	return EXIT_SUCCESS;
}

