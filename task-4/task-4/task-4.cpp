// task-4.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <string>

static const int numLen = 2000;


std::vector<int> ReadNumber(std::string n)
{
	std::vector<int> num(numLen);
	for (int i = n.length() - 1, j = 0; i >= 0; --i, ++j)
	{
		num[j] = static_cast<int>(n[i]) - '0';
	}
	return num;
}

std::string SubNumbers(std::vector<int> &num1, std::vector<int> &num2)
{
	int shortNum = 0;

	std::string result = "";
	for (size_t i = 0; i < num1.size(); ++i)
	{
		shortNum = num1[i] - num2[i];

		if (shortNum < 0)
		{
			--num1[i + 1];
			shortNum += 10;
		}
		result += static_cast<char>(shortNum) + '0';
	}

	return result;
}


void OutputResult(std::string result)
{
	std::ofstream output("output.txt");
	int j = result.length() - 1;
	for (j; j >= 0 && result[j] == '0'; --j)
	{
	}
	if (j > 0)
	{
		for (j; j >= 0; --j)
		{
			output << result[j];
		}
	}
	else
	{
		output << "0";
	}
	output << std::endl;
}


int main()
{
	std::string firstNum = "";
	std::string secondNum = "";
	
	std::ifstream input("input.txt");

	input >> firstNum;
	input.get();
	input >> secondNum;

	std::vector<int> num1 = ReadNumber(firstNum);
	std::vector<int> num2 = ReadNumber(secondNum);



	std::string result = SubNumbers(num1, num2);


	OutputResult(result);

	
	return 0;
}

