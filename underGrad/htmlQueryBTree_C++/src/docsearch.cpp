//���������ĵ�&&����
#include "dictionaryBTree.h"
#include <fstream>
#include <iostream>
#include<time.h>

using namespace std;

#pragma once

BTree DicTree;
void OutputBTree(BTNode* root);

//����ҳ�ִʽ����B��
bool createBTree()
{
	ifstream inFile("�ִ�.txt");
	if (!inFile)
		return false;
	char* c = new char[10000];
	CharString ending("##");
	int n = 1;
	int judge = 0;
	BTNode* bp = NULL;
	Keyword* kp;
	DocLink* lp;
	int num = 0;
	int ID = 1;
	while(!inFile.eof())
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
		judge = DicTree.search(term, num, bp);
		if(judge == 1)
			DicTree.edit(bp, num, n);
		else
		{
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
			DicTree.insert(kp, num, bp);
			ID++;
		}
	}
	inFile.close();
	ofstream outFile("�ִ�B��.txt");
	outFile.close();
	OutputBTree(DicTree.root);
	delete c;
	return true;
}
//return���йؼ��ʸ���
int numcount(BTNode* root)
{
	int count = 0;
	if(!root)
		return 0;
	else
	{
		for(int i = 0; i <= root -> n;i++)
			count += numcount(root -> child[i]);
		count += root -> n;
		return count;
	}
}
//return���еĹؼ����ۼƴ���
int addcount(BTNode* root)
{
	int count = 0;
	if(!root)
		return 0;
	else
	{
		for(int i = 0;i <= root -> n;i++)
			count += addcount(root -> child[i]);
		for(int i = 0; i < root -> n;i++)
			count += root -> key[i] -> occur;
		return count;
	}
}

void OutputDocLink(DocLink * lp)
{
	if(!lp)
		return ;
	else
	{
		ofstream outFile("�ִ�B��.txt",ios::app);
		DocNode*p = lp->head;
		while(p)
		{
			outFile << p->DocID << endl;
			outFile << p->times << endl;
			p = p->next;
		}
		outFile.close();
	}
}
//�����õ���������ٶ���
void OutputBTree(BTNode* root)
{
	if(!root)
		return;
	else
	{
		for(int i = 0;i < root->n;i++)
		{
			Keyword* k = root->key[i];
			ofstream outFile("�ִ�B��.txt",ios::app);
			outFile << k->term.data << endl;
			outFile << k->termID << endl;
			outFile << k-> DF << endl;
			outFile << k->occur << endl;
			outFile.close();
			OutputDocLink(k->l);
		}
		for(int i = 0;i <= root->n;i++)
			OutputBTree(root->child[i]);
	}
}

void resetBTree()
{
	ifstream inFile("�ִ�B��.txt");
	if(!inFile)
		return;
	else
	{
		char *c = new char [1000];
		int termID = 0;
		int df = 0;
		int occur = 0;
		int i = 0;
		int count = 1;
		BTNode* bp = NULL;
		int num = 0;
		while(!inFile.eof())
		{
			if(count % 100 == 0)
				cout << count << endl;
			inFile>>c;
			CharString term(c);
			inFile >> termID;
			inFile >> df;
			inFile >> occur;
			DocLink* lp = new DocLink;
			lp->termID = termID;
			DocNode* p = lp->head;
			DocNode* dp;
			for(i = 1;i <= df;i++)
			{
				dp = new DocNode;
				inFile >> dp->DocID;
				inFile >> dp->times;
				dp->next = NULL;
				if(i == 1)
					lp->head = dp;
				else
					p->next = dp;
				p = dp;
			}
			Keyword* k = new Keyword;
			k->DF = df;
			k->l = lp;
			k->term = term;
			k->occur = occur;
			k->termID = termID;
			DicTree.search(term, num, bp);
			DicTree.insert(k, num, bp);
			count++;
		}
		delete c;
	}
	inFile.close();
}//�������뵽�ĵ��ﴢ����������¹����ʵ���
//������ѯ
void batch()
{
	ifstream inFile("��ѯ����.txt");
	ofstream outFile("��ѯ���.txt", ios::out);
	if (!inFile)
		return ;
	char* c = new char[10000];
	int n = 0;
	int i = 0, head = 0, j = 1;;
	int Doc[2001] = {0};
	bool result = false;
	while(!inFile.eof())
	{
		for(i = 0;i <= 2000;i++)
			Doc[i] = 0;
		n = 0;
		inFile.getline(c,10000);
		CharString words(c);
		head = 0;
		for(i = 0;i < words.length;i++)
		{
			if(words.data[i] == ' ')
			{
				CharString term = words.subString(head, i - head);
				BTNode* bp = NULL;
				int num = 0;
				int judge = DicTree.search(term, num, bp);
				if(judge == 1)
				{
					DocNode* dp = bp -> key[num] -> l -> head;
					while(dp)
					{
						Doc[dp->DocID]++;
						dp = dp->next;
					}
				}
				head = i + 1;
				n++;
			}
		}
		CharString term = words.subString(head, i - head);
		BTNode* bp = NULL;
		int num = 0;
		int judge = DicTree.search(term, num, bp);
		if(judge == 1)
		{
			DocNode* dp = bp -> key [num] -> l -> head;
			while(dp)
			{
				Doc[dp->DocID]++;
				dp = dp->next;
			}
		}
		n++;
		outFile << endl <<  "��" << j << "����ѯ�����" << endl;
		cout  << endl << "��" << j << "����ѯ�����" << endl;
		for(i = 1;i <= 2000;i++)
		{
			if(Doc[i] > 0)
			{
				cout << i << ' ';
				outFile << i << ' ';
				result = true;
			}
		}
		if(result == false)
		{
			cout  << "��" << j << "����ѯ�޽��";
			outFile << "��" << j << "����ѯ�޽��";
		}
		cout << endl;
		j++;
	}
	delete c;
}
//������ѯ
void onesearch()
{
	//cout << "�ùؼ��ʹ�������" << numcount(DicTree.root) << "����ҳ��" << endl;
	//cout << "���ؼ����ۼƳ�����" << addcount(DicTree.root) << "��" << endl;
	char c[100];
	while(1)
	{
		cin >> c;
		c[strlen(c)] = '\0';
		if(c[0] == '#') break;
		CharString term(c);
		BTNode* bp = NULL;
		int num = 0;
		double time, over;
		time = clock();
		int judge = DicTree.search(term, num, bp);
		if(judge == 0)
		{
			cout << "���޴˴�"<< endl;
			over = clock();
			cout << "��ѯ��ʱ��" << (over - time) / 1000 << "��" << endl;
		}
		else
		{
			DocNode* dp = bp -> key[num] -> l -> head;
			while(dp)
			{
				cout << dp -> DocID << endl;
				dp = dp -> next;
			}
			over = clock();
			cout << "��ѯ��ʱ��" << (over - time) / 1000 << "��" << endl;
		}
	}
}
