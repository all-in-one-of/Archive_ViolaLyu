#ifndef CHARSTRING_H
#define CHARSTRING_H

#include <iostream>
typedef char elemType;

class CharString
{
public:
	long length;
	elemType* data;
public:
	CharString(){length = 0; data = 0;};
	CharString(CharString &cs);
	CharString(elemType* e);
	~CharString(){
		if(length != 0) 
			delete []data; 
		data = 0; 
		length = 0;
	};

	long index(CharString &cs);			// 模式匹配函数
	CharString subString(long pos, long len);	// 提取以starting_pos为起点，cslength为长度的CharString
	void concat(CharString &cs);
	void concat(elemType e);
	void renew();			// 重新定义cs
	
	void operator=(CharString &cs);
	void operator=(elemType* e);
	bool operator==(CharString &cs);
	bool operator<(CharString &cs);
	elemType operator[](long i);

	friend std::ostream& operator<<(std::ostream &o, const CharString& cs);
};

#endif