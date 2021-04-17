// mp3-lab6-TText.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <stdio.h>
#include "TText.h"
TMem TTextLink::mem;

int main()
{
	TTextLink::InitMem(100);
	TText text;
	text.Read("text.txt");
	text.Print();
	puts("------\n");
	text.Reset();
	text.InsDownLine("2");
	text.InsDownSections("1.1");
	text.InsNextSections("1.2");
	text.Print();
	text.GoNextLink();
	text.DelDownLine();
	puts("------\n");
	text.Print();
	putchar('\n');
	TTextLink::PrintFree();
	TTextLink::clean(text);
	TTextLink::PrintFree();
	text.Save("save.txt");
	return 0;
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
