#ifndef DOCLINK_H
#define DOCLINK_H

//储存词出现的文档ID和次数;主关键词为次数，升序;次关键词为文档ID，降序;
#include"CharString.h"

class DocNode
{
public:
	int times;
	int DocID;
	DocNode* next;

	DocNode():DocID(0), times(0), next(NULL){};
};

class DocLink
{
public:
	int termID;
	DocNode* head;

	DocLink(): head(NULL), termID(0){};
	~DocLink();

	void init();
	bool search(int DocID, DocNode * &p);
	void insert(int DocID);
	void edit(int times, DocNode* p);
};

#endif