#include "stdafx.h"
#include "Ticket.h"

const std::pair<std::string, std::string> CTicket::GetNumbers(std::ifstream &input) const
{
	size_t lengthNumber = 0;
	input >> lengthNumber;
	if (lengthNumber > MAX_LENGTH)
	{
		throw std::logic_error("Is not a valid length\n");
	}
	input.get();

	std::string tmpString;
	input >> tmpString;
	std::string firstNum = tmpString.substr(0, lengthNumber);
	std::string secondNum = tmpString.substr(lengthNumber);
	return std::make_pair(firstNum, secondNum);
}

CTicket::CTicket(std::ifstream &input)
{
	std::pair<std::string, std::string> numbers = GetNumbers(input);
	m_left.Initialization(numbers.first);
	m_right.Initialization(numbers.second);
}

const TicketNumber CTicket::GetValue() const
{
	TicketNumber tmp;
	tmp.left = m_left;
	tmp.right = m_right;
	return tmp;
}

bool CTicket::IsHappy() const
{
	return m_left.count == m_right.count;
}

CTicket::~CTicket()
{
}

