#include "triedoc.h"
#include "searchutils.h"
#include <sstream>
#include <fstream>
#include <algorithm>
#include <stdio.h>
#include <regex>
#include <exception>

class DocExistsException: exception
{
public:
	DocExistsException()
		: exception() {}
	DocExistsException(string s)
		: exception(s.c_str()) {}
	DocExistsException(const char* const & s)
		: exception(s) {}
};

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
	trierootnode (), trienodesarray (),lastserialnr(0)
{
	trienodesarray.push_back(trierootnode);
	if (source != "") {
		try {
		putdoc(site, source, mode);
		} 
		catch (DocExistsException e)
		{

		}
	}
	else {
		docname = "";
		docext = "";
		lastserialnr = 0;
	}
}

triedoc::triedoc(const triedoc& other)
	: triebuf (other.triebuf),
	trierootnode (other.trierootnode), trienodesarray (other.trienodesarray),
	docname(other.docname), docext(other.docext), lastserialnr(other.lastserialnr)
{}

void triedoc::putdoc(string site,string src,char mode){
	string dest = doc_dir(site,src);
	string fullsrc = makeFullPath(src);
	docname = getFilePrefix(getFileName(src));
	docext  = getFileSuffix(getFileName(src));

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
	else if(GetLastError() == ERROR_PATH_NOT_FOUND) // Directory does not exist
	{
		throw exception(("Was unable to add document " + src + " since the source directory does not exist").c_str());
	}
	else // Directory exists
	{
		throw DocExistsException(("Was unable to add document " + src + " to the site " + site + " since it already exists there").c_str());
	}
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
	lastserialnr =0;

}

bool is_stop(string word, vector<string> stop)
{
    return (count (stop.begin(), stop.end(), word) != 0);
}

void triedoc::idx(string site)
{
	string next;
	vector<string> stopWords = this->stopWords(site);

	string filePath = site + '\\' + docname + '\\' + docname + '.' + docext;
	
	ifstream fin;
	fin.open(filePath);
	regex rgx("[-a-zA-Z0-9]+"); // Represents all sequences of alphanumeric characters and hyphen
	vector<string> words;
	long pos;
	long lo=0; 
	do
	{
		pos = (long) fin.tellg();
		getline(fin,next);
		// Debugging
		//cerr << next << endl;
		//cerr << "Offset: " << lo << endl;
		for(sregex_iterator it(next.begin(), next.end(), rgx), it_end; it != it_end; ++it )
		{
			if((count (stopWords.begin(), stopWords.end(), (*it)[0]) == 0)
				&& ((*it)[0].matched))
			{
				// Debugging
				//cerr << "\t" << (*it)[0] << " at position " << it->position() << endl;
				add_node((*it)[0], lo + it->position());
			}
		}
		lo += next.length();
	}while(!fin.eof() && fin.good());
	if(!fin.eof())
		throw exception(
			("Error reading the contents of the file " + filePath).c_str());
	fin.close();
	flush(site);
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
		for(long j = 0; (j < 10) && (i < trienodesarray.end()); ++j, ++i)
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

void triedoc::printWords(long idx, string str)
{
	long node = idx;
	if (idx != trierootnode.nodeserialnr)
		str += triebuf.get_node(node).letter;
	for(long i = 0; i < trienode::LINKS_LENGTH; ++i)
	{
		if(triebuf.get_node(node).links[i] != trienode::NULL_LINK)
		{
			printWords(triebuf.get_node(node).links[i], str);
		}
	}
// Debugging
//	if(triebuf.get_node(node).wordend)
//	{
//		cout << str << endl;
//	}
}

void triedoc::add_node(string word, long offset)
{
	long index = trierootnode.nodeserialnr;
	long ptr = index;
    for(string::const_iterator chr = word.begin(); chr != word.end(); ++chr)
    {
        // If the next link doesn't exist, create it
		if(trienodesarray[ptr][*chr] == trienode::NULL_LINK)
        {
			trienodesarray.push_back(trienode(offset,0,*chr, false,lastserialnr++));
			trienodesarray[ptr].set_link(*chr, lastserialnr);
        }
        // Update data
        index = trienodesarray[ptr][*chr];
		ptr = index;//chng
    }
	++(trienodesarray[ptr].nrofoccurences);
	trienodesarray[ptr].wordend = true;
}

string triedoc::lineWithOffset(string path,long offset)
{
	if(offset < 0) return "";
	string docpath = doc_path(path,docname) + "." + docext;
	ifstream fin(docpath);
	string line;
	long count = 0;
	do
	{
		getline(fin,line);
		count += line.length();
		//cerr << "Current location: " << count << " line: " << line << endl;
	}while (count <= offset);
	//cerr << "Current location: " << count << " line: " << line << endl;
	return line;
}

string triedoc::expsearch (string path, string expr)
{
	expr = "(" + expr + ")";
	vector<vector<string> > atoms = get_atoms(expr);
	vector<Occurence> res;
	res.resize(atoms.size());
	transform(atoms.begin(), atoms.end(), res.begin(), AtomSearcher<Occurence>(trierootnode, triebuf));
	string sexp = replace_atoms(expr);
	long loc = shunting_yard(sexp, res);

//	cerr << "Expsearch invoked" << endl;
//	cerr << expr << " converted to:" << endl;
//	cerr << sexp << endl;
//	cerr << "Atom results: " << endl;
//	for(vector<Occurence>::const_iterator i = res.begin(); i != res.end(); ++i)
//		cerr << i->value << endl;
//	 cerr << "Shunting yard says result is: " << loc << endl;
//	 cerr << "Line including first occurence of searchexp: " << lineWithOffset(path, loc) << endl;
	return lineWithOffset(path, loc);
}

long triedoc::expcount (string path, string expr)
{
	expr = "(" + expr + ")";
	vector<vector<string> > atoms = get_atoms(expr);
	vector<Count> res;
	res.resize(atoms.size());
	transform(atoms.begin(), atoms.end(), res.begin(), AtomSearcher<Count>(trierootnode, triebuf));
	string sexp = replace_atoms(expr);
	long count = shunting_yard(sexp, res);
	
//	cerr << "Expcount invoked" << endl;
//	cerr << expr << " converted to:" << endl;
//	cerr << sexp << endl;
//	cerr << "Atom results: " << endl;
//	for(vector<Count>::const_iterator i = res.begin(); i != res.end(); ++i)
//		cerr << i->value << endl;
//	 cerr << "Shunting yard says result is: " << count << endl;
	return count;
}
bool triedoc::is_indexed(string path)
{
	ifstream ifile(doc_path(path,docname) + ".trie");
    return (ifile?true:false);
}
vector<string> triedoc::stopWords(string path)
{
	string stopPath = path;
	ifstream stopfin;
	string next;
	vector<string>stopWords;
	stopfin.open(stopPath);
	if(!stopfin.is_open())
	{
		return stopWords;
	}
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
	return stopWords;
}
void triedoc::writeStopWords(string sitePath,vector<string> words)
{
	ofstream stopout(sitePath + '\\' + docname + '\\' + docname + ".stop");
	for(vector<string>::const_iterator i = words.begin();i<words.end();i++)
	{
		stopout<<*i<<endl;
	}
}
void triedoc::docstopupdate(string sitepath, list<string> wordList, int code)
{
	string stoppath = sitepath + '\\' + docname + '\\' + docname + ".stop";
	switch(code)
	{
		case 1:
			{
			vector<string> stopWords = this->stopWords(stoppath);
			for(list<string>::const_iterator i = wordList.begin();i != wordList.end();i++)
			{
				//add to word list if it doesnt contain it
			}
			this->writeStopWords(sitepath,stopWords);
			break;
			}
		case 2:
			{
			vector<string> stopWords = this->stopWords(stoppath);
			for(list<string>::const_iterator i = wordList.begin();i != wordList.end();i++)
			{
				//remove from stop words
			}
			this->writeStopWords(sitepath,stopWords);
			break;
			}
		case 3:
			this->writeStopWords(sitepath,this->stopWords(sitepath + "\\stop.lst"));

			break;
	}
}
void triedoc::docidxupdate(string, list<string>, int)
{}