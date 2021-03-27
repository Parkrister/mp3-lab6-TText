#pragma once
#include <stdlib.h>
#include <string.h>
#include "stack.h"
#include <iostream>
#include <fstream>
using namespace std;

const size_t MaxLen = 80;

class TTextLink
{
public:
	TTextLink* pNext, * pDown;
	char str[MaxLen];
	TTextLink(char* s = nullptr, TTextLink* pn = nullptr, TTextLink* pd = nullptr) {
		if (s == nullptr)
			str[0] = '\0';
		else {
			strcpy(str, s);
		}
		pNext = pn;
		pDown = pd;
	}
	~TTextLink();
};

class TText {
	TTextLink *pFirst, *pCurr;
	stack<TTextLink*> st;
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

	void InsNextSection(char* s) {
		TTextLink* tmp = new TTextLink(s, NULL, pCurr->pNext);
		pCurr->pNext = tmp;
	}
	void InsDownLine(char* s) {
		TTextLink* tmp = new TTextLink(s, pCurr->pDown);
		pCurr->pDown = tmp;
	}
	void InsDownSection(char* s) {
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
	void DelDownSection() {
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
	void Save(char* fn) {
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
	void Read(char* fn) {
		ifstream ifs(fn);
		pFirst = ReadRec(ifs);
		ifs.close();
	}
	TTextLink* ReadRec(ifstream& ifs) {
		TTextLink* pF, * pC;
		pF = pC = NULL;
		char Buff[MaxLen];
		while (!ifs.eof()) {
			Buff = ifs.getline(Buff, MaxLen, '\n');
		}
	}
};