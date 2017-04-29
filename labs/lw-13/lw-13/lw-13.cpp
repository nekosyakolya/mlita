#include "stdafx.h"
#include <map>
#include <fstream>
#include <iostream>
#include <string>

struct Position
{
	size_t row = 1;
	size_t column = 0;
};

void ToLowerCase(char & symbol)
{
	if ((symbol <= 'ß' && symbol >= 'À') || (symbol <= 'Z' && symbol >= 'A' ))
	{
		symbol += 32;
	}
	if (symbol == '¨')
	{
		symbol += 16;
	}
}

std::multimap <char, size_t> GetBase(std::string & sample)
{
	std::multimap <char, size_t> tmp;
	for (int i = sample.size() - 1, j = 0; i >= 0; --i, ++j)
	{
		ToLowerCase(sample[i]);
		tmp.emplace(sample[i], static_cast<size_t>(j));
	}
	return tmp;
}

size_t GetNumberIdenticalSymbols(size_t lastIndex, size_t &j)
{
	size_t result = 0;
	if (j < lastIndex)
	{
		result = lastIndex - j;
		j = lastIndex;
	}
	return result;
}

size_t GetNewIndex(size_t &j, size_t size, const std::multimap <char, size_t>& base, char symbol)
{
	size_t numIdenticalSymbols = GetNumberIdenticalSymbols(size - 1, j);
	return (base.find(symbol) != base.end()) ? (base.find(symbol)->second - numIdenticalSymbols) : size;
}

void RecountPosition(size_t i, std::string &text, Position &position)
{
	if (i < text.size())
	{
		for (size_t tmp = position.column; tmp <= i; ++tmp)
		{
			if (text[tmp] == '\n')
			{
				text[tmp] = ' ';
				++position.row;
				position.column = tmp + 1;
			}
		}
	}
}

void OutputPosition(size_t i, const Position &position, std::ofstream &output)
{
	(i < position.column) ? output << (position.row - 1) << ' ' << (i + 1) : output << position.row << ' ' << (i - position.column + 1);
	output << std::endl;
}

void FindSample(std::string & sample, std::string & text, std::ofstream &output)
{
	bool isFind = false;
	std::multimap <char, size_t> base = GetBase(sample);
	Position position;

	for (size_t i = sample.size() - 1, sampleIndex = i; i < text.size();)
	{
		ToLowerCase(text[i]);
		if (text[i] == sample[sampleIndex])
		{
			if (sampleIndex == 0)
			{
				OutputPosition(i, position, output);
				isFind = true;
				sampleIndex = sample.size() - 1;
				i += sample.size();
			}
			else
			{
				--sampleIndex;
				--i;
			}
		}
		else
		{
			i += GetNewIndex(sampleIndex, sample.size(), base, text[i]);
			RecountPosition(i, text, position);
		}
	}

	if (!isFind)
	{
		output << "No" << std::endl;
	}
}

int main()
{
	std::ifstream input("input.txt");
	std::ofstream output("output.txt");

	std::string sample;
	std::string fileName;

	getline(input, sample);
	getline(input, fileName);

	std::ifstream dictionary(fileName);
	std::string text;
	getline(dictionary, text, '\0');

	FindSample(sample, text, output);

	return EXIT_SUCCESS;
}
