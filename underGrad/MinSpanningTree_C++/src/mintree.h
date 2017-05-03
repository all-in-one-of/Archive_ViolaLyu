#ifndef MINTREE_H
#define MINTREE_H

#include<iostream>
using namespace std;

struct EdgeElem  //�߼���Ԫ�鶨��
{
	int v1, v2;
	float weight;
};

struct VertexSetElem  //��ͨ���㼯��������
{
	int vex;  //�������
	int set;   //�����������Ϻ�
};

class mintree
{
public:
	mintree():vertex(0),edge(0),matrix(0),Edge(0){}
	mintree(int v);
	~mintree()
	{
		deletetree();
	}
	int vertex;
	int edge;
	float **matrix;    //�ڽӾ���
	EdgeElem *Edge;
	void init_vertex(int v);
	void init_edge(int i, int vertex1, int vertex2, float weight);
	void deletetree();
public:
	void input();
	void output();
	void kruskal();
	void zhuliu();      //��С�������������㷨
};

#endif