#include "stdafx.h"

#include <algorithm>
#include <iterator>

#include "Ticket.h"

std::vector<int> SubNumbers(std::vector<int> &num1, std::vector<int> &num2)
{
	int shortNum = 0;

	std::vector<int> result;
	for (size_t i = 0; i < num1.size() && i < num2.size(); ++i)
	{
		shortNum = num1[i] - num2[i];

		if (shortNum < 0)
		{
			--num1[i + 1];
			shortNum += 10;
		}
		result.push_back(shortNum);
	}

	return result;
}


std::vector<int> AddNumbers(std::vector<int> &num1, std::vector<int> &num2)
{
	int shortNum = 0;
	int inc = 0;
	std::vector<int> result(num1.size());
	for (size_t i = 0; i < num1.size() && i < num2.size(); ++i)
	{
		shortNum = num1[i] + num2[i] + inc;
		inc = 0;

		if (shortNum > MAX_BASE)
		{
			if (i == result.size() - 1)
			{
				result.push_back(1);
			}
			else
			{
				++inc;
			}
			shortNum %= 10;
		}
		result[i] = shortNum;
	}

	return result;
}


std::vector<int> CountNewNumber(const std::pair <Num, Num> &numberTicket)
{
	std::vector<int> result = numberTicket.second.number;
	unsigned currResult = numberTicket.second.count - numberTicket.second.number.front();

	int tmp = numberTicket.first.count - currResult;
	for (size_t i = 0, j = numberTicket.second.number.size() - 1; tmp > 0; ++i, --j)
	{
		if (tmp > MAX_BASE)
		{
			result[i] = MAX_BASE;
		}
		else
		{
			if (tmp <= result[i])
			{
				result[i] += tmp;
				if (result[i] > MAX_BASE)
				{
					result[i + 1] = result[i] - MAX_BASE;
					result[i] = MAX_BASE;
					tmp -= result[i + 1];
				}
			}
			else
			{
				result[i] = tmp;
			}
		}
		tmp -= result[i];
	}

	return result;

}

std::vector<int> GetResult(const CTicket &ticket)
{
	std::pair <Num, Num> number = ticket.GetValue();

	std::vector<int> result = { 0 };
	if (number.first.count > number.second.count)
	{
		std::vector<int> newNumber = CountNewNumber(number);
		result = SubNumbers(newNumber, number.second.number);
	}
	else if (number.first.count < number.second.count)
	{
		unsigned tmp = number.second.count;
		std::vector<int> tmpNum = number.second.number;

		if (number.second.number.size() != 1)
		{
			for (size_t i = 0; (tmp > number.first.count || number.second.number[i] > MAX_BASE) && i < number.second.number.size() - 1; ++i)
			{
				tmp -= number.second.number[i];
				++tmp;
				number.second.number[i] = 0;
				++number.second.number[i + 1];
			}
		}
		std::vector<int> tmpRes;
		if (number.second.number.back() > MAX_BASE || number.second.number.back() > number.first.count)
		{
			std::vector<int> tmp(tmpNum.size());
			tmp.push_back(1);
			tmpRes = SubNumbers(tmp, tmpNum);

			number.second.number.back() = 0;
			number.first.IncNumber();
		}
		number.second.Count();

		std::vector<int> newNumber = CountNewNumber(number);
		result = (tmpRes.size() != 0) ? AddNumbers(newNumber, tmpRes) : SubNumbers(newNumber, tmpNum);

	}
	return result;

}


void OutputResult(std::vector<int>& result, std::ofstream &output)
{
	while (result.size() > 1)
	{
		if (*result.rbegin() == 0)
		{
			result.pop_back();
		}
		else
		{
			break;
		}
	}
	std::copy(result.rbegin(), result.rend(), std::ostream_iterator<int>(output));
}

int main()
{
	std::ifstream input("input.txt");
	std::ofstream output("output.txt");
	try
	{
		CTicket ticket(input);
		std::vector<int> result = GetResult(ticket);
		OutputResult(result, output);
	}
	catch (const std::logic_error &error)
	{
		std::cerr << error.what() << std::endl;;
	}
	return EXIT_SUCCESS;
}

