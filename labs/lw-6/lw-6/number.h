#pragma once
#include <vector>
#include <string>

static const int MAX_BASE = 9;

struct Num
{
	std::vector<int> number;
	unsigned count = 0;
	
	void IncNumber()
	{
		size_t i = 0;
		for (i; i < number.size(); ++i)
		{
			if (number[i] + 1 > MAX_BASE)
			{
				number[i] = 0;
			}
			else
			{
				break;
			}
		}

		if (i < number.size())
		{
			++number[i];
		}
		Count();
	}

	void Count()
	{
		count = 0;
		for (unsigned i = 0; i < number.size(); ++i)
		{
			count += number[i];
		}
	}

	void Initialization(const std::string &number)
	{
		ReadNumber(number);
		Count();
	}
private:
	void ReadNumber(const std::string &numberStr)
	{
		std::vector<int> num(numberStr.length());
		for (int i = numberStr.length() - 1, j = 0; i >= 0; --i, ++j)
		{
			num[j] = static_cast<int>(numberStr[i]) - '0';
		}
		std::swap(num, number);
	}
};

