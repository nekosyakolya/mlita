#include "stdafx.h"
#include <map>
#include <fstream>
#include <iostream>
#include <string>
#include <cmath>

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

size_t Find(const std::string & sample, const std::string & text, size_t i, const std::multimap <char, size_t>& base)
{
	int result = 1;
	bool isFind = true;
	for (int j = sample.size() - 1; j >= 0;--j, --i)
	{
		if (sample[j] != text[i])
		{
			isFind = false;
			result = (base.find(text[i]) != base.end()) ? (base.find(text[i])->second) : sample.size();
			result -= ((sample.size() - 1) -j);
			break;
		}
	}
	if (isFind)
	{
		std::cout << "yes" << std::endl;
	}
	return abs(result);
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

	getline(dictionary, text);

	std::multimap <char, size_t> base = GetBase(sample);
	
	for (size_t i = sample.size() - 1; i < text.size() || !dictionary.eof();)
	{

		if (i >= text.size() && !dictionary.eof())
		{
			std::string tmp;
			getline(dictionary, tmp);
			text += ' ';
			text += tmp;
		}
		else
		{
			ToLowerCase(text[i]);

			if (text[i] == sample.back())
			{
				i += Find(sample, text, i, base);
			}
			else
			{
				i += (base.find(text[i]) != base.end()) ? (base.find(text[i])->second) : sample.size();
			}
		}
	}

	return EXIT_SUCCESS;
}
