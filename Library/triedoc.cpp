#include "triedoc.h"
#include <sstream>
#include <fstream>
#include <algorithm>
#include <stdio.h>
using namespace Library;

triedoc::triedoc(string path,string name)
	: triebuf (), trierootnode (), trienodesarray ()
{
	if (name != "") {
		putdoc(path, name);
	}
	else {
		docname = "";
		docext = "";
	}
}

void triedoc::putdoc(string site,string src,char mode){
	stringstream ss;
	ss << site << "\\" << getFilePrefix(getFileName(src));
	string dest = ss.str();
	string fullsrc = makeFullPath(src);
	if(createDirectory(dest) != 0) // File doesn't exist
	{
		transferFileToDirectory(mode,fullsrc,dest);
		list<string> lst = getFileNameList(getFilePath(fullsrc));
		string stopfilename = getFilePrefix(getFileName(src)) + ".stop";
		string stopfilepath = getFilePath(fullsrc)+"\\" + stopfilename;
		if(find(lst.begin(), lst.end(), stopfilename) != lst.end()) {
			transferFileToDirectory(mode, stopfilepath, dest, false);
		}
		else {
			ofstream file;
			file.open(dest + "\\" +stopfilename);
			file.close();
		}
	}
	docname = getFilePrefix(getFileName(src));
	docext  = getFileSuffix(getFileName(src));
}
void triedoc::getdoc(string site,string dest){
	stringstream dests;
	dests << dest << "\\" << docname;
	stringstream sites;
	sites << site << "\\" << docname;
	if(	createDirectory(dests.str())==0)cout<<"failed to create directory"<<endl;
	cout<<dests.str()<<endl
		;
	list<string> files = getFileNameList(sites.str());
	sites << "\\";
	for(list<string>::iterator itr = files.begin();itr != files.end(); itr++)
	{
		copyFileToDirectory(sites.str() + string(*itr),
			dests.str(), true);
	}	
}
void triedoc::del(string fullPath,char removeType = 'l')
{
	if(removeType == 'P'||removeType =='p')
	{
		remove(fullPath+'\\'+docname+'\\'+docname+'.'+docext);
	}
}
void triedoc::idx(string fullPath)
{}
void triedoc::flush(string fullPath)
{}

triedoc::~triedoc()
{}
