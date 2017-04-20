#include "stdafx.h"
#include <algorithm>
#include <iterator>
#include "Ticket.h"

std::vector<int> SubNumbers(const std::vector<int> &minuend, const std::vector<int> &subtrahend)
{
	int shortNum = 0;
	int coefficient = 0;
	std::vector<int> result;
	for (size_t i = 0; i < minuend.size() && i < subtrahend.size(); ++i)
	{
		shortNum = minuend[i] - subtrahend[i] - coefficient;
		coefficient = 0;
		if (shortNum < 0)
		{
			coefficient = 1;
			shortNum += 10;
		}
		result.push_back(shortNum);
	}

	return result;
}

std::vector<int> AddNumbers(std::vector<int> &first, std::vector<int> &second)
{
	int shortNum = 0;
	int coefficient = 0;
	std::vector<int> result(first.size());
	for (size_t i = 0; i < first.size() && i < second.size(); ++i)
	{
		shortNum = first[i] + second[i] + coefficient;
		coefficient = 0;

		if (shortNum > MAX_BASE)
		{
			(i == result.size() - 1) ? result.push_back(1) : ++coefficient;
			shortNum %= 10;
		}
		result[i] = shortNum;
	}
	return result;
}

unsigned GetSum(unsigned i, const std::vector<int> & number)
{
	unsigned result = 0;
	for (i; i < number.size(); ++i)
	{
		result += number[i];
	}
	return result;
}

void SetShortNumber(size_t i, int &tmp, std::vector<int> &result)
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

std::vector<int> GetNewNumber(const TicketNumber &ticket)
{
	std::vector<int> result = ticket.right.number;
	int tmp = ticket.left.count - (ticket.right.count - ticket.right.number.front());

	for (size_t i = 0; tmp > 0; ++i)
	{
		if (tmp > MAX_BASE)
		{
			result[i] = MAX_BASE;
			tmp += GetSum(i + 1, result);
		}
		else
		{
			SetShortNumber(i, tmp, result);
		}
		
		tmp -= result[i];
	}
	return result;
}

std::vector<int> SetResidue(TicketNumber &number, const std::vector<int> &originalNumber)
{
	std::vector<int> residue;
	if (number.right.number.back() > MAX_BASE || number.right.number.back() > static_cast<int>(number.left.count))
	{
		std::vector<int> minuend(number.right.number.size());
		minuend.push_back(1);
		residue = SubNumbers(minuend, originalNumber);

		number.right.number.back() = 0;
		number.left.IncNumber();
	}
	return residue;
}

void MakeNumberForCount(TicketNumber &number)
{
	unsigned tmp = number.right.count;

	if (number.right.number.size() != 1)
	{
		for (size_t i = 0; (tmp > number.left.count || number.right.number[i] > MAX_BASE) && i < number.right.number.size() - 1; ++i)
		{
			tmp -= number.right.number[i];
			++tmp;
			number.right.number[i] = 0;
			++number.right.number[i + 1];
		}
	}
}

std::vector<int> GetResult(const CTicket &ticket)
{
	TicketNumber ticketNumber = ticket.GetValue();

	std::vector<int> result = { 0 };
	std::vector<int> currResult;
	if (ticketNumber.left.count < ticketNumber.right.count)
	{
		MakeNumberForCount(ticketNumber);
		currResult  = SetResidue(ticketNumber, ticket.GetValue().right.number);
		ticketNumber.right.Count();
	}
	if (!ticket.IsHappy())
	{
		std::vector<int> newNumber = GetNewNumber(ticketNumber);
		result = (currResult.size() != 0) ? AddNumbers(newNumber, currResult) : SubNumbers(newNumber, ticket.GetValue().right.number);
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

