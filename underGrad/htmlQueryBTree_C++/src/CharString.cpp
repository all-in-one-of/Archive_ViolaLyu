#include"CharString.h"
#include<string>

CharString::CharString(CharString &cs)
{
	length = cs.length;
	data = new elemType[length + 1];
	for(int i = 0; i < length; i++)
		data[i] = cs.data[i];
	data[length] = '\0';
}

CharString::CharString(elemType* e)
{
	length = strlen(e);
	data = new elemType[length];
	for(int i = 0; i < length; i++)
		data[i] = e[i];
}
//模式匹配函数
long CharString::index(CharString &cs)
{
	int j = 0, k = -1, m = cs.length;
	int* next = new int[m];
	next[0] = -1;
    while(j < m-1)
	{
        if(k == -1 || cs[j] == cs[k])	{++j;	++k;	next[j] =k;}
        else  k = next[k];
	}
	int i = -1, n = length;
	j = -1;
	while (i < n && j < m)
	{
		if(j == -1 || data[i] == cs[j])	{++i;	++j;}
		else	j = next[j];
	}
	delete []next;
	if(j >= m)	return(i-m);
    else	return -1;
}
//提取出以pos为起点，len为长度的CharString
CharString CharString::subString(long pos, long len)
{
	CharString cs;
	cs.length = len;
	cs.data = new elemType[cs.length];
	for(int i = 0; i < cs.length; i++)
		cs.data[i] = data[i + pos];
	return cs;
}

void CharString::concat(CharString &cs)
{
	elemType* temp = new elemType[length+cs.length + 1];
	for(int i = 0; i < length; i++)
		temp[i] = data[i];
	for(int i = 0; i < cs.length; i++)
		temp[length+i] = cs.data[i];
	if(length != 0)
		delete []data;
	temp[length + cs.length] = '\0';
	data = temp;
	length += cs.length;
}

void CharString::concat(elemType e)
{
	elemType* temp = new elemType[length+1+1];
	for(int i = 0; i < length; i++)
		temp[i] = data[i];
	temp[length] = e;
	if(length != 0)
		delete []data;
	temp[length+1] = '\0';
	data = temp;
	length++;
}

void CharString::renew()
{
	if(length != 0)
		delete []data;
	data = 0;
	length = 0;
}

void CharString::operator=(CharString &cs)
{
	if(length != 0)
		delete []data;
	length = cs.length;
	data = new elemType[length + 1];
	for(int i = 0; i < length; i++)
		data[i] = cs.data[i];
	data[length] = '\0';
}

void CharString::operator=(elemType* e)
{
	if(length != 0)
		delete []data;
	length = strlen(e);
	data = new elemType[length + 1];
	for(int i = 0; i < length; i++)
		data[i] = e[i];
	data[length] = '\0';
}

bool CharString::operator==(CharString &cs)
{
	if(length == cs.length)
	{
		int i;
		for(i = 0; i < length; i++)
			if(data[i] != cs.data[i])
				break;
		if(i == length)
			return true;
	}
	return false;
}

bool CharString::operator<(CharString &cs)
{
	int shortlen = length < cs.length ? length : cs.length;
	for(int i = 0; i < shortlen; i++)
	{
		if(data[i] < cs.data[i])
			return true;
		else if(data[i] > cs.data[i])
			return false;
	}
	if(length < cs.length)
		return true;
	return false;
}

elemType CharString::operator[](long i)
{
	return data[i];
}

std::ostream& operator<<(std::ostream &o, const CharString& cs)
{
	for(int i = 0; i < cs.length; i++)
		o << cs.data[i];
	return o;
}