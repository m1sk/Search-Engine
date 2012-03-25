#pragma once
#include <string>
#include"fileutils.h"
using namespace std;
#define LINKS_LENGTH 256
class trienode
{
private:
	long nodeserialnr;
	long firstoffset;
	long nrofoccurences;
	unsigned char letter;
	bool wordend;
	unsigned char links [LINKS_LENGTH];
public:
	trienode(void);
	~trienode(void);
	static string serialize(trienode);
	static trienode deserialize(string);
};

