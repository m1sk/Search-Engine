#pragma once
#include <string>
#include"fileutils.h"
using namespace std;

namespace Library {
	struct trienode {
	// A trienode is a node in a trie tree
		static const long LINKS_LENGTH = 256;
		static const long INVALID_NODE = -1;

		// The serial number for the node in the trie tree
		long          nodeserialnr;
		// The offset for the first instance of a word in the text file
		long          firstoffset;
		// The number of words in the text file
		long          nrofoccurences;
		// The letter this node represents
		unsigned char letter;
		// Whether this node is the end of a word (when looking up the trie tree)
		bool          wordend;
		// Array indeces are the ASCII values of the characters
		// Array values  are the serial numbers of the next nodes
		long int      links [LINKS_LENGTH];
		/*************************************************
		* FUNCTION
		*    constructor
		* RETURN VALUE
		*    A trienode object initialized with the passed data
		* DEFAULTS
		*    A trienode object initialized with default data
		*    (everything -1, letter is ASCII 255,
		*     links are initialized to INVALID_NODE)
		**************************************************/
		trienode(long _serialnr = INVALID_NODE, long _firstoffset = -1,
			long _nrofoccurences = -1, unsigned char _letter = 0xFF,
			bool _wordend = false);
		/*************************************************
		* FUNCTION
		*    operator[]
		* RETURN VALUE
		*    The index of the trienode pointed to by the ascii value of c
		**************************************************/
		long& operator[](char c);
		/*************************************************
		* FUNCTION
		*    print_node
		* MEANING
		*    Prints the values of the node nicely
		**************************************************/
		void print_node() const;
	};
}

