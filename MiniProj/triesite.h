#pragma once
#include<string>
#include<list>
#include"triedoc.h"
using namespace std;

class triesite
{
private:
	string sitename;
	list<string> doclist;
	bool mounted;
	char mounttype;
public:
	triesite(void);
	triesite(string,char,char);
	void create(string);
	void mount(string,char='q');
	void unmount();
	triedoc* docexists(string);
	void docupload(string,char);
	string docdownload(string,string=".");
	~triesite(void);
};
