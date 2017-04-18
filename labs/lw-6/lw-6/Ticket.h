#pragma once

#include "number.h"
#include <iostream>
#include <fstream>

class CTicket
{
public:
	CTicket(std::ifstream &);
	const std::pair<Num, Num> GetValue() const;
	~CTicket();
private:
	Num m_left;
	Num m_right;
	const std::pair<std::string, std::string> GetNumbers(std::ifstream &) const;
};

