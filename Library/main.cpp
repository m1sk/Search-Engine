// main.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "triesite.h"
#include "fileutils.h"
#include <iostream>

using namespace std;
using namespace Library;

void print(trienode n)
{
	cout << n.nodeserialnr << " " << n.letter << " " << endl;
}
void start()
{
	string path = "temp0";
	triesite site(path);
	site.docupload("temp\\a.txt");
	site.docupload("temp\\b.txt");
	site.docupload("temp\\c.txt");
	site.unmount();
	site.mount(path);
	
	if(site.docexists("c")!=NULL)
		cout<<"doc \"c.txt\" exists"<<endl;

	site.docidx("a");
	site.docexists("a")->printNodes();
}
int _tmain(int argc, _TCHAR* argv[])
{
	try
	{
		start();
	}
	catch(exception e)
	{
		cerr << e.what() << endl;
	}
	system("pause");
	removeDirectoryWithSubs(makeFullPath("temp0"));

	/*
	triesite site;
	cout<<getCurrentPath()<<endl;
	
	/**/
	/*
	string filePath = "C:\\Users\\Micha\D\esktop\\tempDest\\";
	triedoc doc(filePath, "file1.txt");
	doc.idx(filePath);

	doc.printWords();
	doc.flush(filePath);
	//delete &doc;
	triebuffer buff(filePath+"file1\\file1.trie");
	buff.open_file(true);
	cout<<buff.file_size()<<endl;
	buff.close_file();
//	cout<< buff.buffer[0].letter<<endl;
	/**/
	return 0;

}

