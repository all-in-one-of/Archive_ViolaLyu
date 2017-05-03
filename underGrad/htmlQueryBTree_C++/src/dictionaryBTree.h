#ifndef DICTIONARYBTREE_H
#define DICTIONARYBTREE_H

//´Êµä:ËÄ²æB-Ê÷
#include"DocLink.h"

class Keyword
{
public:
	CharString term;
	int DF;
	int occur;
	DocLink* l;
	int termID;

	Keyword():DF(0), occur(0), l(NULL), termID(0){};
	~Keyword(){delete l;};
};

class BTNode
{
public:
	int n;
	Keyword* key[3];
	BTNode* child[4];
	
	BTNode(): n(0){
		for(int i = 0;i <= 3;i++)
			child[i] = NULL;
		for(int i = 0;i < 3;i++)
			key[i] = NULL;
	};
	~BTNode(){
		for(int i = 0;i <= 3;i++)
			delete child[i];
		for(int i = 0;i < 3;i++)
			delete key[i];
	};
};

class BTree
{
public:
	BTNode* root;

	BTree(){root = new BTNode;};

	void init();
	bool search(CharString term,int &num, BTNode* &p);
	void insert(Keyword* k, int num, BTNode* &p);
	void edit(BTNode* &p, int num, int Doc_ID);
	void deletetree(BTNode* p);
};

#endif