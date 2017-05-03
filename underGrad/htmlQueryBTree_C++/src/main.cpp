#include"CharString.h"
#include"dictionaryBTree.h"
#include"DocLink.h"
#include"hash.h"
#include<iostream>
#include<time.h>

using namespace std;

bool createBTree();
int numcount(BTNode* root);
int addcount(BTNode* root);
void OutputDocLink(DocLink * lp);
void OutputBTree(BTNode* root);
void resetBTree();
void batch();
void onesearch();

void main()
{
	int loc = 0;
	double timetree, timetreeover, timebatch, batchover;
	cout << "��ʼ����B��" << endl;
	timetree = clock();
	createBTree();
	timetreeover = clock();
	cout << "����B����ʱ��" << (timetreeover - timetree) / 1000 << "��" << endl;
	cout << "��ѡ�񵥸���ѯ��ʽ��1ΪB-�����ң�2Ϊ��ϣ����" << endl;
	int a;
	cin >> a;
	if(a == 1)
	{
		cout << "������ؼ��ʣ�����#��ʾ������ѯ" << endl;
		onesearch();
		//cout << "��ѯ��ʱ��" << (timeoneover - timeone) / 1000 << "��" << endl;
	}
	else  if(a == 2)
	{
		cout << "������ؼ��ʣ�����#��ʾ������ѯ" << endl;
		//timehash = clock();
		mapping();
		hashdoc();
		//timehashover = clock();
		//cout << "��ѯ��ʱ��" << (timehashover - timehash) / 1000 << "��" << endl;
	}
	cout << "�������������ѯ" << endl;
	timebatch = clock();
	batch();
	batchover = clock();
	cout << "��ѯ��ʱ��" << (batchover - timebatch) / 1000 << "��" << endl;
	system("pause");
}