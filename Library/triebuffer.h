#pragma once
#include"fileutils.h"
#include"trienode.h"
using namespace std;
using namespace System;

namespace Library {
	class triebuffer
	{
		fstream file;
		string path;
		trienode buffer[10];
	public:
		triebuffer(void);
		~triebuffer(void);
	};
}