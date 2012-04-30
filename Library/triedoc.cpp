#include "triedoc.h"
#include <sstream>
#include <fstream>
#include <algorithm>
#include <stdio.h>
// Include Boost libraries http://www.boost.org
#include "..\boost_1_47"

using namespace Library;
// Include Boost lambda expressions
using namespace Boost::lambda;

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

bool is_stop(string word, vector<string> stop)
{
    return (count (stop.begin(), stop.end(), word) != 0);
}

trienode get_node(int index)
{
    // _1 defines a lambda expression.
    // Here, we define an anonymous function checking whether the node's serial
    // number is equal to the index
    return find_if(trienodesarray.begin(), trienodesarray.end(), _1.nodeserialnr
                                                                    == index);
}

void gen_trie(vector<tuple<string, long, long> > doc)
{
    int index = trierootnode.nodeserialnr;
    // tuple is a Boost class. Here a tuple of string, long and long
    for(vector<tuple<string, long, long> >::const_iterator word = doc.begin();
        word != doc.end(); ++word)
    {
        // tuple.get<N>() returns a reference to the Nth (0-indexed) element of
        // the tuple
        string str = word.get<0>();
        for(string::const_iterator chr = str.begin(); chr != str.end(); ++chr)
        {
            // If we've reached the end of the word, let the node say so
            if((chr + 1) == str.end())
            {
                get_node(index)->wordend = true;
                break;
            }

            // If the next link doesn't exist, create it
            if((*get_node(index))[*chr] == NULL_LINK)
            {
                trienodesarray.push_back(trienode(0,0,*chr, false));
                ((*get_node(index))[*chr] = trienode.lastserialnr);
            }
            // Update data
            get_node(index)->firstoffset = word.get<1>();
            get_node(index)->nrofoccurences = word.get<2>();
            index = (*get_node(index))[*chr];
        }
    }
}

// tuple is a Boost class. Here a tuple of string, long and long
vector<tuple<string, long, long> > get_wordlist(fstream file);

void triedoc::idx(string fullPath)
{
    get_wordlist(/* The triedoc file*/)
    /* filter wordlist by is_stop */
    gen_trie(/* wordlist */)
}

void triedoc::flush(string fullPath)
{

}
triedoc::~triedoc()
{}
