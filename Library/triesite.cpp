#include "triesite.h"
#include <exception>

using namespace Library;

triesite::triesite(string path, char func, char mode) {
	doclist = list<triedoc>();
	if(path.compare("")!=0){
		sitename = makeFullPath(path);
		if(func == 'C' || func == 'c'){
			create(sitename);
		}
		else if(func == 'M' || func == 'm'){
			mount(sitename, mode);
		}
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
		throw new exception("Unable to create a search site");
	}
}

void triesite::mount(string path,char mode){
	//iterate through all files in path and create triedocs from each when 
	// then add the triedocs to doclist
	sitename = getFileName(path);
	list<string> docs = getSubDirectoryNameList(path);
	list<string>::iterator iter;
	triedoc* tmp;
	for(iter = docs.begin(); iter != docs.end(); ++iter){
		tmp = new triedoc(path, appendPath(path, *iter));
		doclist.push_back(*tmp);
	}
	mounttype = mode;
	mounted = true;
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
		triedoc doc = triedoc();
		doc.putdoc(sitename,name,func);
		doclist.push_back(doc);
	}
	else {
		throw new exception("Document already exists in search site");
	}

}

string triesite::docdownload(string name,string path = getCurrentPath()) {
	path = makeFullPath(path);
	triedoc* doc = docexists(name);
	if(doc != NULL){
		doc->getdoc(sitename,path);
	}
	else {
		throw new exception("Document doesn't exist in search site");
	}
	return path;
}

triesite::~triesite(){
	unmount();
}
