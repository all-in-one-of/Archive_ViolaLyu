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
			//��ʼ���ڽӾ���
			matrix[srcvertex][resvertex] = weight;
			matrix[resvertex][srcvertex] = weight;
			//��ʼ���߼���Ԫ��
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

//����xԪ�����ڼ���&&ѹ��·��
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
	//��ֵ
	double t = 0;    
	set<int> s;
	ofstream output("output_samemovie.txt", ios::out);

	//������Ԫ�鰴Ȩֵ��������
	qsort(Edge, edge, sizeof(EdgeElem), compare);
	cout << " ���ڼ��㹲ͬ�����ĵ�Ӱ��Ŀ"<< endl;
	while(t <=40)
	{
	//��ʼ��
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
		//�ߵ����㲻��ͬһ����
		if (x != y)
		{
			//�ϲ�x��y���ڼ���
			if(rank[x] == rank[y])
			{
				rank[x] = rank[y] + 1;
				parent[y] = x;
			}
			//�߶�С�������ڸ߶ȴ�����
			else if(rank[x] < rank[y])  
				parent[x] = y;
			else
				parent[y] = x;
		}
	}
	//������, ����ͼ����ͨ��֧����
	s.clear();
	for (i = 0; i < vertex; i++)
		s.insert(parent[i]); 
	//��ͨ��֧�ĸ���
	branch = s.size(); 
	output << "��ֵΪ" << t << "��" <<"��ͨ��֧��"<< branch << "��" << endl << endl;
	t += 1;
	}
	output.close();
	output.open("output_ranksimilarity.txt", ios::out);
	t = 0; 
	cout << "���ڼ����������ƶ�" << endl;
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
		//�ߵ����㲻��ͬһ����,�ϲ�������
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
	//������
	s.clear();
	for (i = 0; i < vertex; i++)
		s.insert(parent[i]); 
	//��ͨ��֧�ĸ���
	branch = s.size(); 
	output << "��ֵΪ" << t << "����ͨ��֧��" << branch << "��" << endl << endl;
	t += 0.025;
	}
}