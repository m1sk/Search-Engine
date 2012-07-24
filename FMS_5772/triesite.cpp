#include "stdafx.h"
#include "triesite.h"
#include <exception>
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
	if(mounted)
		unmount();
	doclist.clear();
	long err = createDirectory(path);
	if(err == 0)
		throw exception(("Unable to create a search site at " + path
			+ "\nError:" + strerror(errno)).c_str());
}

void triesite::mount(string path,char mode){
	if(mounted)
		unmount();
	sitename = makeFullPath(path);
	// Iterate through all files in path and create triedocs from each
	// then add the created triedocs to the doclist
	list<string> docs = getSubDirectoryNameList(sitename);
	list<string>::iterator iter;
	for(iter = docs.begin(); iter != docs.end(); ++iter){
		doclist.push_back(triedoc(sitename, find_triedoc(sitename, *iter)));
	}
	mounted = true;
}

void triesite::unmount(){
	if(!mounted)
		return;
	doclist.clear();
	sitename = "";
	mounttype = '\0';
	mounted = false;
}

list<triedoc>::iterator triesite::docexists(string compname){
	if(!mounted)
		throw exception("Can't perform queries on non-mounted search site");
	list<triedoc>::iterator iter;
	for(iter = doclist.begin(); iter != doclist.end(); ++iter)
		if(iter->getdocname().compare(compname) == 0){
			return iter;
		}
	return doclist.end();
}

void triesite::docupload(string name,char func) {
	if(!mounted)
		throw exception("Can't perform queries on non-mounted search site");
	if(docexists(name)==doclist.end())
		doclist.push_back(triedoc(sitename,name,func));
	else
		throw exception("Document already exists in search site");
}

string triesite::docdownload(string name,string path = getCurrentPath()) {
	if(!mounted)
		throw exception("Can't perform queries on non-mounted search site");
	path = makeFullPath(path);
	list<triedoc>::iterator doc = docexists(name);
	if(doc != doclist.end())
		doc->getdoc(sitename,path);
	else
		return NULL;
	return path;
}

void triesite::del(char removeType)
{
	if(!mounted)
		throw exception("Can't perform queries on non-mounted search site");
	if(removeType=='P'||removeType=='p')
		removeDirectoryWithSubs(sitename);
	else if(!(removeType=='L'||removeType=='l'))
		return;
	sitename = "";
	doclist.clear();
	mounted = false;
	mounttype = '\0';
}

void triesite::docdel(string name,char type)
{
	if(!mounted)
		throw exception("Can't perform queries on non-mounted search site");
	list<triedoc>::iterator targ = docexists(name);
	if(targ == doclist.end())
		throw exception(("Couldn't delete " + name + " because "
			"there is no document by that name.").c_str());
	else 
	{
		targ->del(sitename,type);
		doclist.erase(targ);
	}
}

void triesite::putstopfl(string stopName)
{
	if(!mounted)
		throw exception("Can't perform queries on non-mounted search site");
	if(getFileSuffix(stopName) !="stop")
		throw exception((stopName + " is not a valid stop file").c_str());
	string stopSrc = makeFullPath(stopName);
	copyFileToDirectory(stopSrc,sitename,true);
	rename(appendPath(sitename,getFileName(stopName)).c_str(),appendPath(sitename,"stop.lst").c_str());
}

void triesite::docidx(string docName)
{
	if(!mounted)
		throw exception("Can't perform queries on non-mounted search site");
	list<triedoc>::iterator targ = docexists(docName);
	if(targ == doclist.end())
		throw exception(("Couldn't index " + docName + " because "
			"there is no document by the name: ").c_str());
	else 
		targ->idx(sitename);
}
list<string> triesite::listdoc(long listtype)
{
	if(!mounted)
		throw exception("Can't perform queries on non-mounted search site");
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
				throw exception("Invald list type parameter in triesite::listdoc");
			}
		}
		else
		{
			switch(listtype)
			{
			case 1:
				break;
			case 0:
				ret.push_back(iter->getdocname());
				break;
			case 2:
				ret.push_back(iter->getdocname());
				break;
			default:
				throw exception("Invald list type parameter in triesite::listdoc");
			}
		}
	}
	return ret;
}
string triesite::expsearch(string docName,string expr)
{
	if(!mounted)
		throw exception("Can't perform queries on non-mounted search site");
	list<triedoc>::iterator targ = docexists(docName);
	if(targ == doclist.end())
		throw exception(("Couldn't search " + docName + " because "
			"there is no document by the name: ").c_str());
	else
		return targ->expsearch(sitename,expr);
}
long triesite::expcount(string docName,string expr)
{
	if(!mounted)
		throw exception("Can't perform queries on non-mounted search site");
	list<triedoc>::iterator targ = docexists(docName);
	if(targ == doclist.end())
		throw exception(("Couldn't search " + docName + " because "
			"there is no document by the name: ").c_str());
	else
		return targ->expcount(sitename,expr);
}
list<string> triesite::doclookup(string exp)
{
	if(!mounted)
		throw exception("Can't perform queries on non-mounted search site");
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