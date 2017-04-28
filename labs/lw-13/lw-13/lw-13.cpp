#include "stdafx.h"
#include <map>
#include <fstream>
#include <iostream>
#include <string>

//¨????????????
void ToLowerCase(char & symbol)
{
	if ((symbol <= 'ß' && symbol >= 'À') || symbol <= 'Z' && symbol >= 'A')
	{
		symbol += 32;
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


bool isFindString(std::string & sample, std::string & text, std::ofstream &output)
{
	bool isFind = false;
	std::multimap <char, size_t> base = GetBase(sample);

	for (size_t i = sample.size() - 1, j = i, row = 1, num = 0; i < text.size();)
	{
		ToLowerCase(text[i]);

		if (text[i] == sample[j])
		{
			if (j == 0)
			{
				isFind = true;
				j = sample.size() - 1;
				(i < num) ? output << (row - 1) << ' ' << (i + 1) : output << row << ' ' << (i - num + 1);
				output << std::endl;

				i += sample.size();
			}
			else
			{
				--j;
				--i;
			}
		}
		else
		{
			size_t tmp = num;
			size_t k = 0;
			if (j < (sample.size() - 1))
			{

				k = sample.size() - 1 - j;
				j = sample.size() - 1;

			}

			i += (base.find(text[i]) != base.end()) ? (base.find(text[i])->second - k) : (sample.size());

			if (i < text.size())
			{
				for (; tmp <= i; ++tmp)
				{
					if (text[tmp] == '\n')
					{
						text[tmp] = ' ';
						++row;
						num = tmp + 1;
					}
				}
			}
		}
	}
	return isFind;
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

	if (!isFindString(sample, text, output))
	{
		output << "No" << std::endl;
	}

	return EXIT_SUCCESS;
}

