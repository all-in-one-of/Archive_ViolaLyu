#ifndef GRAPH_H
#define GRAPH_H

#include<iostream>
using namespace std;

#include<stack>

struct EdgeElem  //�߼���Ԫ�鶨��
{
	int v1, v2;
	float weight;
};

/*struct VertexSetElem  //��ͨ���㼯��������
{
	int vex;  //�������
	int set;   //�����������Ϻ�
};*/

class graph
{
public:
	graph():vertex(0),edge(0),matrix(0),Edge(0){}
	graph(int v);
	~graph()
	{
		deletetree();
	}
	int vertex;
	int edge;
	//�ڽӾ���
	float **matrix;    
	EdgeElem *Edge;
	void init_vertex(int v);
	void init_edge(int i, int vertex1, int vertex2, float weight);
	void deletetree();
public:
	void input();
	void output();
	void connect();
};

#endif