#include "triesite.h"
#include "exceptions.h"
#include <stdio.h>
#include <regex>
#include <sstream>
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
	long err = createDirectory(path);
	if(err == 0)
		throw FileException("Unable to create a search site at " + path);
}

void triesite::mount(string path,char mode){
	sitename = makeFullPath(path);
	// Iterate through all files in path and create triedocs from each
	// then add the created triedocs to the doclist
	list<string> docs = getSubDirectoryNameList(sitename);
	list<string>::iterator iter;

	for(iter = docs.begin(); iter != docs.end(); ++iter)
		doclist.push_back(triedoc(sitename, mount_path(sitename, *iter)));
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
	if(docexists(name)==NULL)
	{
		doclist.push_back(triedoc(sitename,name,func));
	}
	else
		throw SiteException("upload" + name, true);
}

string triesite::docdownload(string name,string path = getCurrentPath()) {
	path = makeFullPath(path);
	triedoc* doc = docexists(name);
	if(doc != NULL)
		doc->getdoc(sitename,path);
	else
		return NULL;
	return path;
}

void triesite::del(char removeType)
{
	if(removeType=='P'||removeType=='p')
		removeDirectoryWithSubs(sitename);
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
		throw SiteException("delete " + name);
	else 
	{
		targ->del(sitename,type);
	//	doclist.remove(*targ); //FIXME PLZ TODO
	}
}

void triesite::putstopfl(string stopName)
{
	if(getFileSuffix(stopName) !="stop")
		throw SystemException(stopName + " is not a valid stop file");
	string stopSrc = makeFullPath(stopName);
	copyFileToDirectory(stopSrc,sitename,true);
	rename((sitename + '\\' + getFileName(stopName)).c_str(), (sitename + "\\stop.lst").c_str());
}

void triesite::docidx(string docName)
{
	triedoc* targ = docexists(docName);
	if(targ == NULL)
		throw SystemException("Couldn't index " + docName + " because "
			"there is no document by the name: ");
	else 
		targ->idx(sitename);
}
list<string> triesite::listdoc(long listtype)
{
	list<string> ret;
	list<triedoc>::iterator iter;
	for(iter = doclist.begin(); iter != doclist.end(); ++iter)
	{
		if(iter->is_indexed(sitename))
		{
			switch(listtype)
			{
			case 0:
				ret.push_back(iter->getdocname() + "**");
				break;
			case 1:
				ret.push_back(iter->getdocname());
				break;
			case 2:
				break;
			default:
				throw SystemException("Invald list type");
			}
		}
		else
		{
			switch(listtype)
			{
			case 1:
				break;
			case 0:
			case 2:
				ret.push_back(iter->getdocname());
				break;
			default:
				throw SystemException("Invald list type");
			}
		}
	}
	return ret;
}
string triesite::expsearch(string docName,string expr)
{
	triedoc* targ = docexists(docName);
	if(targ == NULL)
		throw SiteException("search " + docName);
	else
		return targ->expsearch(sitename,expr);
}
long triesite::expcount(string docName,string expr)
{
	triedoc* targ = docexists(docName);
	if(targ == NULL)
		throw SiteException("search " + docName);
	else
		return targ->expcount(sitename,expr);
}
list<string> triesite::doclookup(string exp)
{
	list<string> ret;
	list<string>::iterator iter;
	list<string> indexed = listdoc(1);
	for(iter = indexed.begin(); iter != indexed.end(); ++iter)
	{
		if(expcount(*iter,exp) > 0) 
			ret.push_back(*iter);
	}
	return ret;
}


triesite::~triesite(){
	unmount();
}

