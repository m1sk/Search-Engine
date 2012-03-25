#include <windows.h>
#include <iostream>
#include <list>
#include <fstream>

using namespace std;

// return all file name in folder
static list<string> getFileNameList(string rootPath)
{

	if(rootPath.compare("")!=0)
			rootPath.append("\\");
	rootPath.append("*");

	list<string> myList;
	void*  hFind = INVALID_HANDLE_VALUE;
	WIN32_FIND_DATA ffd;

	hFind = FindFirstFile(rootPath.c_str(), &ffd);

	if (INVALID_HANDLE_VALUE == hFind) 
		return myList;

	do
	{
		if (!(ffd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY))
			myList.push_back(ffd.cFileName);		
	}
	while (FindNextFile(hFind, &ffd) != 0);

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
	WIN32_FIND_DATA ffd;


	hFind = FindFirstFile(rootPath.c_str(), &ffd);

	if (INVALID_HANDLE_VALUE == hFind) 
		return result;

	do
	{
		if (ffd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
			result.push_back(ffd.cFileName);		
	}
	while (FindNextFile(hFind, &ffd) != 0);
	if(result.front().compare(".")==0)
		result.pop_front(); // remove '.' 
	if(result.front().compare("..")==0)
		result.pop_front(); // remove '..'
	return result;
}

// print all string element from list<string>
static void printAllList(list<string> myList)
{
	int size = myList.size();
	list<string>::iterator it = myList.begin();
	for(it =myList.begin(); it!=myList.end();it++ )
	{
		const char* dirName = (*it).c_str();// convert from string to char*
		cout<<" "<<dirName<<endl;
	}
}

// Returns the current folder
//Folder from which you run the project executable file
static string getCurrentPath() 
{     
	char buffer[MAX_PATH];     
	GetModuleFileName( NULL, buffer, MAX_PATH );     
	string::size_type pos = string( buffer ).find_last_of( "\\/" );     
	return string( buffer ).substr( 0, pos); 
} 

//return suffix file  "myFile.txt" ==> "txt"
static string getFileSuffix(string fileName)
{
	int start = fileName.find_last_of('.')+1;
	if(start == 0)
		return "";
	int sizeSuffix = fileName.length()-start;
	return fileName.substr(start,sizeSuffix);
}

//return preffix file  "myFile.txt" ==> "myFile"
static string getFilePrefix(string fileName)
{
	int end= fileName.find_last_of('.');
	if(end == -1)
		return fileName;
	return fileName.substr(0,end);
}

// _mkdir
static int createDirectory(string path)
{
	// NULL == create directory with a default security descriptor
	return CreateDirectory(path.c_str(),NULL);
}

// return file name without path  "c:\\dir1\\subdir2\\text.txt" ==> "text.txt"
static string getFileName(string path)
{
	int start = path.find_last_of('\\')+1;
	int end = path.length();
	if(start == -1)
		return path;
	return path.substr(start,end-start);
}

// return file path
static string getFilePath(string path)
{
	int end = path.find_last_of('\\');
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

	return MoveFile(sourceFile.c_str(),destDirectory.c_str());
}

// copy file from sourceFile to destDirectory
static int copyFileToDirectory(string sourceFile , string destDirectory, bool overwriteFlag)
{
	destDirectory.append("\\");
	string fileName = getFileName(sourceFile);
	destDirectory.append(fileName);

	return CopyFile(sourceFile.c_str(),destDirectory.c_str(),overwriteFlag);
}
static int transferFileToDirectory(char mode, string sourceFile , string destDirectory, bool overwriteFlag = true)
{
	if(mode == 'c' || mode == 'C'){
		copyFileToDirectory(sourceFile,destDirectory,overwriteFlag);
	}
	else if(mode == 'm' || mode == 'M'){
		moveFileToDirectory(sourceFile,destDirectory);
	}
}

