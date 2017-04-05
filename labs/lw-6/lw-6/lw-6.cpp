#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <string>


struct Num
{
	std::vector<unsigned> number;
	unsigned count = 0;
};


std::vector<unsigned> ReadNumber(std::string n, unsigned lenght)
{
	std::vector<unsigned> num(lenght);
	for (int i = n.length() - 1, j = 0; i >= 0; --i, ++j)
	{
		num[j] = static_cast<unsigned>(n[i]) - '0';
	}
	return num;
}

unsigned GetNum(const std::vector<unsigned> &number, unsigned pos)
{
	unsigned result = 0;
	for (unsigned i = pos; i < number.size(); ++i)
	{
		result += number[i];
	}
	return result;
}

//
//void SetNum(const std::string &str, unsigned &result, unsigned &resultNum)
//{
//	result = 0;
//	resultNum = 0;
//	for (auto el : str)
//	{
//		result += static_cast<unsigned>(el) - '0';
//		resultNum *= 10;
//		resultNum += static_cast<unsigned>(el) - '0';
//	}
//}


//���� �������� �� ������������
void IncNumber(std::vector<unsigned> &number, unsigned i)
{
	for (;number[i] + 1 > 9; ++i)
	{
	}
	++number[i];
}

int main()
{

	std::ifstream input("input.txt");

	unsigned numLenght = 0;
	input >> numLenght;
	input.get();

	std::string tmpString;

	input >> tmpString;
	std::string firstNum = tmpString.substr(0, numLenght);
	std::string secondNum = tmpString.substr(numLenght);


	Num first;
	Num second;


	first.number = ReadNumber(firstNum, numLenght);
	first.count = GetNum(first.number, 0);

	second.number = ReadNumber(secondNum, numLenght);
	second.count = GetNum(second.number, 0);


	if (first.count == second.count)
	{
		std::cout << 0;
	}
	else
	{

		unsigned currResult = GetNum(second.number, 1);

		if (first.count <= currResult)
		{
			IncNumber(first.number, 0);//����������� ������
			first.count = GetNum(first.number, 0);//������� ����� ������

			//��� ���� ��� ��������� ����� ��� �������� �����


			//�� ���� �� 10 � ������� numLenght ������� second.count
			std::vector<unsigned> tmp(numLenght);
			second.number = tmp;//�������� ������


			tmp.push_back(1);


			second.count = 0;//������� ����� ������

		}
		else
		{



		}
			//��� ��������� �� first.count �����,��� ����� ���������� ���� ���������
		//���������� �� ��� ����� ������ ��� ����� 10--��� ����?
		//��� ������ ����������
		// � ���� ������� ������� � �������������� �������� 1

		//��� ���� 02 98  ��� 02 09 ��� 02 90   //83 91   //83 93
	}

	return 0;
}

