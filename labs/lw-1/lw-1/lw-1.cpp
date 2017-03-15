// lw-1.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>

void InitSite(std::vector<std::vector<bool>> & field, unsigned n, unsigned m)
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
	Building bed;
	unsigned area = 0;
};


bool IsValidWidth(const Building &building, unsigned a)
{
	return building.first.x >= 0 && building.second.x >= building.first.x && a >= building.second.x;
}

bool IsValidHeight(const Building &building, unsigned b)
{
	return building.first.y >= 0 && building.second.y >= building.first.y && b >= building.second.y;
}

void CheckValidityBuilding(const Building &building, unsigned a, unsigned b)
{

	if (!(IsValidHeight(building, b), IsValidWidth(building, a)))
	{
		throw std::logic_error("Incorrect coordinates\n");
	}

}

std::vector<Building> GetBuilding(unsigned a, unsigned b, std::ifstream & input)
{
	std::vector<Building> buildings;
	while (input)
	{
		Building tmp;
		input >> tmp.first.x;
		input >> tmp.first.y;
		input >> tmp.second.x;
		input >> tmp.second.y;
		input.get();
		CheckValidityBuilding(tmp, a, b);
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


void FillSite(std::vector<std::vector<bool>> & field, const std::vector<Building> &buldings)
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
			Bed newBed;
			newBed.bed.first.x = coordinates[j].x;
			newBed.bed.first.y = coordinates[j].y;
			newBed.bed.second.x = coordinates[j + 1].x;
			newBed.bed.second.y = coordinates[j + 1].y;
			newBed.area = newBed.bed.second.x - newBed.bed.first.x;
			tmpBeds.push_back(newBed);

			coordinates.erase(coordinates.begin() + j + 1);
			coordinates.erase(coordinates.begin() + j);
		}
	}
	return tmpBeds;

}
bool IsValidNumberBuilding(unsigned n)
{
	return n <= 10 && n >= 0;
}

bool IsValidNumberBed(unsigned m)
{
	return m <= 2 && m >= 1;
}

bool IsValidParameters(unsigned a, unsigned b)
{
	return a >= 1 && b <= 10000;
}

void CheckValidity(unsigned n, unsigned m, unsigned a, unsigned b)
{
	if (!(IsValidNumberBuilding(n) && IsValidNumberBed(m) && IsValidParameters(a, b)))
	{
		throw std::logic_error("Incorrect value(s)\n");;
	}
}


void FindOptimalLocation(unsigned m, std::vector<std::vector<bool>> &site, std::ofstream &output)
{
	for (unsigned i = m; i != 0; --i)
	{
		std::vector<Bed> tmpBeds = GetBeds(site);
		std::vector<Bed> currentBeds;
		std::vector<Bed> resultBeds;

		for (auto bed : tmpBeds)
		{
			currentBeds.push_back(bed);

			while (currentBeds.size() != 0)
			{
				Bed tmp = *currentBeds.begin();
				for (auto b : tmpBeds)
				{
					if (tmp.bed.second.y == b.bed.first.y && ((b.bed.first.x <= tmp.bed.first.x &&
						b.bed.second.x >= tmp.bed.second.x)
						|| (b.bed.first.x >= tmp.bed.first.x && b.bed.second.x <= tmp.bed.second.x)
						))
					{
						Bed newBed;
						newBed.bed.first.y = tmp.bed.first.y;
						newBed.bed.second.y = b.bed.second.y;
						newBed.bed.first.x = (tmp.bed.first.x < b.bed.first.x) ? b.bed.first.x : tmp.bed.first.x;
						newBed.bed.second.x = (tmp.bed.second.x < b.bed.second.x) ? tmp.bed.second.x : b.bed.second.x;
						newBed.area = (newBed.bed.second.x - newBed.bed.first.x) * (newBed.bed.second.y - newBed.bed.first.y);
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
			BetBuilding(site, result.bed);
			resultBeds.clear();
		}

		output << result.bed.first.x << ' ' << result.bed.first.y << ' '
			<< result.bed.second.x << ' ' << result.bed.second.y << std::endl;
	}
}


int main()
{
	unsigned n = 0;
	unsigned m = 0;
	unsigned a = 0;
	unsigned b = 0;

	std::ifstream input("input.txt");
	std::ofstream output("output.txt");
	try
	{
		input >> n;//постройки
		input >> m;//грядки
		input.get();

		input >> a;//стороны
		input >> b;
		input.get();
		CheckValidity(n, m, a, b);

		std::vector<std::vector<bool>> site(b);//b= y
		InitSite(site, b, a + 2);//b= y

		std::vector<Building> buldings = GetBuilding(a, b, input);
		FillSite(site, buldings);

		FindOptimalLocation(m, site, output);

	}
	catch (const std::exception& err)
	{
		std::cerr << err.what();
	}

	return EXIT_SUCCESS;
}

