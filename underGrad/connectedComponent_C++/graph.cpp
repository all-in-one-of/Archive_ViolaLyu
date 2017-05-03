#include"graph.h"

#include<fstream>
#include<stack>
#include<set>

#define INF 1e10

graph::graph(int v)
{
	vertex = v;
	edge = 0;
	matrix = new float*[v];
	for(int i = 0; i < v; i++)
		matrix[i] = new float[v];
}

void graph::deletetree()
{
	for (int i = 0; i < vertex; i++)
		delete matrix[i];
	delete Edge;
	delete matrix;	
}

void graph :: init_vertex(int v)
{
	deletetree();
	vertex = v;
	edge = 0;
	matrix = new float*[v];
	for(int i = 0; i < v; i++)
		matrix[i] = new float[v];
}

void graph::init_edge(int i, int vertex1, int vertex2, float weight)
{
	Edge[i].v1 = vertex1;
	Edge[i].v2 = vertex2;
	Edge[i].weight = weight;
}

void graph::input()
{
	ifstream file("graph_movie.txt", ios::in);
	int vertexnum, edgenum, srcvertex, resvertex;
	float weight;
	file >> vertexnum >> edgenum;
	init_vertex(vertexnum);
	edge = edgenum;
	Edge = new EdgeElem[edgenum];
	for (int i = 0; i < vertexnum; i++)
		for (int j = 0; j < vertexnum; j++)
			matrix[i][j] = INF;
	for (int i = 0; i < edgenum; i++)
		{
			file >> srcvertex >> resvertex >> weight;
			//初始化邻接矩阵
			matrix[srcvertex][resvertex] = weight;
			matrix[resvertex][srcvertex] = weight;
			//初始化边集三元组
			Edge[i].v1 = srcvertex;
			Edge[i].v2 = resvertex;
			Edge[i].weight = weight;
		}
		file.close();
}

int compare(const void *a, const void *b)
{
	if((*(EdgeElem*)a).weight == (*(EdgeElem*)b).weight)
		return (*(EdgeElem*)a).v1 - (*(EdgeElem*)b).v1;
	return (*(EdgeElem*)a).weight - (*(EdgeElem*)b).weight;
}

//查找x元素所在集合&&压缩路径
int find(int x, int parent[])
{
	if(x != parent[x])
		parent[x] = find(parent[x], parent);
	return parent[x];
}

void graph::connect()
{
	int *parent = new int[vertex];
	int *rank = new int[vertex];
	int i, x, y;
	int branch;
	//阈值
	double t = 0;    
	set<int> s;
	ofstream output("output_samemovie.txt", ios::out);

	//将边三元组按权值升序排序
	qsort(Edge, edge, sizeof(EdgeElem), compare);
	cout << " 正在计算共同看过的电影数目"<< endl;
	while(t <=40)
	{
	//初始化
	for(i = 0; i < vertex; i++)
	{
		parent[i] = i;
		rank[i] = 0;
	}

	for(i = 0; i <edge; i++)
	{
		if(Edge[i].weight <= t)
			continue;
		x = find(Edge[i].v1, parent);
		y = find(Edge[i].v2, parent);
		//边的两点不在同一集合
		if (x != y)
		{
			//合并x，y所在集合
			if(rank[x] == rank[y])
			{
				rank[x] = rank[y] + 1;
				parent[y] = x;
			}
			//高度小的连接在高度大树后
			else if(rank[x] < rank[y])  
				parent[x] = y;
			else
				parent[y] = x;
		}
	}
	//输出结果, 计算图的连通分支个数
	s.clear();
	for (i = 0; i < vertex; i++)
		s.insert(parent[i]); 
	//连通分支的个数
	branch = s.size(); 
	output << "阈值为" << t << "的" <<"连通分支有"<< branch << "个" << endl << endl;
	t += 1;
	}
	output.close();
	output.open("output_ranksimilarity.txt", ios::out);
	t = 0; 
	cout << "正在计算评分相似度" << endl;
	while(t <= 1)
	{
	for(i = 0; i < vertex; i++)
	{
		parent[i] = i;
		rank[i] = 0;
	}

	for(i = 0; i < edge; i++)
	{
		if((Edge[i].weight - floor(Edge[i].weight)) <= t)
			continue;
		x = find(Edge[i].v1, parent);
		y = find(Edge[i].v2, parent);
		//边的两点不在同一集合,合并两集合
		if (x != y)
		{
			if(rank[x] == rank[y])
			{
				rank[x] = rank[y] + 1;
				parent[y] = x;
			}
			else if(rank[x] < rank[y])  
				parent[x] = y;
			else
				parent[y] = x;
		}
	}
	//输出结果
	s.clear();
	for (i = 0; i < vertex; i++)
		s.insert(parent[i]); 
	//连通分支的个数
	branch = s.size(); 
	output << "阈值为" << t << "的连通分支有" << branch << "个" << endl << endl;
	t += 0.025;
	}
}