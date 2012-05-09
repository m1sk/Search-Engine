#include "triedoc.h"
#include <sstream>
#include <fstream>
#include <algorithm>
#include <stdio.h>
#include <regex>

using namespace Library;
using namespace std::tr1;

string doc_dir (string site, string source)
{
	string name = getFileName(getFilePrefix(source));
	return site + (*(site.end() - 1) == '\\'? "":"\\") + name + "\\";
}

string doc_path (string site, string source)
{
	string name = getFileName(getFilePrefix(source));
	return doc_dir(site, source) + name;
}

triedoc::triedoc(string site,string source, char mode)
	: triebuf (doc_path(site,source) + ".trie"),
	trierootnode (), trienodesarray ()
{
	trienodesarray.push_back(trierootnode);
	if (source != "") {
		putdoc(site, source, mode);
	}
	else {
		docname = "";
		docext = "";
	}
}

triedoc::triedoc(const triedoc& other)
	: triebuf (other.triebuf),
	trierootnode (other.trierootnode), trienodesarray (other.trienodesarray),
	docname(other.docname), docext(other.docext)
{}

void triedoc::putdoc(string site,string src,char mode){
	string dest = doc_dir(site,src);
	string fullsrc = makeFullPath(src);
	if(createDirectory(dest) != 0) // File doesn't exist
	{
		transferFileToDirectory(mode,fullsrc,dest);
		list<string> lst = getFileNameList(getFilePath(fullsrc));
		string stopfilename = getFilePrefix(getFileName(fullsrc)) + ".stop";
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
	else
		throw exception(("Was unable to add document " + src + " to the search site." + site
		+ "\nDoes it already exist there?").c_str());
	docname = getFilePrefix(getFileName(src));
	docext  = getFileSuffix(getFileName(src));
}

void triedoc::getdoc(string site,string dest){
	stringstream dests;
	dests << dest << "\\" << docname;
	stringstream sites;
	sites << site << "\\" << docname;
	if(createDirectory(dests.str())==0)
		throw exception(("Failed to create directory " + dests.str()).c_str());
	list<string> files = getFileNameList(sites.str());
	sites << "\\";
	for(list<string>::iterator itr = files.begin();itr != files.end(); itr++)
		copyFileToDirectory(sites.str() + string(*itr), dests.str(), true);
}

void triedoc::del(string site,char type)
{
	if(type == 'P' || type =='p')
	{
		removeDirectoryWithSubs((site+'\\'+docname).c_str());
	}
	else if(type == 'L' || type =='l')
	{
		if(remove((doc_path(site,docname) + ".trie").c_str()))
		{
			if(errno!=ENOENT)
			{
				throw exception(("Error while logically deleting " + site
					+ ". Error: " + strerror(errno)).c_str());
			}
		}
	}
	triebuf = triebuffer("");
	docname = "";
	docext="";
	trienodesarray = vector<trienode>();
	trierootnode = trienode();

}

bool is_stop(string word, vector<string> stop)
{
    return (count (stop.begin(), stop.end(), word) != 0);
}

void triedoc::idx(string site)
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
	}while(!stopfin.eof() && stopfin.good());
	if(!stopfin.eof())
		throw exception(
			("Error reading the contents of the file " + stopPath).c_str());
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
		// Debugging
		//cerr << next << endl;
		for(sregex_iterator it(next.begin(), next.end(), rgx), it_end; it != it_end; ++it )
		{
			if((count (stopWords.begin(), stopWords.end(), (*it)[0]) == 0)
				&& ((*it)[0].matched))
			{
				// Debugging
				//cerr << "\t" << (*it)[0] << " at position " << it->position() << endl;
				add_node((*it)[0], it->position());
			}
		}
	}while(!fin.eof() && fin.good());
	if(!fin.eof())
		throw exception(
			("Error reading the contents of the file " + filePath).c_str());
	fin.close();
// Debugging
//	cerr<<"Node Array Size" << trienodesarray.size();
}

bool comp(trienode a, trienode b)
{
	return a.nodeserialnr < b.nodeserialnr;
}

void triedoc::flush(string site)
{
	triebuf.open_file();
	sort(trienodesarray.begin(), trienodesarray.end(), comp);
	vector<trienode>::const_iterator i = trienodesarray.begin();
	do
	{
		for(int j = 0; (j < 10) && (i < trienodesarray.end()); ++j, ++i)
			triebuf.buffer[j] = *i;
		triebuf.write();
	}while(i < trienodesarray.end());
	triebuf.close_file();
// Debugging
//	cerr << "Wrote " << triebuf.file_size() << " trienodes to the file " << triebuf.filePath << endl;
}

void triedoc::printNodes()
{
	for(vector<trienode>::const_iterator i = trienodesarray.begin();i<trienodesarray.end();i++)
	{
		i->print_node();
	}
}

void triedoc::printWords()
{
	printWords(trierootnode.nodeserialnr, "");
}

void triedoc::printWords(int idx, string str)
{
	int node = get_node(idx);
	if (idx != trierootnode.nodeserialnr)
		str += trienodesarray[node].letter;
	for(int i = 0; i < trienode::LINKS_LENGTH; ++i)
	{
		if(trienodesarray[node].links[i] != trienode::NULL_LINK)
		{
			printWords(trienodesarray[node].links[i], str);
		}
	}
// Debugging
//	if(trienodesarray[node].wordend)
//	{
//		cout << str << endl;
//	}
}


int triedoc::get_node(int serial)
{
	for(vector<trienode>::iterator node = trienodesarray.begin();node!=trienodesarray.end();++node)
	{
		if(node->nodeserialnr==serial)
			return node - trienodesarray.begin();
	}
	return -1;
}

void triedoc::add_node(string word, long offset)
{
	int index = trierootnode.nodeserialnr;
	int ptr = get_node(index);
    for(string::const_iterator chr = word.begin(); chr != word.end(); ++chr)
    {
        // If the next link doesn't exist, create it
		if(trienodesarray[ptr][*chr] == trienode::NULL_LINK)
        {
            trienodesarray.push_back(trienode(offset,0,*chr, false));
			trienodesarray[ptr].set_link(*chr, trienode::lastserialnr);
        }
        // Update data
        ++(trienodesarray[ptr].nrofoccurences);
        index = trienodesarray[ptr][*chr];
		ptr = get_node(index);
    }
	trienodesarray[ptr].wordend = true;
}

