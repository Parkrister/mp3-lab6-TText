// mp3-lab6-TText.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <stdio.h>
#include "TText.h"

int main()
{
	TTextLink::InitMem();
	TText text;
	text.Read("text.txt");
	text.Print();
	std::cout << '\n';
	std::cout << std::endl << "Free list : ";
	TTextLink::PrintFree();
	TTextLink::Clean(text);
	std::cout << std::endl << "New free list : ";
	TTextLink::PrintFree();
	std::cout << std::endl;
	char str[] = "gamm";
	for (text.Reset(); !text.IsEnd(); text.GoNext())
	{
		if (!strcmp(text.pCurr->str, str))
		{
			text.DelDownLine();
			break;
		}
	}
	std::cout << '\n';
	text.Print();
	std::cout << std::endl << "Free list : ";
	TTextLink::PrintFree();
	TTextLink::Clean(text);
	std::cout << std::endl << "New free list : ";
	TTextLink::PrintFree();
	std::cout << std::endl;
	for (text.Reset(); !text.IsEnd(); text.GoNext())
	{
		if (!strcmp(text.pCurr->str, str))
		{
			text.InsDownLine("new_line");
			break;
		}
	}
	std::cout << '\n';
	text.Print();
	std::cout << std::endl << "Free list : ";
	TTextLink::PrintFree();
	TTextLink::Clean(text);
	std::cout << std::endl << "New free list : ";
	TTextLink::PrintFree();
	std::cout << std::endl;
	for (text.Reset(); !text.IsEnd(); text.GoNext())
	{
		if (!strcmp(text.pCurr->str, str))
		{
			text.DelNextLine();
			break;
		}
	}
	std::cout << '\n';
	text.Print();
	std::cout << std::endl << "Free list : ";
	TTextLink::PrintFree();
	TTextLink::Clean(text);
	std::cout << std::endl << "New free list : ";
	TTextLink::PrintFree();
	std::cout << std::endl;
	//text.SaveS("read.txt");
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
