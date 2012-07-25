// main.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "triesite.h"
#include "fileutils.h"
#include <regex>
#include <iostream>

using namespace std;
using namespace Library;

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
	site.docidx("b");
//	site.docexists("a")->printNodes();
	cout << "Search a: " << site.expsearch("a", "*e*") << endl;
	cout << "Search b: " << site.expcount("b","*") << endl;
	for(int i = 0; i<=2; ++i)
	{
		cout << "Listdoc of type " << i << endl;
		list<string> res = site.listdoc(i); 
		for(list<string>::const_iterator it = res.begin(); it != res.end();it ++)
			cout << *it << endl;
		cout << "-------------------" << endl << endl;
	}
}

long _tmain(long argc, _TCHAR* argv[])
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
	
	/*
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
	/*
	string filePath = "C:\\Users\\Micha\\Desktop\\tempDest\\";
	vector<string> expr;
	//expr.push_back("((((One Three Seven Nine) & (elen sila)) | ((lu*) & (annoy))) | (bla fe*))");
	//expr.push_back("(One)");
	expr.push_back("R*ga");
	expr.push_back("shad*");
	expr.push_back("*");
	triedoc doc(filePath, "file1.txt");
	cout << "Is indexed ? "<<doc.is_indexed(filePath) ;
	doc.idx(filePath);
	cout << "Is indexed ? "<<doc.is_indexed(filePath) ;
	for(vector<string>::iterator i = expr.begin(); i != expr.end(); ++i)
	{
		cout << "Expression: " << *i << endl;
		cout << "Expsearch invoked" << endl
			<< "Line including first occurence of searchexp: "  << doc.expsearch(filePath, *i) << endl;;
		cout << endl;
		cout << "Expcount invoked" << endl
			<< "Number of occurences is: " << doc.expcount (filePath, *i) << endl << endl << endl << endl;
	}
	/*
	string input = "((((foo bar va) & (elen sila)) | ((lumenn) & (annoy))) | (bla))";
	vector<vector<string> > atoms = get_atoms(input);
	cout << "Input: " << input << endl;
	long count = 0;
	for(vector<vector<string> >::const_iterator i = atoms.begin(); i != atoms.end(); ++i)
	{
		cout << "Atom #" << count++ << endl;
		for(vector<string>::const_iterator j = i->begin(); j != i->end(); ++j)
		{
			cout << '\t' << *j << endl;
		}
		cout << endl;
	}
	cout << replace_atoms(input) << endl;
	cout << shunting_yard(replace_atoms(input)) << endl;
	/**/
	return 0;
}