#include "stdafx.h"
#include <map>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

void ToLowerCase(char & symbol)
{
	if ((symbol <= 'Я' && symbol >= 'А') || (symbol <= 'Z' && symbol >= 'A' ))
	{
		symbol += 32;
	}
	if (symbol == 'Ё')
	{
		symbol += 16;
	}
}

std::multimap <char, size_t> GetBase(std::string & sample)
{
	std::multimap <char, size_t> tmp;
	for (int i = sample.size() - 1, j = 0; i >= 0; --i, ++j)
	{
		if (tmp.find(sample[i]) == tmp.end())
		{
			ToLowerCase(sample[i]);
			tmp.emplace(sample[i], static_cast<size_t>(j));
		}
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

size_t Find(const std::vector<size_t> &positions, const std::string & sample, const std::string & text, size_t i, const std::multimap <char, size_t>& base, const std::vector<int>& suffics)
{
	size_t result = 1;
	bool isFind = true;
	std::string textStr = text;
	size_t index = positions.size() - 1;

	for (int j = sample.size() - 1; j >= 0;--j, --i)
	{
		if (textStr[i] == '\n')
		{
			textStr[i] = ' ';
			--index;
		}

		if (sample[j] != textStr[i])
		{
			isFind = false;
			result = (base.find(textStr[i]) != base.end()) ? (base.find(textStr[i])->second) : sample.size();
			if (result < ((sample.size() - 1) - j))
			{
				result = suffics[j];// + 1 мб...
			}
			else
			{
				result -= ((sample.size() - 1) - j);
			}

			break;
		}
	}
	

	if (isFind)
	{
		std::cout << "row: "  << (index + 1) << " col:" << ((i - positions[index]) + 2) << std::endl;
	}

	return result;
}

std::vector<int> GetShift(const std::string & sample)
{
	size_t m = sample.size();

	std::vector<int> suffshift(m + 1, m);
	std::vector<int> z(m, 0);
	for (int j = 1, maxZidx = 0, maxZ = 0; j < m; ++j) {
		if (j <= maxZ) z[j] = std::min(maxZ - j + 1, z[j - maxZidx]);
		while (j + z[j] < m && sample[m - 1 - z[j]] == sample[m - 1 - (j + z[j])]) z[j]++;
		if (j + z[j] - 1 > maxZ) {
			maxZidx = j;
			maxZ = j + z[j] - 1;
		}
	}
	for (int j = m - 1; j > 0; j--) suffshift[m - z[j]] = j; //цикл №1
	for (int j = 1, r = 0; j <= m - 1; j++) //цикл №2
		if (j + z[j] == m)
			for (; r <= j; r++)
				if (suffshift[r] == m) suffshift[r] = j;


	return suffshift;
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

	std::vector<int>result = GetShift(sample);

	std::vector<size_t> positions;
	positions.push_back(0);

	for (size_t i = sample.size() - 1; i < text.size() || !dictionary.eof();)
	{

		if (i >= text.size() && !dictionary.eof())
		{
			std::string tmp;
			getline(dictionary, tmp);
			text += '\n';

			positions.push_back (text.size());
			
			text += tmp;
		}
		else
		{
			ToLowerCase(text[i]);



			if (text[i] == sample.back())
			{
				i += Find(positions, sample, text, i, base, result);
			}
			else
			{
				char symbol = (text[i] == '\n') ? ' ' : text[i];
				
				i += (base.find(symbol) != base.end()) ? (base.find(symbol)->second) : sample.size();
			}
		}
	}

	return EXIT_SUCCESS;
}
