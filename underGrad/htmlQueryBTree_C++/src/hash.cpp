#include"hash.h"
#include"CharString.h"
#include<time.h>

htmlhash dichash;

#pragma once

int hashfunc(CharString &term)
{
	int loc = 1;
	int i = 0;
	for(i = 0;i < term.length;i++)
		loc = abs((loc * term.data[i])) % HashSize;
	return loc;
}

int reduceconflict(int loc)
{
	while(dichash.map[loc] != NULL)
		loc = (loc + 1) % HashSize;
	return loc;
}//���ڹ�ϣ�����ǵݳ˵ģ����Ӧ�ýϴ��������˳������������ͻ

bool hashsearch(CharString term, int& loc)
{
	loc = hashfunc(term);
	while(dichash.map[loc])
	{
		if(dichash.map[loc] -> term == term)
			return true;
		else
			loc = (loc + 1) % HashSize;
	}
	return false;
}//���ù�ϣ���������

bool mapping()
{
	dichash.map = new Keyword*[HashSize];
	if(!dichash.map)
		return false;//�ڴ����ʧ��
	else
	{
		for(int i = 0; i < HashSize; i++)
			dichash.map[i] = NULL;
		ifstream inFile("�ִ�.txt");
		if (!inFile)
			return false;
		char* c = new char[10000];
		CharString ending("##");
		int n = 1;//������¼��ǰ��html�����
		int judge = 0;
		int loc = 0;
		Keyword* kp;
		DocLink* lp;
		int num = 0;
		int ID = 1;
		while(!inFile.eof() && n == 1)
		{
			inFile.getline(c,10000);
			CharString term(c);
			if(term == ending)
			{
				n++;
				continue;
			}
			if(term.data[0] >= 0)
				continue;
			judge = hashsearch(term, loc);
			if(judge == 0)
			{
				loc = hashfunc(term);
				if(dichash.map[loc])
					loc = reduceconflict(loc);
				lp = new DocLink;
				lp->termID = ID;
				lp->head = new DocNode;
				lp->head->DocID = n;
				lp->head->times = 1;
				lp->head->next = NULL;
				kp = new Keyword;
				kp->term = term;
				kp->termID = ID;
				kp->DF = 1;
				kp->occur = 1;
				kp->l = lp;
				dichash.map[loc] = kp;
				ID++;
			}
			else
			{
				DocNode* dp = NULL;
				int j = dichash.map[loc] -> l -> search(n, dp);
				if(j == 1)
				{
					dichash.map[loc] -> l -> edit(1, dp);
					dichash.map[loc] -> occur++;
				}
				else
				{
					dichash.map[loc] -> l -> insert(n);
					dichash.map[loc] -> DF++;
					dichash.map[loc] -> occur++;
				}
			}
		}
		inFile.close();
		return true;
	}
}

void hashdoc()
{
	while(1)
	{
		int loc = 0;
		double timehash, timehashover;
		char a[100];
		CharString b("#");
		cin >> a;
		CharString c(a);
		if(c == b) break;
		timehash = clock();
		int i = hashsearch(c, loc);
		if(i == 1)
		{
			DocNode* dp = dichash.map[loc]-> l -> head;
			while(dp)
			{
				cout << dp -> DocID << endl;
				dp = dp -> next;
			}
			timehashover = clock();
			cout << "��ѯ��ʱ��" << (timehashover - timehash) / 1000 << "��" << endl;
		}
	}
}