﻿#pragma once
#include<string>
#include<vector>
#include"fileutils.h"
#include"triebuffer.h"
#include"trienode.h"
using namespace std;

namespace Library {
	class triedoc {
	// A triedoc is an abstraction of a document in the search site
		long lastserialnr;
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
	*    string site   - The path to the site (If it is not a full path, it is assumed
	*                    the directory is in the current directory)
	*                    (Default: current path)
	*    string source - The path to the document
	*                    (Default: "")
	* RETURN VALUE
	*    A triedoc object initialized with the parameters passed
	* MEANING
	*     if name isn't "" then putdoc() is called with path and name
	*     otherwise just initialize variables to default data
	* SEE ALSO
	*     putdoc()
	**************************************************/
		triedoc(string site = "",string name = "", char mode = 'c');
	/*************************************************
	* FUNCTION
	*    copy constructor
	* PARAMETERS
	*    triedoc& other - A triedoc reference
	* RETURN VALUE
	*    A copy of the triedoc object passed
	* MEANING
	*     Copies every member of the passed object deeply
	*     (I.e. the buffer points to a new fstream object)
	**************************************************/
		triedoc(const triedoc& other);
	/*************************************************
	* FUNCTION
	*    putdoc
	* PARAMETERS
	*    string site - The path to the site (If it is not a full path, it is assumed
	*					the directory is in the current directory)
	*					(Default: current path)
	*    string src  - Name of the document (must have extension) if not a full path
	*                   assumes relative to current path
	*    char   mode - Whether to move ('m'/'M') or copy ('c'/'C') the file
	* MEANING
	*     Creates a folder in the site and copies the document to the new folder 
	*     also copies the documents .stop file if it exists
	* THROWS 
	*    Was unable to add document _documentPath_ to search site _sitePath_.
	*	 Does it already exist there?" - if there is an error creating the document folder
	**************************************************/
		void putdoc(string site,string src,char mode = 'c');
	/*************************************************
	* FUNCTION
	*    getdoc
	* PARAMETERS
	*    string  site - The path to the site (must be full path) 
	*    string  dest - Destination
	*					(Default: create current directory) 
	* MEANING
	*     Copies this document from the site to destination
	* THROWS 
	*     Failed to create directory _destinationPath_ - if there is an error
	*                                                    creating the destination folder
	**************************************************/
		void getdoc(string site,string dest = getCurrentPath());
	/*************************************************
	* FUNCTION
	*    del
	* PARAMETERS
	*	 string site - The path to the site
	*    char   type - Whether to perform logical ('l' or 'L')
	*					or physical ('p' or 'P') deletion of the document
	*					(Default: logical)
	* MEANING
	*    Delete doc either logically or physically based on the removeType parameter
	*    When deleting the file, default values will be set to all members
	* THROWS
	*	 Error while logically deleting _docPath_. Error: _errnoMeaning_ - if there was an error
	*                                                                      deleting the .trie file
	*                                                                      other than non-existence
	**************************************************/
		void del(string site,char type='l');
	/*************************************************
	* FUNCTION
	*    idx
	* PARAMETERS
	*	 string site - Full path to the triesite
	* MEANING
	*    Indexes the words in the document into a trie tree
	* THROWS
	*    Error reading the contents of the file _filePath_ - if there was an error reading the file
	* SEE ALSO
	*    flush()
	**************************************************/
		void idx(string site);
	/*************************************************
	* FUNCTION
	*    flush
	* PARAMETERS
	*	 string site - Full path to the site
	* MEANING
	*     Writes the trie to a file named _docname_.trie
	**************************************************/
		void flush(string site);
	/*************************************************
	* FUNCTION
	*    printNodes
	* MEANING
	*     Print every node in the trie
	**************************************************/
		void printNodes();
	/*************************************************
	* FUNCTION
	*    printWords
	* MEANING
	*     Print every word in the trie
	**************************************************/
		void printWords();
	/*************************************************
	* FUNCTION
	*    printWords
	* PARAMETERS
	*	 long    idx - The index of the node
	*	 string str - The prefix of the words in the node
	* MEANING
	*     Print every word in the node, prefixed by the string
	**************************************************/
		void printWords(long idx, string str);
	/*************************************************
	* FUNCTION
	*    getdocname
	* RETURN VALUE
	*    The triedoc's name
	**************************************************/
		string getdocname() const { return docname; }
	/*************************************************
	* FUNCTION
	*    expsearch
	* PARAMETERS
	*    string path   - The full path to the site 
	*    string expr - expression to search for in the document
	* RETURN VALUE
	*    The first line that contains a match to the expression
	* SEE ALSO
	*     searchutils.h
	**************************************************/
	    string expsearch (string path, string expr);
	/*************************************************
	* FUNCTION
	*    expcount
	* PARAMETERS
	*    string path   - The full path to the site 
	*    string expr - expression to search for in the document
	* RETURN VALUE
	*   The amount of times the search expression can be found in the document
	* SEE ALSO
	*     searchutils.h
	**************************************************/
		long expcount (string path, string expr);
	/*************************************************
	* FUNCTION
	*    lineWithOffset
	* PARAMETERS
	*    string path  - The full path to a file 	
	*	 long offset  - An offset in the file
	* RETURN VALUE
	*   The line in the file that contains the _offset_  character
	**************************************************/
		string lineWithOffset(string path,long offset);
	//If a ".trie" file exists then the file is indexed
	bool is_indexed(string sitePath);	
private:
	/*************************************************
	* FUNCTION
	*    add_node
	* PARAMETERS
	*	 string word - The word to add
	*    long offset - The offset of the current location of the word in the file
	* MEANING
	*    Recursively adds the word to the trie, updating nodes if they exist and
	*    creating them if they don't
	**************************************************/
		void add_node(string word, long offset);
	};
}