#ifndef MINTREE_H
#define MINTREE_H

#include<iostream>
using namespace std;

struct EdgeElem  //边集三元组定义
{
	int v1, v2;
	float weight;
};

struct VertexSetElem  //连通顶点集合数定义
{
	int vex;  //顶点序号
	int set;   //顶点所属集合号
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
	float **matrix;    //邻接矩阵
	EdgeElem *Edge;
	void init_vertex(int v);
	void init_edge(int i, int vertex1, int vertex2, float weight);
	void deletetree();
public:
	void input();
	void output();
	void kruskal();
	void zhuliu();      //最小生成树的朱刘算法
};

#endif