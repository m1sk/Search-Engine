#pragma once
#include <string>
#include"fileutils.h"
using namespace std;

namespace Library {
	struct trienode {
	// A trienode is a node in a trie tree
		static const long LINKS_LENGTH = 256;
		static const long INVALID_NODE = -1;

		// The last serial number assigned
		//static long   lastserialnr;
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
		*    default constructor
		* RETURN VALUE
		*    A trienode object initialized with default data
		*    (everything 0, except for the links,
		*     which are initialized to INVALID_NODE)
		**************************************************/
		trienode();
		/*************************************************
		* FUNCTION
		*    constructor
		* RETURN VALUE
		*    A trienode object initialized with the passed data
		**************************************************/
		trienode(long _firstoffset,
			long _nrofoccurences, unsigned char _letter,
			bool _wordend, long _serialnr);
		/*************************************************
		* FUNCTION
		*    operator[]
		* RETURN VALUE
		*    The index of the trienode pointed to by the ascii value of c
		**************************************************/
		long operator[](char c);
		/*************************************************
		* FUNCTION
		*    set_link
		* PARAMETERS
		*    char idx - The index of the link to be changed
		*    long val - The new value for the link
		* MEANING
		*    Update the link idx with the new value val
		**************************************************/
		void set_link(char idx, long val);
		/*************************************************
		* FUNCTION
		*    print_node
		* MEANING
		*    Prints the values of the node nicely
		**************************************************/
		void print_node() const;
	};

}
