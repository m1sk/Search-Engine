// strconvert.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"


void prtCstring(char *str)
{
	cout << "printing C-style string " << str << endl; 
}
void prtCppString1(string &str)
{
    cout << "printing C++ string passed by reference " << str << endl; 
}

void prtCppString2(string *str)
{
    cout << "printing C++ string passed by pointer " << *str << endl; 
}

void prtCppString3(string str)
{
    cout << "printing C++ string passed by value " << str << endl; 
}

int _tmain(int argc, _TCHAR* argv[])
{
	// first option for converting Cpp-String into C-charArray
	string cppst1("Hello!");
	char cst1[50];
	strcpy(cst1,cppst1.c_str());
	cout << "cppst1 = " << cppst1 << endl;
	cout << "cst1 = " << cst1 << endl;
	// second option for converting Cpp-String into C-charArray
	char cstrarray[50];
	string cppstr = "Hello!";
	int arraylen = cppstr.length();
	for (int i = 0; i < arraylen; i++)
		cstrarray[i] = cppstr[i];
	cstrarray[arraylen] = '\0';
	cout << "cppstr = " << cppstr << endl;
	cout << "cstrarray = " << cstrarray << endl;
	// third option for converting Cpp-String into C-charArray
	string cppstr2 = "Hello!";
	char *cstr = &cppstr2[0];
	cout << "cppstr2 = " << cppstr2 << endl;
	cout << "cstr = " << cstr << endl;
	// changing the contents of a Cpp string -- option 1 
	//   the contents of cstr is changed and it can be seen also using cppstr2
	cstr[1] = 'a'; 
	cout << "changed cppstr2 = " << cppstr2 << endl; 
	cout << "changed cstr = " << cstr << endl;
	// changing the contents of a Cpp string -- option 2 
	//   the contents of cppstr2 is changed and it can be seen also using cstr
	cppstr2[1] = 'a'; 
	cout << "changed cppstr2 again = " << cppstr2 << endl;
	cout << "changed cstr again = " << cstr << endl;
	// changing the contents of a Cpp string -- option 3 
	//   the substring of cppstr2, whose length is 3 and starts at position 2, 
	//   is replaced by the string "ab"
	cppstr2.replace(2,3,"ab");  
	cout << "changed cppstr2 again again = " << cppstr2 << endl;
	cout << "changed cstr again again = " << cstr << endl;
	/*========================================================*/
	// first option for converting C-charArray into Cpp-String
	string cppstr3, cppstr4;
	char Cchararray[] = "Hello!";
	int stlen = strlen(Cchararray);
	for (int i = 0; i < stlen; i++)
       cppstr3 += Cchararray[i];
	cout << "cppstr3 = " << cppstr3 << endl;
	cout << "Cchararray = " << Cchararray << endl;
	// second option for converting C-charArray into Cpp-String
	char Cchararray2[] = "Hello!";
	cppstr4 = Cchararray2;
	cout << "cppstr4 = " << cppstr4 << endl;
	cout << "Cchararray2 = " << Cchararray2 << endl;
	/*========================================================*/
	// passing strings as parameters -- C style
	cout << "Passing to prtCstring the C string " << Cchararray << endl;
	prtCstring(Cchararray);
	/*========================================================*/
	// passing strings as parameters -- option 1 -- C++ style
	cout << "Passing by reference to prtCppString1 the C++ string " << cppstr3 << endl;
	prtCppString1(cppstr3);
	// passing strings as parameters -- option 2 -- C++ style
	cout << "Passing by pointer to prtCppString2 the C++ string " << cppstr3 << endl;
	prtCppString2(&cppstr3);
	// passing strings as parameters -- option 3 -- C++ style
	cout << "Passing by value to prtCppString3 the C++ string " << cppstr3 << endl;
	prtCppString3(cppstr3);
	//
	cout << "press any key to continue ... " << endl;
	getchar();
	return 0;


}