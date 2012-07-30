#include "triebuffer.h"
// Debugging
//#include <iostream>
//using std::cerr;
using namespace Library;

triebuffer::triebuffer(string path)
{
// Debugging
//	cerr << "Building object " << this << " with path " << path << "\n";
	buffer = new trienode [10];
	filePath = path;
	file = new fstream();
}
triebuffer::triebuffer(const triebuffer& other)
{
// Debugging
//	cerr << "Copying object " << &other << "\npath: " << other.filePath << "\n";
	buffer = new trienode [10];
	filePath = other.filePath;
	file = new fstream();
	for(long i = 0; i < 10; ++i)
		buffer[i] = other.buffer[i];
}

ios::pos_type triebuffer::get_pos()
{
	return buffer[0].nodeserialnr * sizeof(trienode);
}

long triebuffer::get_block()
{
	return buffer[0].nodeserialnr;
}

trienode& triebuffer::operator[](long idx)
{
	if((idx/10) != (get_block()/10))
	{
		write();
		file->seekp((idx/10)*10*(sizeof trienode));
		read(idx);
	}

	return buffer[idx % 10];
}

void triebuffer::read(ios::pos_type idx)
{
	if(!file->is_open())
		open_file(true);
	file->seekg((idx/10)*10*(sizeof trienode));
	file->read((char*)buffer, 10*(sizeof trienode));
	if(file->eof()) {
		for(std::streamsize i = file->gcount()/(sizeof trienode) - 1;
			i < 10; ++i)
			buffer[i] = trienode();
		file->clear();
		write();
	}
// Debugging
//	for(long i = 0; i < 10; ++i)
//		cerr << "Read: " << buffer[i].nodeserialnr << ' ' << buffer[i].letter << '\n';
//	cerr << '\n';
}

void triebuffer::write()
{
	if(!file->is_open())
		open_file();
	file->seekp(get_pos());
	file->write((char*) buffer,10*sizeof(trienode));
}

void triebuffer::open_file(bool append)
{
	fstream(filePath, ios::app).close(); // Create the file if it doesn't exist
	file->open(filePath, ios::binary | ios::out | ios::in | (append? ios::app : 0));
	if(file->tellg() / (sizeof trienode) == 0)
	{
		for(long i = 0; i < 10; ++i)
			buffer[i] = trienode();
		write();
	}
	if(!file->is_open())
		throw exception(("Couldn't open .trie file " + filePath).c_str());
	file->seekp(0);
	file->seekg(0);
}
void triebuffer::open_file(string path, bool append)
{
	if(!(path == ""))
		filePath = path;
	open_file(append);
}

long triebuffer::file_size()
{
	fstream tmp(filePath, ios::in | ios::binary | ios::ate);
// Debugging
//	cerr << "file size: " << file->tellg() << "\nsize of trienode: " << sizeof(trienode)
//		<< "\nsize of long: " << sizeof(long) << "\nrecord count: " << ret << "\n";
	return (long)(tmp.tellg() / sizeof(trienode));
}

triebuffer::~triebuffer()
{
	// Debugging
	// cerr<<"Destructor of "<< this << "\npath: " << filePath;
	write();
	delete [] buffer;
	delete file;
}

