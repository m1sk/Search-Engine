#pragma once
#include<string>
#include<vector>
#include"fileutils.h"
#include"triebuffer.h"
#include"trienode.h"
using namespace std;

namespace Library {
	class triedoc
	{
	private:
		// name of the document 
		string     docname;
		// extension of the document
		string     docext;
		// root of the trie tree
		trienode   trierootnode;
		// buffer containing current trienode
		triebuffer triebuf;
		// dynamic array used when creating and searching trietree
		vector<trienode> trienodesarray;
	public:
	/*************************************************
	* FUNCTION
	*    constructor
	* PARAMETERS
	*    string path - The path to the site (If it is not a full path, it is assumed
	*					the directory is in the current directory)
	*					(Default: current path)
	*    string name - name of the document
	*                   (Default: "")
	* RETURN VALUE
	*    A triedoc object initialized with the parameters passed
	* MEANING
	*     if name isn't "" then putdoc() is called with path and name
	*     otherwise just initialize variables to default data
	* SEE ALSO
	*     putdoc()
	**************************************************/
		triedoc(string path = "",string name = "");
	/*************************************************
	* FUNCTION
	*    putdoc
	* PARAMETERS
	*    string path - The path to the site (If it is not a full path, it is assumed
	*					the directory is in the current directory)
	*					(Default: current path)
	*    string src - name of the document (must have extension) if not a full path
	*                  assumes relative to current path
	* MEANING
	*     creates a folder in the site and copies the document to the new folder 
	*     also copies the documents .stop file if it exists
	* THROWS 
	*    Was unable to add document to search site.\
	*		Does it already exist?" - if there is an error creating the document folder 
	* SEE ALSO
	*     putdoc()
	**************************************************/
		void putdoc(string site,string src,char mode = 'c');
	/*************************************************
	* FUNCTION
	*    putdoc
	* PARAMETERS
	*    string  site - The path to the site (must be full path) 
	*    string  dest - destination
	*					(Default: create current directory) 
	* MEANING
	*     copies this document from the site to destination
	**************************************************/
		void getdoc(string site,string dest = getCurrentPath());
	/*************************************************
	* FUNCTION
	*    del
	* PARAMETERS
	*	 string     fullPath - full path to the triesite
	*    char removeType - Whether to perform logical ('l' or 'L')
	*					or physical ('p' or 'P') removal of the site
	*					(Default: logic)
	* MEANING
	*    delete doc either logically or physically based on parameter
	*    and remove from doclist
	* THROWS
	*	
	*
	**************************************************/
		void del(string fullPath,char removeType='l');
	/*************************************************
	* FUNCTION
	*    idx
	* PARAMETERS
	*	 string     fullPath - full path to the triesite
	* MEANING
	*   
	* THROWS
	*    
	* SEE ALSO
	*    flush()
	**************************************************/
		void idx(string fullPath);
	/*************************************************
	* FUNCTION
	*    flush
	* PARAMETERS
	*	 string     fullPath - full path to the triesite
	* MEANING
	*   
	* THROWS
	*    
	* SEE ALSO
	*   
	**************************************************/
		void flush(string fullPath);
		void add_node(string word, long offset);
	private:
		int get_node(int);
		void indexing(string site);

	public:
		// getter for docname
		string getdocname() const { return docname; }
		// destructor
		~triedoc(void);
	};
}