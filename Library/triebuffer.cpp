#include "triebuffer.h"
using namespace Library;

triebuffer::triebuffer(string path)
{
	buffer = new trienode [10];
	filePath = path;
	file = new fstream();
}
triebuffer::triebuffer(const triebuffer& other)
{
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
	if((idx/10) != (get_block()/10)) {
		write();
		file->seekp((idx/10)*10*sizeof(trienode));
		read(idx);
	}

	return buffer[idx % 10];
}

void triebuffer::read(ios::pos_type idx)
{
	if(!file->is_open())
		open_file(true);
	file->seekg((idx/10)*10*sizeof(trienode));
	file->read((char*)buffer, 10*sizeof(trienode));
		<< file_size() << " trienodes\n";
	if(file->eof()) {
		for(std::streamsize i = file->gcount()/sizeof(trienode) - 1;
			i < 10; ++i)
			buffer[i] = trienode();
		file->clear();
		write();
	}
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
	file->open(filePath, ios::binary | ios::out | ios::in
		| (append? ios::app : (ios_base::openmode) 0));
	if(!file->is_open())
		throw FileException("Couldn't open .trie file " + filePath);
	if(file_size() == 0) {
		for(long i = 0; i < 10; ++i)
			buffer[i] = trienode();
		write();
	}
	file->seekp(0);
	file->seekg(0);
}
void triebuffer::open_file(string path, bool append)
{
	if(path != "")
		filePath = path;
	open_file(append);
}

long triebuffer::file_size()
{
	return (long)(fstream(filePath, ios::in | ios::binary | ios::ate)
		.tellg() / sizeof(trienode));
}

triebuffer::~triebuffer()
{
	write();
	delete [] buffer;
	delete file;
}

