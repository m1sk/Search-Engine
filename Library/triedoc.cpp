#include "triedoc.h"
#include <sstream>
#include <fstream>
#include <algorithm>
#include <stdio.h>
#include <regex>

using namespace Library;
using namespace std::tr1;

triedoc::triedoc(string path,string name)
	: triebuf (), trierootnode (), trienodesarray ()
{
	trienodesarray.push_back(trierootnode);
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

void triedoc::del(string fullPath,char removeType)
{
	if(removeType == 'P'||removeType =='p')
	{
		remove((fullPath+'\\'+docname+'\\'+docname+'.'+docext).c_str());
	}
}

bool is_stop(string word, vector<string> stop)
{
    return (count (stop.begin(), stop.end(), word) != 0);
}

int triedoc::get_node(int index)
{
	for(vector<trienode>::iterator node = trienodesarray.begin();node!=trienodesarray.end();++node)
	{
		if(node->nodeserialnr==index)
			return node - trienodesarray.begin();
	}
	return -1;
}

void triedoc::add_node(string word, long offset)
{
	int index = trierootnode.nodeserialnr;
	int ptr = 0;
    for(string::const_iterator chr = word.begin(); chr != word.end(); ++chr)
    {
		ptr = get_node(index);
        // If we've reached the end of the word, let the node say so
        if((chr + 1) == word.end())
        {
            trienodesarray[ptr].wordend = true;
            break;
        }
        // If the next link doesn't exist, create it
		if(trienodesarray[ptr][*chr] == trienode::NULL_LINK)
        {
            trienodesarray.push_back(trienode(offset,0,*chr, false));
			trienodesarray[ptr].set_link(*chr, trienode::lastserialnr);
        }
        // Update data
        ++(trienodesarray[ptr].nrofoccurences);
        index = trienodesarray[ptr][*chr];
    }
}

void triedoc::indexing(string site)
{
	string stopPath = site + '\\' + docname + '\\' + docname + ".stop";
	ifstream stopfin;
	string next;
	vector<string>stopWords;
	stopfin.open(stopPath);
	do
	{
		getline(stopfin,next);
		stopWords.push_back(next);
		//parse out words and add
		//add_node()
	}
	while(!stopfin.eof());
	stopfin.close();

	string filePath = site + '\\' + docname + '\\' + docname + '.' + docext;
	
	ifstream fin;
	fin.open(filePath);
	regex rgx("[-a-zA-Z0-9]+"); // Represents all sequences of alphanumeric characters and hyphen
	cmatch res;
	vector<string> words;
	int pos;
	do
	{
		pos = (int) fin.tellg();
		getline(fin,next);
		cout << next << endl;
		for(sregex_iterator it(next.begin(), next.end(), rgx), it_end; it != it_end; ++it )
		{
			if((count (stopWords.begin(), stopWords.end(), (*it)[0]) == 0)
				&& ((*it)[0].matched))
			{
				cout << "\t" << (*it)[0] << " at position " << it->position() << endl;
				add_node((*it)[0], it->position());
			}
		}

/*		//parse out words check that it isnt in stop list and add
		regex_search(next.c_str(), res, rgx);
		for(int i = 0; i < res.length(); ++i)
		{
			if(count (stopWords.begin(), stopWords.end(), res[i]) == 0)
			{
				cout <<'\t' << res[i] << " at position " << res.position(i) << endl;
				add_node(res[i], res.position(i));
			}
		}
		cout << endl;*/
	}
	while(!fin.eof());
	fin.close();
}

void triedoc::idx(string fullPath)
{
	indexing(fullPath);
//    get_wordlist(/* The triedoc file*/);
    /* filter wordlist by is_stop */
}

void triedoc::flush(string fullPath)
{

}
triedoc::~triedoc()
{}
