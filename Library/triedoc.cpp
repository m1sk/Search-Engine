#include "triedoc.h"
#include <sstream>
#include <algorithm>

using namespace Library;

triedoc::triedoc(string path,string name){
	if (name != "") {
		putdoc(path, name);
	}
	else {
		triebuf =  new triebuffer();
		docname = "";
		trierootnode = NULL;
		trienodesarray = array<trienode, 0U>();
	}
}

void triedoc::putdoc(string site,string src,char mode){
	stringstream ss;
	ss << site << "\\" << getFilePrefix(getFileName(src));
	string dest = ss.str();
	string fullsrc = makeFullPath(src);
	if(createDirectory(dest) == 0)
		throw new exception("Was unable to add document to search site.\
							Does it already exist?");
	transferFileToDirectory(mode,fullsrc,dest);
	list<string> lst = getFileNameList(getFilePath(fullsrc));
	string stopfilename = getFilePrefix(src) + ".stop";
	string stopfilepath = getFilePath(fullsrc) + stopfilename;
	if(find(lst.begin(), lst.end(), stopfilename) != lst.end()) {
		transferFileToDirectory(mode, stopfilepath, dest, false);
	}
	else {
		//check for a stop list, creating an empty one if it doesn't exist
		//if(fileExists(site<<"\\stop.lst"))
		//else
		//{
		//
		//}
	}
	docname = getFilePrefix(src);
	triebuf = new triebuffer();
	trierootnode = NULL;
	trienodesarray = array<trienode, 0U>();
}
void triedoc::getdoc(string site,string dest){
	stringstream dests;
	dests << dest << "\\" << docname;
	stringstream sites;
	sites << site << "\\" << docname;
	createDirectory(dests.str());
	list<string> files = getFileNameList(dests.str());
	dests << "\\" << docname << "\\";
	for(list<string>::iterator itr = files.begin();itr != files.end(); itr++)
	{
		copyFileToDirectory(sites.str() + string(*itr),
			dests.str() + string(*itr), true);
	}	
}
triedoc::~triedoc()
{
	delete triebuf;
}
