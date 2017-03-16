#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>

struct Point
{
	unsigned x = 0;
	unsigned y = 0;
};

struct Building
{
	Point leftUp;
	Point rightBottom;
};

struct Bed
{
	Building building;
	unsigned area = 0;
};

void InitField(std::vector<std::vector<bool>> & field, unsigned n, unsigned m)
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

bool IsValidWidth(const Building &building, unsigned a)
{
	return building.leftUp.x >= 0 && building.rightBottom.x >= building.leftUp.x && a >= building.rightBottom.x;
}

bool IsValidHeight(const Building &building, unsigned b)
{
	return building.leftUp.y >= 0 && building.rightBottom.y >= building.leftUp.y && b >= building.rightBottom.y;
}

void CheckValidityBuilding(const Building &building, unsigned a, unsigned b)
{
	if (!(IsValidHeight(building, b), IsValidWidth(building, a)))
	{
		throw std::logic_error("Incorrect coordinates\n");
	}
}

std::vector<Building> GetBuildings(unsigned a, unsigned b, std::ifstream & input)
{
	std::vector<Building> buildings;
	while (input)
	{
		Building tmp;
		input >> tmp.leftUp.x;
		input >> tmp.leftUp.y;
		input >> tmp.rightBottom.x;
		input >> tmp.rightBottom.y;
		input.get();
		CheckValidityBuilding(tmp, a, b);
		buildings.push_back(tmp);
	}
	return buildings;
}

void BuildBuilding(std::vector<std::vector<bool>> & field, const Building &bulding)
{
	for (size_t i = bulding.leftUp.y; i < bulding.rightBottom.y; ++i)
	{
		for (size_t j = bulding.leftUp.x + 1; j <= bulding.rightBottom.x; ++j)
		{
			field[i][j] = false;
		}
	}
}

void FillField(std::vector<std::vector<bool>> & field, const std::vector<Building> &buldings)
{
	for (auto bulding : buldings)
	{
		BuildBuilding(field, bulding);
	}
}

void AddBed(std::vector<Point> &coordinates, std::vector<Bed> &tmpBeds)
{
	while (coordinates.size() != 0)
	{
		size_t j = 0;
		Bed newBed;
		newBed.building.leftUp.x = coordinates[j].x;
		newBed.building.leftUp.y = coordinates[j].y;
		newBed.building.rightBottom.x = coordinates[j + 1].x;
		newBed.building.rightBottom.y = coordinates[j + 1].y;
		newBed.area = newBed.building.rightBottom.x - newBed.building.leftUp.x;
		tmpBeds.push_back(newBed);

		coordinates.erase(coordinates.begin() + j + 1);
		coordinates.erase(coordinates.begin() + j);
	}
}

std::vector<Bed> GetUnusedRows(const std::vector<std::vector<bool>> & field)
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
				tmp.x = j;
				tmp.y = (!field[i][j]) ? i : i + 1;
				coordinates.push_back(tmp);
			}
		}

		AddBed(coordinates, tmpBeds);
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

void ChangeField(std::vector<Bed> &resultBeds, std::vector<std::vector<bool>> &field, Bed &result)
{
	if (resultBeds.size() != 0)
	{
		result = *std::max_element(resultBeds.begin(), resultBeds.end(), [](const Bed& a, const Bed& b) {
			return a.area < b.area;
		});
		BuildBuilding(field, result.building);
		resultBeds.clear();
	}
}

void OutputInfo(std::ofstream &output, const Bed &result)
{
	output << result.building.leftUp.x << ' ' << result.building.leftUp.y << ' '
		<< result.building.rightBottom.x << ' ' << result.building.rightBottom.y << std::endl;
}

void AddResult(std::vector<Bed> &currentBeds, std::vector<Bed> &resultBeds)
{
	Bed max = *std::max_element(currentBeds.begin(), currentBeds.end(), [](const Bed& a, const Bed& b) {
		return a.area < b.area;
	});
	resultBeds.push_back(max);
	currentBeds.erase(currentBeds.begin());
}

Bed GetBed(const Bed &tmp, const Bed &bed)
{
	Bed newBed;
	newBed.building.leftUp.y = tmp.building.leftUp.y;
	newBed.building.rightBottom.y = bed.building.rightBottom.y;
	newBed.building.leftUp.x = (tmp.building.leftUp.x < bed.building.leftUp.x) ? bed.building.leftUp.x : tmp.building.leftUp.x;
	newBed.building.rightBottom.x = (tmp.building.rightBottom.x < bed.building.rightBottom.x) ? tmp.building.rightBottom.x : bed.building.rightBottom.x;
	newBed.area = (newBed.building.rightBottom.x - newBed.building.leftUp.x) * (newBed.building.rightBottom.y - newBed.building.leftUp.y);
	return newBed;
}

bool CanGlued(const Bed &firstBed, const Bed &secondBed)
{
	return (firstBed.building.rightBottom.y == secondBed.building.leftUp.y && ((secondBed.building.leftUp.x <= firstBed.building.leftUp.x &&
		secondBed.building.rightBottom.x >= firstBed.building.rightBottom.x)
		|| (secondBed.building.leftUp.x >= firstBed.building.leftUp.x && secondBed.building.rightBottom.x <= firstBed.building.rightBottom.x)
		));
}

void FindOptimalLocation(unsigned m, std::vector<std::vector<bool>> &field, std::ofstream &output)
{
	for (unsigned i = m; i != 0; --i)
	{
		std::vector<Bed> unusedRows = GetUnusedRows(field);
		std::vector<Bed> currentBeds;
		std::vector<Bed> resultBeds;

		for (auto bed : unusedRows)
		{
			currentBeds.push_back(bed);
			while (currentBeds.size() != 0)
			{
				Bed tmp = *currentBeds.begin();
				for (auto bed : unusedRows)
				{
					if (CanGlued(tmp, bed))
					{
						Bed newBed = GetBed(tmp, bed);
						currentBeds.push_back(newBed);
					}
				}
				AddResult(currentBeds, resultBeds);
			}

		}
		Bed result;
		ChangeField(resultBeds, field, result);
		OutputInfo(output, result);
	}
}

int main()
{
	unsigned numBuildings = 0;
	unsigned numBeds = 0;
	unsigned widthField = 0;
	unsigned heightField = 0;

	std::ifstream input("input.txt");
	std::ofstream output("output.txt");
	try
	{
		input >> numBuildings;
		input >> numBeds;
		input.get();

		input >> widthField;
		input >> heightField;
		input.get();
		CheckValidity(numBuildings, numBeds, widthField, heightField);

		std::vector<std::vector<bool>> field(heightField);
		InitField(field, heightField, widthField + 2);
		if (numBuildings != 0)
		{
			std::vector<Building> buildings = GetBuildings(widthField, heightField, input);
			FillField(field, buildings);
		}

		FindOptimalLocation(numBeds, field, output);

	}
	catch (const std::exception& err)
	{
		std::cerr << err.what();
	}

	return EXIT_SUCCESS;
}
