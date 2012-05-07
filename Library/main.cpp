// main.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "triesite.h"
#include "fileutils.h"
#include <iostream>

using namespace std;
using namespace Library;


int _tmain(int argc, _TCHAR* argv[])
{

	/*	cout << "Hello, world" << endl;
/*	triesite site;
	cout<<getCurrentPath()<<endl;
	
	*/
	string filePath = "C:\\Users\\Micha\\Desktop\\tempDest\\";
	triedoc doc(filePath, "file1.txt");
	doc.add_node("hello", 0);
	doc.idx(filePath);
/*	ifstream fin;
	string next;
	fin.open(filePath);
	do
	{
		getline(fin,next);
		cout<<next<<endl;
	}
	while(!fin.eof());
	fin.close();*/
	return 0;
}
