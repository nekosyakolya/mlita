// task-10.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <vector>
#include <algorithm>
#include <iterator>

std::map <char, size_t> GetBase(const std::string &baseWord)
{
	std::map <char, size_t> tmp;
	for (auto symbol : baseWord)
	{
		if (tmp.find(symbol) != tmp.end())
		{
			++tmp.find(symbol)->second;
		}
		else
		{
			tmp.emplace(symbol, 1);
		}
	}
	return tmp;
}


size_t GetScore(std::map <char, size_t>base, const std::string &tmpWord)
{
	for (auto symbol: tmpWord)
	{
		auto it = base.find(symbol);
		if (it == base.end())
		{
			return 0;
		}
		else
		{
			--it->second;
			if (it->second == 0)
			{
				base.erase(it);
			}
		}
	}

	return tmpWord.size();
}




std::pair<size_t, std::vector<std::string>> ProcessGame(std::ifstream & input)
{
	std::string baseWord;
	input >> baseWord;

	std::map <char, size_t> base = GetBase(baseWord);
	
	size_t resultScore = 0;
	std::vector<std::string> result;

	std::string tmpWord;
	size_t tmpResult;
	while (input >> tmpWord)
	{
		tmpResult = GetScore(base, tmpWord);

		if (tmpResult != 0)
		{
			result.push_back(tmpWord);
			resultScore += tmpResult;
		}

	}

	return std::make_pair(resultScore, result);
}


void OutputResult(std::pair<size_t, std::vector<std::string>> &result, std::ofstream &output)
{
	output << result.first;

	output << std::endl;
	std::sort(result.second.begin(), result.second.end(), [](const std::string &a, const std::string &b)
	{
		return (a.size() == b.size()) ? (a < b) : (a.size() > b.size());
	});

	std::copy(result.second.begin(), result.second.end(), std::ostream_iterator<std::string>(output, "\n"));

}

int main()
{
	std::ifstream input("input.txt");
	std::ofstream output("output.txt");



	std::pair<size_t, std::vector<std::string>> result = ProcessGame(input);

	OutputResult(result, output);

	return EXIT_SUCCESS;
}

