#include "triesite.h"
#include <exception>
#include <stdio.h>
using namespace Library;

triesite::triesite(string path, char func, char mode) {
	doclist = list<triedoc>();
	if(path.compare("")!=0){
		sitename = makeFullPath(path);
		mounted = true;
		mounttype = mode;
		if(func == 'C' || func == 'c')
			create(sitename);
		else if(func == 'M' || func == 'm')
			mount (sitename, mode);
	}
	else {
		sitename = "";
		doclist.clear();
		mounted = false;
		mounttype = '\0';
	}
}

void triesite::create(string path){
	doclist.clear();
	int err = createDirectory(path);
	if(err == 0){
		throw exception(("Unable to create a search site at " + path
			+ "\nError:" + strerror(errno)).c_str());
	}
}

void triesite::mount(string path,char mode){
	// Iterate through all files in path and create triedocs from each
	// then add the created triedocs to the doclist
	list<string> docs = getSubDirectoryNameList(sitename);
	list<string>::iterator iter;
	for(iter = docs.begin(); iter != docs.end(); ++iter){
		doclist.push_back(triedoc(sitename, find_triedoc(sitename, *iter)));
	}
}

void triesite::unmount(){
	doclist.clear();
	sitename = "";
	mounttype = '\0';
	mounted = false;
}

triedoc* triesite::docexists(string compname){
	list<triedoc>::iterator iter;
	for(iter = doclist.begin(); iter != doclist.end(); ++iter)
		if(iter->getdocname().compare(compname) == 0){
			return &(*iter);
		}

		return NULL;
}

void triesite::docupload(string name,char func) {
	if(docexists(name)==NULL){
		doclist.push_back(triedoc(sitename,name,func));
	}
	else {
		throw exception("Document already exists in search site");
	}

}

string triesite::docdownload(string name,string path = getCurrentPath()) {
	path = makeFullPath(path);
	triedoc* doc = docexists(name);
	if(doc != NULL){
		doc->getdoc(sitename,path);
	}
	else {
		return NULL;
	}
	return path;
}
void triesite::del(char removeType)
{
	if(removeType=='P'||removeType=='p')
	{
		removeDirectoryWithSubs(sitename);
	}
	else if(removeType=='L'||removeType=='l')
	{}
	else
	{return;}
	sitename = "";
	doclist.clear();
	mounted = false;
	mounttype = '\0';
}
void triesite::docdel(string name,char type)
{
	triedoc* targ = docexists(name);
	if(targ == NULL)
	{
		throw exception(("Couldn't delete " + name + " because "
			"there is no document by that name.").c_str());
	}
	else 
	{
		targ->del(sitename,type);
		doclist.remove(*targ);
	}
}
void triesite::putstopfl(string stopName)
{
	if(getFileSuffix(stopName)!="stop")
	{
		throw exception((stopName + " is not a valid stop file").c_str());
	}
	string stopSrc = makeFullPath(stopName);
	copyFileToDirectory(stopSrc,sitename,true);
	rename(appendPath(sitename,getFileName(stopName)).c_str(),appendPath(sitename,"stop.lst").c_str());
}
void triesite::docidx(string docName)
{
	triedoc* targ = docexists(docName);
	if(targ == NULL)
	{
		throw exception(("Couldn't index " + docName + " because "
			"there is no document by the name: ").c_str());
	}
	else 
	{
		targ->idx(sitename);
	}
}
triesite::~triesite(){
	unmount();
}
