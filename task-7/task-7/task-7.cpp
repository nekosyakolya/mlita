// task-7.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <string>

std::vector<bool> GetCode(std::ifstream &input)
{
	std::vector<bool> tmpCode;
	std::string tmp;
	input >> tmp;
	for (auto ch : tmp)
	{
		bool flag = (ch == '1') ? true : false;
		tmpCode.push_back(flag);
	}
	return tmpCode;
}

int main()
{
	std::ifstream input("input.txt");
	std::ofstream output("output.txt");

	std::vector<bool> code = GetCode(input);

	std::vector<unsigned> positions;
	unsigned count = 0;

	for (unsigned i = 0; i < code.size() ; ++i)
	{
		if (code[i])
		{
			++count;
			positions.push_back(i);
		}
	}

	for (size_t i = 10; i != 0; --i)
	{

		if (count % 2 == 0)
		{
			code[code.size() - 1] = !code[code.size() - 1];
			if (code[code.size() - 1])
			{
				positions.push_back(code.size() - 1);
			}
			else
			{
				positions.erase(positions.end() - 1);
			}
		}
		else
		{
			if (code[0] && positions.size() == 1)
			{
				code[0] = !code[0];
				positions.clear();
			}
			else
			{
				code[positions[positions.size() - 1] - 1] = !code[positions[positions.size() - 1] - 1];
				if (code[positions[positions.size() - 1] - 1])
				{
					positions.insert(--positions.end(), positions[positions.size() - 1] - 1);
				}
				else
				{
					positions.erase(positions.end() - 2);
				}
			}
		}
		++count;

		for (auto it : code)
		{
			output << static_cast<int>(it);
		}
		output << std::endl;
	}

	return EXIT_SUCCESS;
}

