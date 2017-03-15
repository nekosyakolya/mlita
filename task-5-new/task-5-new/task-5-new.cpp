// task-5-new.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>


std::vector<std::pair<unsigned, bool>> GetSegments(std::ifstream &input)
{
	std::vector<std::pair<unsigned, bool>> tmp;
	unsigned n = 0;
	while (input)
	{
		input >> n;
		tmp.push_back(std::make_pair(n, true));
		input >> n;
		tmp.push_back(std::make_pair(n, false));
		input.get();
	}
	return tmp;
}


unsigned FindResult(std::vector<std::pair<unsigned, bool>> &segments, unsigned m)
{

	unsigned result = 0;

	unsigned counter = 0;

	for (auto it = segments.begin(); it != segments.end(); ++it)
	{
		
		(it->second) ? ++counter : --counter;
		if (!it->second && counter == (m - 1))
		{
			++result;
		}

	}

	return result;
}





int main()
{
	std::ifstream input("input10.txt");
	std::ofstream output("output.txt");

	unsigned n;
	unsigned m;

	input >> n;
	input >> m;
	input.get();


	std::vector<std::pair<unsigned, bool>> segments = GetSegments(input);

	std::sort(segments.begin(), segments.end(), [](const std::pair<unsigned, bool> &a, const std::pair<unsigned, bool> &b)
	{
		return (a.first != b.first) ? (a.first < b.first) : (a.second);
	});

	unsigned result = FindResult(segments, m);


	output << result << std::endl;

	return 0;
}

