// task-6.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <iterator>

std::vector<unsigned> GetElements(std::ifstream &input)
{
	std::vector<unsigned> elements;

	unsigned tmp = 0;
	while (input >> tmp)
	{
		elements.push_back(tmp);
	}
	return elements;
}


void Search(std::vector<unsigned> &elements)
{
	size_t j = elements.size() - 2;
	bool isFind = false;
	for (j; j >= 0; --j)
	{
		if (elements[j] < elements[j + 1])
		{
			isFind = true;
			break;
		}

	}

	if (isFind)
	{
		std::vector<std::pair<unsigned, size_t>> tmpElements;
		for (size_t tmp = j; tmp < elements.size(); ++tmp)
		{
			if (elements[j] < elements[tmp])
			{
				tmpElements.push_back(std::make_pair(elements[tmp], tmp));
			}
		}


		if (tmpElements.size() != 0)
		{
			std::pair<unsigned, size_t> result = *std::min_element(tmpElements.begin(), tmpElements.end(),
				[](std::pair<unsigned, size_t> &a, std::pair<unsigned, size_t> &b) {
				return a.second > b.second;
			});
			std::swap(elements[j], elements[result.second]);

			unsigned m = j + 1;
			for (size_t i = elements.size() - 1; i >= m; --i, ++m)
			{
				std::swap(elements[i], elements[m]);
			}
		}


		std::copy(elements.begin(), elements.end(), std::ostream_iterator<unsigned>(std::cout, " "));
		std::cout << std::endl;
	}


}

int main()
{

	std::ifstream input("input.txt");
	std::ofstream output("output.txt");

	unsigned n;
	unsigned k;

	input >> n;
	input >> k;
	input.get();


	std::vector<unsigned> elements = GetElements(input);


	for (unsigned i = k; i != 0; --i)
	{
		Search(elements);
	}

	return 0;
}

