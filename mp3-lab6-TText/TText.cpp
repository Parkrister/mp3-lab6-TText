#include "TText.h"

void TTextLink::InitMem(size_t size) {
	int Size = sizeof(TTextLink) * size;
	mem.pFirst = mem.pFree = (TTextLink*)malloc(Size);
	mem.pLast = mem.pFirst + (Size - 1);
	TTextLink* tmp = mem.pFirst;
	while (tmp != mem.pLast) {
		tmp->pNext = tmp + 1;
		tmp->flag = false;
		tmp = tmp->pNext;
		tmp->str[0] = '\n';
	}
	tmp->pNext = NULL;
	tmp->flag = false;
}

void TTextLink::PrintFree()
{
	TTextLink* tmp = mem.pFree;
	while (tmp != mem.pLast)
	{
		if (tmp->str[0] != '\0')
			std::cout << tmp->str << ' ';
		tmp = tmp->pNext;
	}
	if (tmp->str[0] != '\0')
		std::cout << tmp->str << ' ';
}

void* TTextLink::operator new(size_t n) {
	TTextLink* pC = mem.pFree;
	if (mem.pFree != NULL)
		mem.pFree = pC->pNext;
	return pC;
}
void TTextLink::operator delete(void* p) {
	TTextLink* pC = (TTextLink*)p;
	pC->pNext = mem.pFree;
	mem.pFree = pC;
}

void TTextLink::Clean(TText& t)
{
	TTextLink* tmp = mem.pFree;
	while (tmp != mem.pLast)
	{
		tmp->flag = false;
		tmp = tmp->pNext;
	}
	tmp->flag = false;
	for (t.Reset(); !t.IsEnd(); t.GoNext())
	{
		t.pCurr->flag = false;
	}
	tmp = mem.pFirst;
	while (tmp != mem.pLast)
	{
		if (tmp->flag)
		{
			TTextLink::operator delete(tmp);
		}
		else
			tmp->flag = true;
		tmp = tmp + 1;
	}
	if (tmp->flag)
	{
		TTextLink::operator delete(tmp);
	}
	else
		tmp->flag = true;
}
