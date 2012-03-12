#pragma once
#include<string>
#include<array>
#include"triebuffer.h"
#include"trienode.h"
using namespace std;

class triedoc
{
private:
	string docname;
	trienode* trierootnode;
	triebuffer triebuf;
	array<trienode> trienodesarray;
public:
	triedoc(void);
	triedoc(string,string);
	~triedoc(void);
	void putdoc(string,string,char='c');
	void getdoc(string,string=".");
};

