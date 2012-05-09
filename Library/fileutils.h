#pragma once
#include <windows.h>
#include <iostream>
#include <list>
#include <fstream>
#include <sstream>
#include <stdio.h>
using namespace std;

namespace Library {

	/*
	* This library includes common functions involving files
	* 
	*/

	// return all file name in folder
	static list<string> getFileNameList(string rootPath)
	{

		if(rootPath.compare("")!=0)
				rootPath.append("\\");
		rootPath.append("*");

		list<string> myList;
		void*  hFind = INVALID_HANDLE_VALUE;
		WIN32_FIND_DATA wfd;
		LPWIN32_FIND_DATAA ffd = (LPWIN32_FIND_DATAA)&wfd;
		hFind = FindFirstFileA(rootPath.c_str(), ffd);

		if (INVALID_HANDLE_VALUE == hFind) 
			return myList;
		do
		{
			if (!(ffd->dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY))
				myList.push_back(ffd->cFileName);		
		}
		while (FindNextFileA(hFind, ffd) != 0);
		FindClose(hFind);
		return myList;
	}

	// return all sub-directory name in folder
	static list<string> getSubDirectoryNameList(string rootPath)
	{
		if(rootPath.compare("")!=0)
				rootPath.append("\\");
		rootPath.append("*");

		list<string> result;

		void*  hFind = INVALID_HANDLE_VALUE;
		WIN32_FIND_DATA wfd;
		LPWIN32_FIND_DATAA ffd = (LPWIN32_FIND_DATAA)&wfd;

		hFind = FindFirstFileA(rootPath.c_str(), ffd);

		if (INVALID_HANDLE_VALUE == hFind) 
			return result;

		do
		{
			if (ffd->dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
				result.push_back(ffd->cFileName);		
		}
		while (FindNextFileA(hFind, ffd) != 0);
		if(result.front().compare(".")==0)
			result.pop_front(); // remove '.' 
		if(result.front().compare("..")==0)
			result.pop_front(); // remove '..'
		return result;
	}
	static void removeDirectory(string dirName)
	{
		//remove(dirName.c_str());
		RemoveDirectoryA(dirName.c_str());
		if(errno != 0)
			throw exception(strerror(errno));
	}
	static void removeDirectoryWithSubs(string dirPath)
	{
		list<string> files = getFileNameList(dirPath);
		list<string>::iterator it = files.begin();
		for(it =files.begin(); it!=files.end();it++ )
		{
			remove((dirPath+"\\"+*it).c_str());
		}
		list<string> directories = getSubDirectoryNameList(dirPath);
		 it = directories.begin();
		for(it =directories.begin(); it!=directories.end();it++ )
		{
			removeDirectoryWithSubs(dirPath+"\\"+(*it));
		}
		removeDirectory(dirPath.c_str());
	}
	// print all string element from list<string>
	static void printAllList(list<string> myList)
	{
		size_t size = myList.size();
		list<string>::iterator it = myList.begin();
		for(it =myList.begin(); it!=myList.end();it++ )
		{
			const char* dirName = (*it).c_str();// convert from string to char*
			cout<<" "<<dirName<<endl;
		}
	}
	// returns true if the parameter "path" is a full path
	static bool isFullPath(string path)
	{

		return (path[1]==':' && path[2]=='\\');
	}

	// Returns the current folder
	//Folder from which you run the project executable file
	static string getCurrentPath() 
	{
		char buffer[MAX_PATH];     
		GetModuleFileNameA(NULL, buffer, MAX_PATH);     
		string::size_type pos = string(buffer).find_last_of( "\\/" );
		string::size_type pos2 = string(buffer).substr(0, pos).find_last_of( "\\/" );     
		
		return string(buffer).substr(0, pos2); 
	} 

	// if a the parameter "path" isn't a full path this function will concatenate "path" to the current directory
	static string makeFullPath(string path)
	{
		if(isFullPath(path))
		{
			return path;
		}
		stringstream ss;
		ss << getCurrentPath() << "\\" << path;
		return ss.str();
	}

	//return suffix file  "myFile.txt" ==> "txt"
	static string getFileSuffix(string fileName)
	{
		size_t start = fileName.find_last_of('.')+1;
		if(start == 0)
			return "";
		size_t sizeSuffix = fileName.length()-start;
		return fileName.substr(start,sizeSuffix);
	}

	//return prefix file  "myFile.txt" ==> "myFile"
	static string getFilePrefix(string fileName)
	{
		size_t end= fileName.find_last_of('.');
		if(end == -1)
			return fileName;
		return fileName.substr(0,end);
	}

	// _mkdir
	static int createDirectory(string path)
	{
		// NULL == create directory with a default security descriptor
		return CreateDirectoryA(path.c_str(),NULL);
	}

	// return file name without path  "c:\\dir1\\subdir2\\text.txt" ==> "text.txt"
	static string getFileName(string path)
	{
		size_t start = path.find_last_of('\\')+1;
		size_t end = path.length();
		if(start == -1)
			return path;
		return path.substr(start,end-start);
	}

	// return file path
	static string getFilePath(string path)
	{
		size_t end = path.find_last_of('\\');
		if(end == -1)
			return "";
		return path.substr(0,end);
	}

	// move file from sourceFile to destDirectory
	static int moveFileToDirectory(string sourceFile , string destDirectory)
	{
		destDirectory.append("\\");
		string fileName = getFileName(sourceFile);
		destDirectory.append(fileName);

		return MoveFileA(sourceFile.c_str(),destDirectory.c_str());
	}

	// copy file from sourceFile to destDirectory
	static int copyFileToDirectory(string sourceFile , string destDirectory, bool overwriteFlag)
	{
		destDirectory.append("\\");
		string fileName = getFileName(sourceFile);
		destDirectory.append(fileName);

		return CopyFileA(sourceFile.c_str(),destDirectory.c_str(),overwriteFlag);
	}

	static int transferFileToDirectory(char mode, string sourceFile , string destDirectory, bool overwriteFlag = true)
	{
		if(mode == 'c' || mode == 'C'){
			return copyFileToDirectory(sourceFile,destDirectory,overwriteFlag);
		}
		else if(mode == 'm' || mode == 'M') {
			return moveFileToDirectory(sourceFile,destDirectory);
		}
		return 0;
	}

	static string appendPath(string base, string extra)
	{
		return base + "\\" + extra;
	}

	static string find_triedoc(string site, string name)
	{
		list<string>files;
		list<string>::iterator fileit;
		files = getFileNameList(appendPath(site, name));
		for(fileit = files.begin(); fileit!=files.end(); fileit++)
		{
			if((getFilePrefix(*fileit) == name)
				&& (getFileSuffix(*fileit) != string("stop"))
				&& (getFileSuffix(*fileit) != string("trie")))
				return *fileit;
		}
		return "";
	}
}