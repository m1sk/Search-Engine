#include "triedoc.h"
#include <algorithm>

triedoc::triedoc(string path = "C:\\",string name = "Untitled"){
	putdoc(path, name);
}
void triedoc::putdoc(string site,string src,char mode = 'c'){
	string dest = site + "\\" + getFilePrefix(getFileName(src));
	if(createDirectory(dest) == 0)
		throw new exception("Was unable to add document to search site.\
							Does it already exist?");
	transferFileToDirectory(mode,src,dest);
	list<string> lst = getFileNameList(getFilePath(src));
	string stopfilename = getFilePrefix(src) + ".stop";
	string stopfilepath = getFilePath(src) + stopfilename;
	if(find(lst.begin(), lst.end(), stopfilename) != lst.end()) {
		transferFileToDirectory(mode, stopfilepath, dest, false);
	}
	else {
		//
	}
	docname = getFilePath(getFileName(src));
	triebuf = triebuffer();
}
void triedoc::getdoc(string site,string dest = getCurrentPath()){
	copyFileToDirectory(site + "\\" + docname, dest, true);
}
