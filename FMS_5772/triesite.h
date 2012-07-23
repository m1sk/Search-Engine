#pragma once
#include<string>
#include<list>
#include"triedoc.h"
#include"fileutils.h"
using namespace std;

namespace Library {
	// A triesite is an abstraction of the search site
	class triesite
	{
	private:
		// The full path to the site
		string        sitename;
		// A list of the documents in the site
		list<triedoc> doclist;
		// A flag denoting whether the site is mounted
		bool          mounted;
		// A flag denoting whether the site is mounted
		// for queries ('q'/'Q') or maintenance ('m'/'M')
		char          mounttype;
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
	*     Creates a directory for the site
	* THROWS
	*     Unable to create a search site at _path_
	*     Error: _errorMsg_ - if there was an error creating the search site
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
	*                                or 'm' (or 'M') for maintenance giving full access
	* MEANING
	*    Populates doclist with triedocs for the site path passed
	**************************************************/
		void mount(string path,char mode='q');
	/*************************************************
	* FUNCTION
	*    unmount
	* MEANING
	*    Clears the doclist and resets all other data to default values
	* SEE ALSO
	*    mount()
	**************************************************/
		void unmount();
	/*************************************************
	* FUNCTION
	*    docexists
	* PARAMETERS
	*    string compname - document name (without extension)
	* RETURN VALUE
	*    If the document exists return an iterator in doclist
	*    pointing to the triedoc with compname or doclist.end()
	*    otherwise
	* MEANING
	*     Checks if a the parameter compname is in the triesite
	**************************************************/
		list<triedoc>::iterator docexists(string compname);
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
	*     Add the document given by name to the triesite by copying it to 
	*	  the site adding adding the document to the doclist
	* THROWS
	*	  "Document already exists in search site" - if document named "name" exists
	*        in the triesite
	* SEE ALSO
	*    putdoc()
	**************************************************/
		void docupload(string name,char func ='c');
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
	*    del
	* PARAMETERS
	*	 char removeType - Whether to perform logical ('l' or 'L')
	*					or physical ('p' or 'P') removal of the site
	*					(Default: logical)
	* MEANING
	*    Delete the site either logically or physically based on parameter
	* THROWS
	*	The appropriate exception if required
	* SEE ALSO
	*    triedoc::del()
	*    fileutils::removeDirectoryWithSubs
	*    errno
	*    strerror
	**************************************************/
		void del(char removeType = 'l');
	/*************************************************
	* FUNCTION
	*    docdel
	* PARAMETERS
	*	 string name - name of doc in doc list to delete 
	*    char   type - Whether to perform logical ('l' or 'L')
	*					or physical ('p' or 'P') removal of the site
	*					(Default: logical)
	* MEANING
	*    Delete doc (basicly call del on the doc with removeType) and remove from doclist
	* THROWS
	*	Couldn't delete  _name_ because there is no document by that name.
	* SEE ALSO
	*    triedoc::del()
	**************************************************/
		void docdel(string name,char removeType = 'l');
	/*************************************************
	* FUNCTION
	*    putstopfl
	* PARAMETERS
	*	 string   stopName - path to a file with a "stop" extension
	*                       if this is not a full path assumes relative to current directory
	* MEANING
	*   copy to site and rename to stop.lst
	* THROWS
	*	
	**************************************************/
		void putstopfl(string stopName);
	/*************************************************
	* FUNCTION
	*    docidx
	* PARAMETERS
	*	 string   docName - name of a doc in doclist
	* MEANING
	*   Call idx on docName if that doc exists in doclist
	* THROWS
	*	_stopName_ is not a valid stop file
	**************************************************/
		void docidx(string docName);
    /*************************************************
	* FUNCTION
	*    listdoc
	* PARAMETERS
	*    long  listtype - 0 or 1 or 2 defining a list of what will be returned 
	*                    0 - all document names
	*					 1 - only indexed document names
    *					 2 - only non-indexed document names
	*                    (default - 0)  
	*					
	* RETURN VALUE
	*    List of the names the document that match the criteria of _listtype_  
	**************************************************/
		list<string> listdoc(long listtype = 0);
	/*************************************************
	* FUNCTION
	*    expsearch
	* PARAMETERS
	*	 string name - name of doc in doc list to search 
	*    string exp - A search expression
	* RETURN VALUE
	*    Preform expsearch on the triedoc named _name_ with _exp_
	* THROWS
	*	Couldn't search  _name_ because there is no document by that name.
	* SEE ALSO
	*    triedoc::expsearch()
	**************************************************/
		string expsearch (string docName,string exp);
    /*************************************************
	* FUNCTION
	*    expcount
	* PARAMETERS
	*	 string name - name of doc in doc list to search 
	*    string exp - A search expression
	* RETURN VALUE
	*    Preform expcount on the triedoc named _name_ with _exp_
	* THROWS
	*	Couldn't search  _name_ because there is no document by that name.
	* SEE ALSO
	*    triedoc::expcount()
	**************************************************/
		long expcount (string docName,string exp);
	/*************************************************
	* FUNCTION
	*    doclookup
	* PARAMETERS
	*    string exp - A search expression
	* RETURN VALUE
	*    A list of all the documents that match the _exp_
	**************************************************/
		list<string> doclookup(string);
	/*************************************************
	* FUNCTION
	*    destructor
	* MEANING
	*     Deletes all allocated memory used by the variables, unmounts
	*	  and set other variables to default data
	* SEE ALSO
	*     unmount()
	**************************************************/
		~triesite(void);
	};
}