// console_tester.cpp : main project file.

#include <iostream>
#include "..\Library\triesite.h"


using namespace std;
using namespace System;
using namespace Library;

int main(/*array<System::String ^> ^args*/)
{
//  Console::WriteLine(L"Hello World");
//	cout<<"Choose a sitepath"<<endl;
	string path;
//	cin>>path;
	cout<< "Hello";
	triesite* site = new triesite("C:\\temp\\");
	cin >> path;
	cout << path;
	cin >> path;
    return 0;
}
