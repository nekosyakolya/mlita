// lw-1.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>

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



struct Bed
{
	Point first;
	Point second;
	unsigned area = 0;
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


void BetBed(std::vector<std::vector<bool>> & field, const Bed &bed)
{
	for (size_t i = bed.first.y; i < bed.second.y; ++i)
	{
		for (size_t j = bed.first.x + 1; j <= bed.second.x; ++j)
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
	input >> m;//грядки
	input.get();

	input >> a;//стороны
	input >> b;
	input.get();

	std::vector<std::vector<bool>> field(b);//b= y
	InitArray(field, b, a + 2);//b= y
	std::vector<Building> buldings = GetBuilding(n, input);
	FillArray(field, buldings);

	for (unsigned i = m; i != 0; --i)
	{
		std::vector<Bed> tmpBeds = GetBeds(field);

		std::vector<Bed> currentBeds;

		std::vector<Bed> resultBeds;

		for (auto bed : tmpBeds)
		{
			currentBeds.push_back(bed);

			while (currentBeds.size() != 0)
			{
				//for
				Bed tmp = *currentBeds.begin();
				for (auto b : tmpBeds)
				{
					if (tmp.second.y == b.first.y && ((b.first.x <= tmp.first.x && b.second.x >= tmp.second.x)
						|| (b.first.x >= tmp.first.x && b.second.x <= tmp.second.x)
						))
					{
						Bed newBed;
						newBed.first.y = tmp.first.y;
						newBed.second.y = b.second.y;
						newBed.first.x = (tmp.first.x < b.first.x) ? b.first.x : tmp.first.x;
						newBed.second.x = (tmp.second.x < b.second.x) ? tmp.second.x : b.second.x;
						newBed.area = (newBed.second.x - newBed.first.x) * (newBed.second.y - newBed.first.y);
						currentBeds.push_back(newBed);

					}
				}

				Bed result = *std::max_element(currentBeds.begin(), currentBeds.end(), [](const Bed& a, const Bed& b) {
					return a.area < b.area;
				});
				resultBeds.push_back(result);
				currentBeds.erase(currentBeds.begin());

			}

		}


		Bed result;
		if (resultBeds.size() != 0)
		{
			result = *std::max_element(resultBeds.begin(), resultBeds.end(), [](const Bed& a, const Bed& b) {
				return a.area < b.area;
			});
		}
		BetBed(field, result);

		output << result.first.x << ' ' << result.first.y << ' '
		<< result.second.x << ' ' << result.second.y << std::endl;
		resultBeds.clear();
	}
	return EXIT_SUCCESS;
}

