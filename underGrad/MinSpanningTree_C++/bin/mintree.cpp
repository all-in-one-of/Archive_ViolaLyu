#include"mintree.h"
#include<stack>
#include<fstream>
#include<set>
#include<queue>
#include<cmath>
#define INF 1e10
mintree::mintree(int v)
{
	vertex = v;
	edge = 0;
	matrix = new float*[v];
	for(int i = 0; i < v; i++)
		matrix[i] = new float[v];
}

void mintree::deletetree()
{
	for (int i = 0; i < vertex; i++)
		delete matrix[i];
	delete Edge;
	delete matrix;
}

void mintree::init_vertex(int v)
{
	deletetree();
	vertex = v;
	edge = 0;
	matrix = new float*[v];
	for(int i = 0; i < v; i++)
		matrix[i] = new float[v];
}

void mintree::init_edge(int i, int vertex1, int vertex2, float weight)
{
	Edge[i].v1 = vertex1;
	Edge[i].v2 = vertex2;
	Edge[i].weight = weight;
}

void mintree::input()
{
	ifstream file("graph_movie.txt", ios::in);
	int vertexnum, edgenum, srcvertex, resvertex;
	float weight;

	file >> vertexnum >> edgenum;
	init_vertex(vertexnum);
	edge = edgenum;
	Edge = new EdgeElem[edgenum];
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

void mintree::kruskal()
{
	VertexSetElem* vertexset = new VertexSetElem[vertex];
	mintree m;
	m.Edge = new EdgeElem[vertex - 1];
	set<int> s1, s2;
	int i, j, t1, t2, curEdge, oldset, branch, flag;
	int selEdge = 0;  //��ѡ������
	float temp;
	cout << "��������kruskal�㷨�����Ժ�" << endl;
	//������Ԫ�鰴Ȩֵ��������
	for(i = 0; i < edge-1; i++)
		for(j = i + 1; j < edge; j++)
			if (Edge[i].weight > Edge[j].weight)
			{
				t1 = Edge[i].v1;
				t2 = Edge[i].v2;
				temp = Edge[i].weight;
				init_edge(i, Edge[j].v1, Edge[j].v2, Edge[j].weight);
				init_edge(j, t1, t2, temp);
			}
	//��ʼ�����㼯��
	for(i = 0; i < vertex; i++)
		vertexset[i].set = i+1;
	curEdge = 0;
	 //ѡ���ı�������vertex-1
	while (selEdge < vertex-1 && curEdge < edge) 
	{
		//�ߵ����㲻��ͬһ����
		if (vertexset[Edge[curEdge].v1].set != vertexset[Edge[curEdge].v2].set)
		{
			//ѡ���˱�
			m.init_edge(m.edge, Edge[curEdge].v1, Edge[curEdge].v2, Edge[curEdge].weight);
			//s1�洢��������С�������еķǹ����ڵ�
			s1.insert(m.Edge[m.edge].v1);  
			s1.insert(m.Edge[m.edge].v2);
			m.edge++;
			//�ϲ���������
			oldset = vertexset[Edge[curEdge].v2].set;
			for(i = 0; i < vertex; i++)
				if (vertexset[i].set == oldset)
				{
					vertexset[i].set = vertexset[Edge[curEdge].v1].set;
				}
			selEdge++;
		}
		curEdge++;
	}		
	//����ͼ����ͨ��֧����
	for (i = 0; i < vertex; i++)
	{
		s2.insert(vertexset[i].set);
	}
	branch = s2.size();  //��ͨ��֧�ĸ���

	//������
	ofstream output("Output_kruskal.txt", ios::out);
	queue<int> isolate;   //�����ڵ㼯
	for (i = 0; i < vertex; i++)
		if (s1.count(i) == 0)
			isolate.push(i);
	for (i = 1; i <= branch; i++)
	{
		output<<"��" << i << "����ͨ��֧:" << endl;
		flag = 1;  //��i����ͨ��֧�ǹ����ڵ�
		for (j = 0; j < m.edge; j++)
			if (s2.find(vertexset[m.Edge[j].v1].set) == s2.begin())
			{
				output << m.Edge[j].v1 << "=>" << m.Edge[j].v2 << "  " << m.Edge[j].weight << endl;
				flag = 0;
			}
		if(flag == 1)
		{
			output<<"�����ڵ�"<<isolate.front()<<endl;
			isolate.pop();
		}
		s2.erase(s2.begin());
		output<<endl;
	}
	output << "��ѡ��" << m.edge << "����" << endl;
	delete vertexset;
}