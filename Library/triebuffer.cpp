#include "triebuffer.h"

using namespace Library;

triebuffer::triebuffer(void)
{
	file = fstream();
	path = string();
	for (int i = 0; i < 10; ++i)
	{
		buffer[i] = trienode();
	}
}


triebuffer::~triebuffer(void)
{
}
