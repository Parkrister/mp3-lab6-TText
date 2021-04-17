#pragma once
#include<iostream>
#include<fstream>
#include<stdio.h>
#include<algorithm>
#include<stack>
#include<set>

const int MAX_SIZE = 80;
const int MaxMemorySize = 100;

struct  TTextLink;
class TText;
struct  TMem
{
	TTextLink* pFirst, * pFree, * pLast;
};

struct TTextLink {
	TTextLink* pNext;
	TTextLink* pDown;
	char str[MAX_SIZE];
	bool flag;
	static TMem mem;
	static void InitMem(int size = MaxMemorySize);
	static void clean(TText& t);
	static void PrintFree();
	//конструктор
	TTextLink(const char* s = NULL, TTextLink* next = NULL, TTextLink* down = NULL);
};

class TText: private TTextLink
{
	TTextLink* pFirst;
	TTextLink* pCurr;
	std::stack<TTextLink*>st;
	//рекурсивна€ печать. ¬нутренн€€ функци€ 
	void PrintRec(TTextLink* t, int level);
	//рекурсивный вывод в файл. ¬нутренн€€ функци€
	void SaveRec(TTextLink* t, std::ofstream& ofs);
	//рекурсивное чтение из файла. ¬нутренн€€ функци€
	TTextLink* ReadRec(std::ifstream& ifs);
public:
	//конструктор по умолчанию
	TText();
	//конструктор копировани€
	//TText(const TText& t);
	//переместить указатель на текущий на первый элемент и очистить стек
	void GoFirstLink();
	//перейти к следующему элементу по иерархии после текущего
	void GoNextLink();
	//перейти к нижнему (вложенному) элементу по иерархии после текущего
	void GoDownLink();
	//вернутьс€ к предыдущему элементу
	void GoPrevLink();
	//добавить следующий по иерархии элемент и присоединить к нему pNext текущего как pNext
	void InsNextLine(const char* s);
	//добавить следующий по иерархии элемент и присоединить к нему pNext текущего как pDown
	void InsNextSections(const char* s);
	//добавить вложенный по иерархии элемент и присоединить к нему pDown текущего как pNext
	void InsDownLine(const char* s);
	//добавить вложенный по иерархии элемент и присоединить к нему pDown текущего как pDown 
	void InsDownSections(const char* s);
	//удалить у текущего следующую по иерархии секцию
	void DelNextLine();
	//удалить у текущего вложенную по иерархии секцию
	void DelDownLine();
	//печать на экран (через вызов рекурсивной печати). ¬нешн€€ функци€
	void Print();
	//вывод в файл (через вызов рекурсивного вывода). ¬нешн€€ функци€ 
	void Save(const char* file_name);
	//чтение из файла (через вызов рекурсивоного чтени€). ¬нешн€€ функци€ 
	void Read(const char* file_name);
	//печать на экран с помощю стека
	void PrintS();
	//сохранение в файл с помощью стека
	void SaveS(const char* file_name);
	//чтение из файла с помощью стека
	void ReadS(const char* file_name);
	//навигаци€ по тексту 
	void Reset();
	void GoNext();
	bool IsEmpty();
	TTextLink* GetCurr() { return pCurr; }
	//переопределение операторов работы с пам€тью
	void* operator new(std::size_t n);
	void operator delete (void* memory);
};