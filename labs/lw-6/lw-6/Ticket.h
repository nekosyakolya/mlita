#pragma once

#include "number.h"
#include <iostream>
#include <fstream>

struct TicketNumber
{
	Num left;
	Num right;
};

class CTicket
{
public:
	CTicket(std::ifstream &);
	const TicketNumber GetValue() const;
	bool IsHappy() const;
	~CTicket();
private:
	Num m_left;
	Num m_right;
	const std::pair<std::string, std::string> GetNumbers(std::ifstream &) const;
};

