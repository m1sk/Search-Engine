#include "stdafx.h"
#include "triebuffer.h"
using namespace Library;

triebuffer::triebuffer(string path)
	: buffer(),
	filePath(path),
	file(new fstream())
{
	for(int i = 0; i < 10; ++i)
		buffer.push_back(trienode(i));
}
triebuffer::triebuffer(const triebuffer& other)
	: buffer(other.buffer),
	filePath(other.filePath),
	file(new fstream())
{}

long triebuffer::block(long idx)
{
	return (idx/10)*10;
}

trienode& triebuffer::operator[](long idx)
{
	if((block(idx)) != (block(buffer[0].nodeserialnr))) {
		write();
		read(idx);
	}

	return buffer[idx % 10];
}

void triebuffer::read(ios::pos_type idx)
{
	if(!file->is_open())
		open_file();
	extend_to(idx);
	for(long i = 0; i < 10; ++i)
		buffer[i] = trienode::read(block(idx) + i,
							reinterpret_cast<ifstream*>(file));
}

void triebuffer::write()
{
	if(!file->is_open())
		open_file();
	extend_to(block(buffer[0].nodeserialnr));
	for(long i = 0; i < 10; ++i)
		trienode::write(buffer[i], reinterpret_cast<ofstream*>(file));
	file->close();
	file->open(filePath, ios::binary | ios::out | ios::in | ios::ate);
}

void triebuffer::open_file()
{
	fstream(filePath, ios::app).close(); // Create the file if it doesn't exist
	file->open(filePath, ios::binary | ios::out | ios::in | ios::ate);
	if(!file->is_open())
		throw FileException("Couldn't open .trie file " + filePath);
	if(file_size(filePath) == 0)
		extend_to(0);
	file->close();
	file->open(filePath, ios::binary | ios::out | ios::in | ios::ate);
}

void triebuffer::extend_to(ios::pos_type idx)
{
	long max = block(idx) + 9;
	long end = file_size(filePath)/sizeof(trienode) - 1;
	if(max <= end)
		return;
	for(++end; end <= max; ++end)
		trienode::write(trienode(end), reinterpret_cast<ofstream*>(file));
}

triebuffer::~triebuffer()
{
	write();
	delete file;
}
