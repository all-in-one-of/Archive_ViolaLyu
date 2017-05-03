#include"dictionaryBTree.h"
//BTree Dictree;
void BTree::init()
{
	root = new BTNode;
}
//查找时把所有的饱和结点分开
bool BTree::search(CharString term,  int &num, BTNode* &p)
{
	BTNode* q, * temp;
	int success = 0;
	int i = 0, j = 0, prei = 0;
	p = root;
	if(!root)
		return false;
	if(root->n == 3)//根节点饱和，则分裂根节点
	{
		root = new BTNode;
		q = new BTNode;
		root -> n = 1;
		q -> n = 1;
		p -> n = 1;
		root -> key[0] = p -> key[1];
		p -> key[1] = NULL;
		q -> key[0] = p -> key[2];
		p -> key[2] = NULL;
		root -> child[0] = p;
		root -> child[1] = q;
		q -> child[0] = p -> child[2];
		p -> child[2] = NULL;
		q -> child[1] = p -> child[3];
		p -> child[3] = NULL;
	}
	p = root;
	q = p;
	while(p)
	{
		for(i = 0; i < p -> n;i++)
		{
			if(term == p->key[i]->term)
			{
				success = 1;
				break;
			}
			else if(term < p->key[i]->term)
				break;
		}
		if(p -> n == 3)
		{
			temp = new BTNode;
			q -> n ++;
			for(j = q -> n; j > prei + 1; j--)
				q -> child[j] = q -> child[j - 1];
			q -> child[j] = temp;
			for(j = q -> n - 1; j > prei; j--)
				q -> key[j] = q -> key[j - 1];
			q -> key[j] = p -> key[1];
			p -> key[1] = NULL;
			temp -> n = 1;
			p -> n = 1;
			temp -> key[0] = p -> key[2];
			p -> key[2] = NULL;
			temp -> child[0] = p -> child[2];
			p -> child[2] = NULL;
			temp -> child[1] = p -> child[3];
			p -> child[3] = NULL;
			if(success == 1)
			{
				p = q;
				num = prei;
				return true;
			}
			else if(i == 2)
			{
				p = temp;
				i = 0;
			}
			else if(i == 3)
			{
				p = temp;
				i = 1;
			}
		}
		if(success == 1)
		{
			num = i;
			return true;
		}
		prei = i;
		q = p;
		p = p -> child[i];
	}
	p = q;
	num = i;
	return false;
}

void BTree::insert(Keyword* k,  int num, BTNode* &p)
{
	int i = p -> n;
	for(; i > num; i--)
	{
		p -> key[i] = p -> key[i - 1];
		p ->child[i] = p ->child[i - 1];
	}
	p -> key[num] = k;
	p -> child[num] = NULL;
	p -> n++;

}

void BTree::edit(BTNode* &p, int num, int Doc_ID)
{
	DocNode* d = NULL;
	int judge = p -> key[num] -> l -> search(Doc_ID, d);
	if(judge == 1)
	{
		p -> key[num] -> l -> edit(1, d);
		p -> key[num] -> occur++;
	}
	else
	{
		p -> key[num] -> l -> insert(Doc_ID);
		p -> key[num] -> DF++;
		p -> key[num] -> occur++;
	}
}
