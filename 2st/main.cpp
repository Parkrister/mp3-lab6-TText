#include"Text.h"
TMem TTextLink::mem;
void main()
{
	TTextLink::InitMem();
	TText text;
	text.Read("text.txt");
	text.Print();
	std::cout << '\n';
	std::cout << std::endl << "Free list : ";
	TTextLink::PrintFree();
	TTextLink::clean(text);
	std::cout << std::endl << "New free list : ";
	TTextLink::PrintFree();
	std::cout << std::endl;
	char str[] = "gamm";
	for (text.Reset(); !text.IsEmpty(); text.GoNext())
	{
		if (!strcmp(text.GetCurr()->str, str))
		{
			text.DelDownLine();
			break;
		}
	}
	std::cout << '\n';
	text.Print();
	std::cout << std::endl << "Free list : ";
	TTextLink::PrintFree();
	TTextLink::clean(text);
	std::cout << std::endl << "New free list : ";
	TTextLink::PrintFree();
	std::cout << std::endl;
	for (text.Reset(); !text.IsEmpty(); text.GoNext())
	{
		if (!strcmp(text.GetCurr()->str, str))
		{
			text.InsDownLine("new_line");
			break;
		}
	}
	std::cout << '\n';
	text.Print();
	std::cout << std::endl << "Free list : ";
	TTextLink::PrintFree();
	TTextLink::clean(text);
	std::cout << std::endl << "New free list : ";
	TTextLink::PrintFree();
	std::cout << std::endl;
	for (text.Reset(); !text.IsEmpty(); text.GoNext())
	{
		if (!strcmp(text.GetCurr()->str, str))
		{
			text.DelNextLine();
			break;
		}
	}
	std::cout << '\n';
	text.Print();
	std::cout << std::endl << "Free list : ";
	TTextLink::PrintFree();
	TTextLink::clean(text);
	std::cout << std::endl << "New free list : ";
	TTextLink::PrintFree();
	std::cout << std::endl;
	text.SaveS("read.txt");
}