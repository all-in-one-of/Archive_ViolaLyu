#ifndef GRAPH_H
#define GRAPH_H

#include<iostream>
using namespace std;

#include<stack>

struct EdgeElem  //边集三元组定义
{
	int v1, v2;
	float weight;
};

/*struct VertexSetElem  //连通顶点集合数定义
{
	int vex;  //顶点序号
	int set;   //顶点所属集合号
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
	//邻接矩阵
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