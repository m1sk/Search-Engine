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
	return (buffer[0].nodeserialnr/10) * 10 * sizeof(trienode);
}

long triebuffer::get_pos_nr()
{
	return (buffer[0].nodeserialnr/10) * 10;
}

trienode& triebuffer::get_node(long idx)
{
	if((idx/10) != (get_pos_nr()/10))
	{
		//write();
		file->seekp((idx/10)*10);
		read(idx);
	}

	return buffer[idx % 10];
}

void triebuffer::read(ios::pos_type idx)
{
	if(!file->is_open())
		open_file(true);
	file->seekg((idx/10)*10);
	file->read((char*)buffer, 10*(sizeof trienode));
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
	fstream(filePath, ios::app).close();
	file->open(filePath, ios::out | ios::binary | ios::in | (append? ios::app : 0));
	/*if(file->tellg() / (sizeof trienode) == 0)
	{
		for(long i = 0; i < 10; ++i)
			buffer[i] = trienode();
		write();
	}/**/
	if(!file->is_open())
	{
		cerr << "errno"<<strerror(errno)<<endl;
		throw exception(("Couldn't open .trie file " + filePath).c_str());
	}
	file->seekp(0);
	file->seekg(0);
}
void triebuffer::open_file(string path, bool append)
{
	if(!(path == ""))
	{
		filePath = path;
	}
	open_file(append);
}
void triebuffer::close_file()
{
		file->close();
}

long triebuffer::file_size()
{
	close_file();
	file->open(filePath, ios::in | ios::binary | ios::ate);
	long ret = (long)(file->tellg() / sizeof(trienode));
// Debugging
//	cerr << "file size: " << file->tellg() << "\nsize of trienode: " << sizeof(trienode)
//		<< "\nsize of long: " << sizeof(long) << "\nrecord count: " << ret << "\n";
	close_file();
	open_file(true);
	return ret;
}

triebuffer::~triebuffer()
{
	// Debugging
	// cerr<<"Destructor of "<< this << "\npath: " << filePath;
	delete [] buffer;
	if(file->is_open())
		close_file();
	delete file;
}
