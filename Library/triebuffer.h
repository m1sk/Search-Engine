#pragma once
#include"fileutils.h"
#include <vector>
#include"trienode.h"
using namespace std;
using namespace System;

namespace Library {
	class triebuffer
	{
		fstream* file;
		string path;
		vector<trienode> buffer;
	public:
		triebuffer();
		~triebuffer();
	};
}