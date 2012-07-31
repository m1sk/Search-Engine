#pragma once
#include"fileutils.h"
#include <vector>
#include"trienode.h"
using namespace std;

namespace Library {
	struct triebuffer {
	// A buffer between the .trie file and an array of trienodes

		// A pointer to the file object the buffer is associated with
		fstream* file;
		// A buffer of constant length 10 of the trienode objects at
		// the current position in the file
		// (I.e. an interpretation of the next sizeof(trienode) * 10 bytes
		trienode* buffer;
		// The file path
		string filePath;
	/*************************************************
	* FUNCTION
	*    constructor
	* PARAMETERS
	*    The path to the file
	* RETURN VALUE
	*    A triebuffer object initialized with default data
	**************************************************/
		triebuffer(string path);
	/*************************************************
	* FUNCTION
	*    copy constructor
	* PARAMETERS
	*    triebuffer& other - A triebuffer reference
	* RETURN VALUE
	*    A copy of the triebuffer object passed
	* MEANING
	*     Copies every member of the passed object deeply
	*     (I.e. the fstream object is not copied, but recreated)
	**************************************************/
		triebuffer(const triebuffer&);
	/*************************************************
	* FUNCTION
	*    get_pos
	* RETURN VALUE
	*    The current position in the file in characters
	**************************************************/
		ios::pos_type get_pos();
	/*************************************************
	* FUNCTION
	*    get_block
	* RETURN VALUE
	*    The current position in the file in trienodes
	**************************************************/
		long get_block();
	/*************************************************
	* FUNCTION
	*    operator[]
	* PATAMETERS
	*    long idx - The serial number of the node
	* RETURN VALUE
	*    The node with the given serial number
	* SIDE EFFECTS
	*    If the node is not in the buffer, the buffer will
	*    be updated to contain the 10 nodes, including
	*    the requested node, at the closest multiple of 10
	*    (I.e. requesting for #1234, if it isn't in the buffer,
	*    updates the buffer to include #1230-#1239)
	**************************************************/
		trienode& operator[](long idx);
	/*************************************************
	* FUNCTION
	*    read
	* PATAMETERS
	*    ios::pos_type idx - The location to read from
	**************************************************/
		void read(ios::pos_type idx);
	/*************************************************
	* FUNCTION
	*    write
	* MEANING
	*    Write the current buffer to the file
	**************************************************/
		void write();
	/*************************************************
	* FUNCTION
	*    open_file
	* PATAMETERS
	*    bool append - Whether to open the file in append mode
	*                  or empty it
	* MEANING
	*    Opens the file for I/O, in binary mode, with append as specified
	*    by the parameter.
	*    The get/put pointers will be located at the beginning of the file
	* THROWS
	*    Couldn't open .trie file _filePath_ - if there were errors when opening the file
	**************************************************/
		void open_file(bool append = false);
	/*************************************************
	* FUNCTION
	*    open_file
	* PATAMETERS
	*    string path - The path to the file to be written
	*    bool append - Whether to open the file in append mode
	*                  or empty it
	* MEANING
	*    Calls open_file(bool) on the file passed if its a valid path, or filePath otherwise
	* SIDE EFFECTS
	*    Assigns filePath to the passed path if its valid
	**************************************************/
		void open_file(string path,bool append = false);
	/*************************************************
	* FUNCTION
	*    file_size
	* RETURN VALUE
	*    The amount of trienodes in the file
	**************************************************/
		long  file_size();
	/*************************************************
	* FUNCTION
	*    destructor
	* MEANING
	*    Closes the file and deallocates the buffer
	**************************************************/
		~triebuffer();
	private:
		triebuffer(); // We don't want the user to be able
		              // to create a triebuffer unassociated
		              // with any file
	};
}

