#include "stdafx.h"
#include <map>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

void ToLowerCase(char & symbol)
{
	if ((symbol <= 'ß' && symbol >= 'À') || (symbol <= 'Z' && symbol >= 'A'))
	{
		symbol += 32;
	}
	if (symbol == '¨')
	{
		symbol += 16;
	}
}

struct Template
{
	std::string string;
	std::multimap <char, size_t> base;
	std::vector<size_t>sufficsShift;
	void GetBase()
	{
		std::multimap <char, size_t> tmp;
		for (int i = static_cast<int>(string.size() - 1), j = 0; i >= 0; --i, ++j)
		{
			if (tmp.find(string[i]) == tmp.end())
			{
				ToLowerCase(string[i]);
				tmp.emplace(string[i], static_cast<size_t>(j));
			}
		}
		std::swap(tmp, base);
	}

	void GetShift()
	{
		const size_t sampleSize = string.size();
		std::vector<size_t> tmp(sampleSize + 1, sampleSize);
		std::vector<size_t> z = GetZFunction();

		for (size_t i = sampleSize - 1; i > 0; --i)
		{
			tmp[sampleSize - z[i]] = i;
		}

		for (size_t i = 1, j = 0; i <= sampleSize - 1; ++i)
		{
			if (i + z[i] == sampleSize)
			{
				for (; j <= i; ++j)
				{
					if (tmp[j] == sampleSize)
					{
						tmp[j] = i;
					}
				}
			}
		}
		std::swap(tmp, sufficsShift);
	}
	size_t GetShift(const char &symbol) const
	{
		return (base.find(symbol) != base.end()) ? (base.find(symbol)->second) : string.size();
	}
private:
	std::vector<size_t> GetZFunction()
	{
		const size_t sampleSize = string.size();
		std::vector<size_t> z(sampleSize, 0);

		for (size_t i = 1, maxZidx = 0, maxZ = 0; i < sampleSize; ++i)
		{
			if (i <= maxZ)
			{
				z[i] = std::min(maxZ - i + 1, z[i - maxZidx]);
			}

			while (i + z[i] < sampleSize && string[sampleSize - 1 - z[i]] == string[sampleSize - 1 - (i + z[i])])
			{
				++z[i];
			}

			if (i + z[i] - 1 > maxZ)
			{
				maxZidx = i;
				maxZ = i + z[i] - 1;
			}
		}

		return z;
	}
};


size_t Find(const std::vector<size_t> &positions, const Template & sample, const std::string & text, size_t i, std::ofstream &output, bool & isFind)
{
	size_t shift = 1;

	std::string textStr = text;
	size_t index = positions.size() - 1;

	int j = static_cast<int>(sample.string.size() - 1);
	for (; j >= 0;--j, --i)
	{
		if (textStr[i] == '\n')
		{
			textStr[i] = ' ';
			--index;
		}

		ToLowerCase(textStr[i]);
		if (sample.string[j] != textStr[i])
		{
			shift = sample.GetShift(textStr[i]);
			shift = (shift < ((sample.string.size() - 1) - j)) ? sample.sufficsShift[j] : (shift - ((sample.string.size() - 1) - j));
			break;
		}
	}

	if (j < 0)
	{
		isFind = true;
		output << (index + 1) << ' ' <<((i - positions[index]) + 2) << std::endl;
	}
	return shift;
}

void FindSampleInText(Template &sample, std::ifstream &dictionary, std::ofstream &output)
{
	std::string text;
	getline(dictionary, text);
	std::vector<size_t> positions = { 0 };
	bool isFind = false;

	for (size_t i = sample.string.size() - 1; i < text.size() || !dictionary.eof();)
	{
		if (i >= text.size() && !dictionary.eof())
		{
			std::string tmp;
			getline(dictionary, tmp);
			text += '\n';
			positions.push_back(text.size());
			text += tmp;
		}
		else
		{
			ToLowerCase(text[i]);
			char symbol = (text[i] == '\n') ? ' ' : text[i];
			i += (symbol == sample.string.back()) ? Find(positions, sample, text, i, output, isFind) : sample.GetShift(symbol);
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
	
	Template sample;
	std::string fileName;

	getline(input, sample.string);
	getline(input, fileName);

	std::ifstream dictionary(fileName);

	sample.GetBase();
	sample.GetShift();

	FindSampleInText(sample, dictionary, output);
	return EXIT_SUCCESS;
}
