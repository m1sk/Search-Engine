#pragma once
#include <string>
#include"fileutils.h"
using namespace std;
#define LINKS_LENGTH 256
using namespace System;

namespace Library {
	// a trienode is a node in a trie tree
	class trienode
	{
	private:
		// serial number for the node in the trie tree
		long          nodeserialnr;
		// offset for the first occerance of a word in the text file
		long          firstoffset;
		// number of words in the text file
		long          nrofoccurences;
		// a character for this node
		unsigned char letter;
		// is this charater the end of a word (when looking up the trie tree)
		bool          wordend;
		// array characters that represent the ascii character 
		// for next node, each entry is the serial of next avaliable node otherwise -1  
		long int      links [LINKS_LENGTH];
	public:
		trienode(void);
		~trienode(void);
		static string serialize(trienode);
		static trienode deserialize(string);
	};

}