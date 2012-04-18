#pragma once
#include <string>
#include"fileutils.h"
using namespace std;
#define LINKS_LENGTH 256
#define NULL_LINK -1
using namespace System;

namespace Library {
	// a trienode is a node in a trie tree
	struct trienode
	{
		// serial number for the node in the trie tree
		long          nodeserialnr;
		// offset for the first instance of a word in the text file
		long          firstoffset;
		// number of words in the text file
		long          nrofoccurences;
		// a character for this node
		unsigned char letter;
		// is this character the end of a word (when looking up the trie tree)
		bool          wordend;
		// array characters that represent the ascii character 
		// for next node, each entry is the serial of next available node otherwise -1  
		long int      links [LINKS_LENGTH];
		/*************************************************
		* FUNCTION
		*    default constructor
		* RETURN VALUE
		*    A trienode object initialized with default data
		*    (everything 0, except for the links,
		*     which are initialized to NULL_LINK)
		**************************************************/
		trienode();
		/*************************************************
		* FUNCTION
		*    constructor
		* RETURN VALUE
		*    A trienode object initialized with the passed data
		**************************************************/
		trienode(long _nodeserialnr, long _firstoffset,
			long _nrofoccurences, unsigned char _letter,
			bool _wordend, long int _links [LINKS_LENGTH]);
	//	static string serialize(trienode);
	//	static trienode deserialize(string);
	};

}