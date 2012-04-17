#include "triebuffer.h"

using namespace Library;

triebuffer::triebuffer()
	: file(NULL), path(), buffer(10, trienode())
	{}

triebuffer::~triebuffer()
{
}
