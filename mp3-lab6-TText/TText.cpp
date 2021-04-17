#include "TText.h"
TTextLink::TTextLink(const char* s, TTextLink* next, TTextLink* down)
{
	flag = true;
	pNext = next;
	pDown = down;
	if (s != NULL)
	{
		int i = 0;
		do {
			str[i] = s[i];
			i++;
		} while (s[i - 1] != '\0');
	}
	else
	{
		str[0] = '\0';
	}
}
void TTextLink::InitMem(int s)
{
	int size = sizeof(TTextLink) * s;
	mem.pFirst = mem.pFree = (TTextLink*)malloc(size);
	mem.pLast = mem.pFirst + (s - 1);
	TTextLink* tmp = mem.pFirst;
	while (tmp != mem.pLast)
	{
		tmp->pNext = tmp + 1;
		tmp->flag = true;
		tmp->str[0] = '\0';
		tmp = tmp->pNext;
	}
	tmp->pNext = NULL;
	tmp->flag = true;
	tmp->str[0] = '\0';
}
void TTextLink::clean(TText& t)
{
	TTextLink* tmp = mem.pFree;
	while (tmp != mem.pLast)
	{
		tmp->flag = false;
		tmp = tmp->pNext;
	}
	tmp->flag = false;
	for (t.Reset(); !t.IsEmpty(); t.GoNext())
	{
		t.GetCurr()->flag = false;
	}
	tmp = mem.pFirst;
	while (tmp != mem.pLast)
	{
		if (tmp->flag)
		{
			TText::operator delete(tmp);
		}
		else
			tmp->flag = true;
		tmp = tmp + 1;
	}
	if (tmp->flag)
	{
		TText::operator delete(tmp);
	}
	else
		tmp->flag = true;
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
TText::TText()
{
	pFirst = NULL;
	pCurr = NULL;
}
void TText::GoFirstLink()
{
	while (!st.empty())
		st.pop();
	pCurr = pFirst;
}
void TText::GoNextLink()
{
	if (pCurr->pNext)
	{
		st.push(pCurr);
		pCurr = pCurr->pNext;
	}
}
void TText::GoDownLink()
{
	if (pCurr->pDown)
	{
		st.push(pCurr);
		pCurr = pCurr->pDown;
	}
}
void TText::GoPrevLink()
{
	if (!st.empty())
	{
		pCurr = st.top();
		st.pop();
	}
}
void TText::InsNextLine(const char* s)
{
	if (pCurr)
	{
		TTextLink* t = (TTextLink*)(TText::operator new(1));
		strcpy_s(t->str, s);
		t->pNext = pCurr->pNext;
		t->pDown = NULL;
		pCurr->pNext = t;
	}
}
void TText::InsNextSections(const char* s)
{
	if (pCurr)
	{
		TTextLink* t = (TTextLink*)(TText::operator new(1));
		strcpy_s(t->str, s);
		t->pNext = NULL;
		t->pDown = pCurr->pNext;
		pCurr->pNext = t;
	}
}
void TText::InsDownLine(const char* s)
{
	if (pCurr)
	{
		TTextLink* t = (TTextLink*)(TText::operator new(1));
		strcpy_s(t->str, s);
		t->pNext = pCurr->pDown;
		t->pDown = NULL;
		pCurr->pDown = t;
	}
}
void TText::InsDownSections(const char* s)
{
	if (pCurr)
	{
		TTextLink* t = (TTextLink*)(TText::operator new(1));
		strcpy_s(t->str, s);
		t->pDown = pCurr->pDown;
		t->pNext = NULL;
		pCurr->pDown = t;
	}
}
void TText::DelNextLine()
{
	if (pCurr && pCurr->pNext)
	{
		TTextLink* t = pCurr->pNext;
		pCurr->pNext = t->pNext;
		TText::operator delete(t);
	}
}
void TText::DelDownLine()
{
	if (pCurr && pCurr->pDown)
	{
		TTextLink* t = pCurr->pDown;
		pCurr->pDown = t->pNext;
		TText::operator delete(t);
	}
}

void TText::Print()
{
	int level = 0;
	TText::PrintRec(pFirst, level);
}
void TText::PrintRec(TTextLink* t, int level)
{
	if (t != NULL)
	{
		for (int i = 0; i < level; i++)
			std::cout << ' ';
		std::cout << t->str << std::endl;
		++level;
		PrintRec(t->pDown, level);
		level--;
		PrintRec(t->pNext, level);
	}
}
void TText::Save(const char* file_name)
{
	std::ofstream ofs(file_name);
	SaveRec(pFirst, ofs);
	ofs.close();
}
void TText::SaveRec(TTextLink* t, std::ofstream& ofs)
{
	if (t != NULL)
	{
		ofs << t->str << '\n';
		if (t->pDown)
		{
			ofs << '{' << '\n';
			SaveRec(t->pDown, ofs);
			ofs << '}' << '\n';
		}
		if (t->pNext)
			SaveRec(t->pNext, ofs);
	}
}
void TText::Read(const char* file_name)
{
	std::ifstream ifs(file_name);
	pFirst = ReadRec(ifs);
	ifs.close();
}
TTextLink* TText::ReadRec(std::ifstream& ifs)
{
	TTextLink* pF, * pC;
	pF = NULL;
	pC = NULL;
	char buff[MAX_SIZE];
	while (!ifs.eof())
	{
		ifs.getline(buff, MAX_SIZE, '\n');
		if (buff[0] == '}')
			break;
		if (buff[0] == '{')
		{
			pC->pDown = ReadRec(ifs);
		}
		else
		{
			if (!pC)
			{
				TTextLink* t = (TTextLink*)(TText::operator new(1));
				strcpy_s(t->str, buff);
				t->pDown = NULL;
				t->pNext = NULL;
				pF = t;
				pC = pF;
			}
			else
			{
				TTextLink* t = (TTextLink*)(TText::operator new(1));
				strcpy_s(t->str, buff);
				t->pDown = NULL;
				t->pNext = NULL;
				pC->pNext = t;
				pC = t;
			}
		}
	}
	return pF;
}

void TText::Reset()
{
	if (pFirst)
	{
		while (!st.empty())
			st.pop();
		pCurr = pFirst;
		st.push(pFirst);
		if (pFirst->pNext)
			st.push(pFirst->pNext);
		if (pFirst->pDown)
			st.push(pFirst->pDown);
	}
}
void TText::GoNext()
{
	if (!st.empty())
	{
		pCurr = st.top();
		st.pop();
		if (pCurr != pFirst)
		{
			if (pCurr->pDown)
				st.push(pCurr->pDown);
			if (pCurr->pNext)
				st.push(pCurr->pNext);
		}
	}
}
bool TText::IsEmpty()
{
	return st.empty();
}
void* TText::operator new(std::size_t n)
{
	TTextLink* pC = mem.pFree;
	if (mem.pFree)
		mem.pFree = mem.pFree->pNext;
	return pC;
}
void TText:: operator delete(void* memory)
{
	TTextLink* pC = (TTextLink*)memory;
	pC->pNext = mem.pFree;
	mem.pFree = pC;
}