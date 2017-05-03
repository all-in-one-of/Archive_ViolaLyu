#include"DocLink.h"

DocLink::~DocLink()
{
	DocNode *after = head, *p = head;
	while(p)
	{
		after = p->next;
		delete p;
		p = after;
	}
	head = NULL;
}

void DocLink::init()
{
	termID = 0;
	head = NULL;
}

bool DocLink::search(int DocID, DocNode* &p)
{
	p = head;
	while(p)
	{
		if(p -> DocID == DocID)
			return true;
		p = p -> next;
	}
	return false;
}

void DocLink::insert(int DocID)
{
	DocNode* p = head, *pre = head, *temp;
	if(!head)
	{
		head = new DocNode;
		head->DocID = DocID;
		head->times = 1;
		head->next = NULL;
	}
	else
	{
		while(p)
		{
			if(p->DocID < DocID || p->times > 1)
				break;
			else
			{
				pre = p;
				p = p->next;
			}
		}
		temp = new DocNode;
		temp->DocID = DocID;
		temp->times = 1;
		temp->next = p;
		if(p == head)
			head = temp;
		else
			pre->next = temp;
	}
}

void DocLink::edit(int times, DocNode* p)
{
	DocNode* temp = head, *pre;
	p->times += times;
	if(p == head && p->next == NULL)
		return;
	else
	{
		if(head == p)
		{
			head = p->next;
			temp = p->next;
		}
		else
		{
			while(temp->next != p)
				temp = temp->next;
			temp->next = p->next;
			pre = temp;
		}
		while(temp)
		{
			if((temp->DocID < p->DocID && temp->times == p->times)|| temp->times > p->times)
				break;
			else
			{
				pre = temp;
				temp = temp->next;
			}
		}
		p->next = temp;
		if(temp == head)
			head = p;
		else
			pre->next = p;
	}
}
