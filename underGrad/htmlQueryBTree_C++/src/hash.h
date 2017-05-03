#ifndef HASH_H
#define HASH_H

#pragma once

#include "CharString.h"
#include "dictionaryBTree.h"
#include <fstream>
#include <iostream>
using namespace std;

#define HashSize 130087

class htmlhash
{
public:
	Keyword** map;
	int num;
	htmlhash():map(NULL), num(0){};
	~htmlhash(){
		if(map) 
			delete[]map;
		map = NULL;
	};
};

int hashfunc(CharString &term);
int reduceconflict(int loc);
bool hashsearch(CharString term, int& loc);
bool mapping();
void hashdoc();

#endif