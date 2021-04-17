#pragma once
#include <stdlib.h>
#include <string.h>
#include "stack.h"
#include <iostream>
#include <fstream>

#define _CRT_SECURE_NO_WARNINGS
using namespace std;

const size_t MaxLen = 80;
const size_t MaxMemorySize = 100;

class TText;
class TTextLink;

struct TMem {
	TTextLink* pFirst, * pLast, * pFree;
};

class TTextLink
{
public:
	TTextLink* pNext, * pDown;
	bool flag;
	static TMem mem;
	char str[MaxLen];
	TTextLink(const char* s = NULL, TTextLink* pn = NULL, TTextLink* pd = NULL) {
		if (s == nullptr)
			str[0] = '\0';
		else {
			strcpy_s(str, s);
		}
		pNext = pn;
		pDown = pd;
	}
	static void InitMem(size_t size = MaxMemorySize);
	//~TTextLink();
	static void PrintFree();
	static void Clean(TText& t);

	void* operator new(size_t n);
	void operator delete(void* p);
};

class TText {
public:
	
	TTextLink *pFirst, *pCurr;
	stack<TTextLink*> st;
	TText() { pFirst = NULL; pCurr = NULL; }
	void GoFirstLink() {
		pCurr = pFirst;
		st.Clear();
	}
	void GoNextLink() {
		if (pCurr->pNext) {
			st.push(pCurr);
			pCurr = pCurr->pNext;
		}
	}
	void GoPrevLink() {
		if (pFirst != pCurr)
			pCurr = st.pop();
	}

	void GoDownLink() {
		st.push(pCurr);
		pCurr = pCurr->pDown;
	}

	void InsNextLine(char* s) {
		TTextLink* tmp = new TTextLink(s, pCurr->pNext);
		pCurr->pNext = tmp;
	}

	void InsNextSection(const char* s) {
		TTextLink* tmp = new TTextLink(s, NULL, pCurr->pNext);
		pCurr->pNext = tmp;
	}
	void InsDownLine(const char* s) {
		TTextLink* tmp = new TTextLink(s, pCurr->pDown);
		pCurr->pDown = tmp;
	}
	void InsDownSection(const char* s) {
		TTextLink* tmp = new TTextLink(s, NULL, pCurr->pDown);
		pCurr->pDown = tmp;
	}
	void DelNextLine() {
		if (pCurr->pNext) {
			TTextLink* tmp = pCurr->pNext;
			pCurr->pNext = tmp->pNext;
			delete tmp;
		}
	}
	void DelDownLine() {
		if (pCurr->pDown) {
			TTextLink* tmp = pCurr->pDown;
			pCurr->pDown = tmp->pNext;
			delete tmp;
		}
	}

	// Печать текста
	void Print() {
		PrintRec(pFirst);
	}
	void PrintRec(TTextLink* t) {
		int level = 1;
		if (t != NULL) {
			for (int i = 0; i < level; i++) {
				std::cout << ' ';
				std::cout << t->str << '\n';
				level++;
				PrintRec(t->pDown);
				level--;
				PrintRec(t->pNext);
			}
		}
	}

	// Запись в файл
	void Save(const char* fn) {
		ofstream ost(fn);
		SaveRec(pFirst, ost);
		ost.close();
	}
	void SaveRec(TTextLink* t, ofstream& ost) {
		if (t != NULL) {
			ost << t->str << '\n';
			if (t->pDown != NULL) {
				ost << '{\n';
				SaveRec(t->pDown, ost);
				ost << '}\n';
			}
			if (t->pNext != NULL)
				SaveRec(t->pNext, ost);
		}
	}

	// Чтение из файла
	void Read(const char* fn) {
		ifstream ifs(fn);
		pFirst = ReadRec(ifs);
		ifs.close();
	}
	TTextLink* ReadRec(std::ifstream& ifs) {
		TTextLink* pF, * pC;
		pF = pC = NULL;
		char Buff[MaxLen];
		while (!ifs.eof()) {
			ifs.getline(Buff, MaxLen, '\n');
			if (Buff[0] == '}')
				break;
			else if (Buff[0] == '{')
				pC->pDown = ReadRec(ifs);
			else {
				TTextLink* tmp = new TTextLink(Buff);
				if (pC == NULL)
					pF = pC = NULL;
				else {
					pC->pNext = tmp;
					pC = pC->pNext;
				}
			}
		}
		return pF;
	}

	//void Reset() { pCurr = pFirst; }
	void GoNext() {
		pCurr = st.pop();
		if (pCurr != pFirst) {
			if (pCurr->pNext)
				st.push(pCurr->pNext);
			if (pCurr->pDown)
				st.push(pCurr->pDown);
		}
	}
	bool IsEnd() { return st.empty(); }
	void Reset() {
		if (pFirst) {
			st.Clear();
			pCurr = pFirst;
			st.push(pFirst);
			if (pCurr->pNext)
				st.push(pCurr->pNext);
			if (pCurr->pDown)
				st.push(pCurr->pDown);
		}
	}

};
