#pragma once
#include<string>
#include<list>
#include"triedoc.h"
#include"fileutils.h"
using namespace std;
using namespace System;

namespace Library {
	// triesite manages a directory which contains triedocs
	// 
	class triesite
	{
	private:
		// full path for the site
		string         sitename;
		// documents in the site
		list<triedoc>  doclist;
		// flag denoting whether the site is mounted
		bool           mounted;
		// mounttype can be 'q' meaning the site is mounted for queries only
		// or 'm' for maintenance giving full access 
		char           mounttype;
	public:
    /*************************************************
	* FUNCTION
	*    constructor
	* PARAMETERS
	*    string path - The path to the site (If it is not a full path, it is assumed
	*					the directory is in the current directory)
	*					(Default: empty path)
	*	 char   func - Whether to create a new site ('c' or 'C')
	*					or mount an existing site   ('m' or 'M')
	*					(Default: create new)
	*	 char   mode - The mount type, which is passed to mount()
	* RETURN VALUE
	*    A triesite object initialized with the parameters passed
	* MEANING
	*     initializes variable to 
	* SEE ALSO
	*     mount()
	*     create()
	**************************************************/
		triesite(string name ="", char func = 'c', char mode = 'q');
	/*************************************************
	* FUNCTION
	*    create
	* PARAMETERS
	*    string path - The path to the site, this must be a full path
	* MEANING
	*     creates a directory for the site
	* SEE ALSO
	*     mount()
	*     createDirectory()
	**************************************************/
		void create(string path);
	/*************************************************
	* FUNCTION
	*    mount
	* PARAMETERS
	*    string path - The path to the site (must be full path)
	*	 char   mode - The mount type,  'q' (or 'Q') meaning the site is mounted for queries only
	*    or 'm' (or 'M') for maintenance giving full access
	* MEANING
	*     populates doclist with triedocs for the parameter site
	* THROWS
	*	  "Unable to create a search site" - there is an error creating the directory
	**************************************************/
		void mount(string path,char mode='q');
	/*************************************************
	* FUNCTION
	*    unmount
	* MEANING
	*     clears doclist and resets all other data to default values
	* SEE ALSO
	*     mount()
	**************************************************/
		void unmount();
	/*************************************************
	* FUNCTION
	*    docexists
	* PARAMETERS
	*    string compname - document name (without extension)
	* RETURN VALUE
	*    if the document exists return the triedoc for compname
	*    otherwise NULL
	* MEANING
	*     checks if a the parameter compname is in the triesite
	**************************************************/
		triedoc* docexists(string compname);
	/*************************************************
	* FUNCTION
	*    docupload
	* PARAMETERS
	*    string name - The path to the document (If it is not a full path, it is assumed
	*					then assumed that this is relative to the current directory)
	*	 char   func - Whether to copy ('c' or 'C')
	*					or move ('m' or 'M') the document into the site
	*					(Default: copy)
	* MEANING
	*     add the document given by name to the triesite by copying it to 
	*	  the site adding adding the document to the doclist
	* THROWS
	*	  "Document already exists in search site" - if document named "name" exists
	*        in the triesite
	* SEE ALSO
	*    putdoc()
	**************************************************/
		void docupload(string name,char func);
	/*************************************************
	* FUNCTION
	*    docdownload
	* PARAMETERS
	*    string name - name of a doc in the triesite
	*	 string path- destination path for the document 
	*                 (if this not a full path then we assume that it is 
	*					relative to current directory)
	* RETURN VALUE
	*    Full path of the document but if no such file exists then null 
	* MEANING
	*     copies the doc named name to the destination path
	* SEE ALSO
	*    getdoc()
	**************************************************/
		string docdownload(string name,string path);
	/*************************************************
	* FUNCTION
	*    destructor
	* MEANING
	*     deletes all allocated memory used by the variables
	*	  and set other variables to default data
	* SEE ALSO
	*     unmount()
	**************************************************/
		~triesite(void);
	};
}