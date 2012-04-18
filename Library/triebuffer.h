#pragma once
#include"fileutils.h"
#include <vector>
#include"trienode.h"
using namespace std;
using namespace System;

namespace Library {
	struct triebuffer
	{
		// A pointer to the file object the buffer is associated with
		fstream* file;
		// The path to the file
		string path;
		// A buffer of constant length 10 of the trienode objects at
		// the current position in the file
		// (I.e. an interpretation of the next (sizeof trienode) * 10 bytes
		vector<trienode> buffer;
	/*************************************************
	* FUNCTION
	*    constructor
	* RETURN VALUE
	*    A triebuffer object initialized with default data      
	**************************************************/
		triebuffer();
	};
}