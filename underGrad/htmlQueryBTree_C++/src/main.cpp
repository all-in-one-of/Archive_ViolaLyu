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
	cout << "开始创建B树" << endl;
	timetree = clock();
	createBTree();
	timetreeover = clock();
	cout << "创建B树用时：" << (timetreeover - timetree) / 1000 << "秒" << endl;
	cout << "请选择单个查询方式，1为B-树查找，2为哈希查找" << endl;
	int a;
	cin >> a;
	if(a == 1)
	{
		cout << "请输入关键词，输入#表示结束查询" << endl;
		onesearch();
		//cout << "查询用时：" << (timeoneover - timeone) / 1000 << "秒" << endl;
	}
	else  if(a == 2)
	{
		cout << "请输入关键词，输入#表示结束查询" << endl;
		//timehash = clock();
		mapping();
		hashdoc();
		//timehashover = clock();
		//cout << "查询用时：" << (timehashover - timehash) / 1000 << "秒" << endl;
	}
	cout << "下面进行批量查询" << endl;
	timebatch = clock();
	batch();
	batchover = clock();
	cout << "查询用时：" << (batchover - timebatch) / 1000 << "秒" << endl;
	system("pause");
}