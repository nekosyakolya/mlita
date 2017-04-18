#include "stdafx.h"
#include "Ticket.h"



const std::pair<std::string, std::string> CTicket::GetNumbers(std::ifstream &input) const
{
	size_t lengthNumber = 0;
	input >> lengthNumber;
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

const std::pair<Num, Num> CTicket::GetValue() const
{
	return std::make_pair(m_left, m_right);
}


CTicket::~CTicket()
{
}

