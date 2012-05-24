#include "trienode.h"
#include <sstream>

using namespace Library;

//long trienode::lastserialnr = 0;

trienode::trienode()
	: nodeserialnr(0),
	firstoffset(0),
	letter('\0'),
	wordend(false)
{for (long i = 0; i < LINKS_LENGTH; ++i) links[i] = NULL_LINK;}

trienode::trienode(long _firstoffset,
	long _nrofoccurences, unsigned char _letter,
	bool _wordend,long serialnr)
	: nodeserialnr(serialnr),
	firstoffset(_firstoffset),
	nrofoccurences(_nrofoccurences),
	letter(_letter),
	wordend(_wordend)
{for (long i = 0; i < LINKS_LENGTH; ++i) links[i] = NULL_LINK;}

long trienode::operator[](char c)
{
	return links[(long) c];
}

void trienode::set_link(char idx, long val)
{
	links[idx] = val;
}

void trienode::print_node() const
{
	//print function modified from oshi cohen code
	printf("\n #################\n");
printf(" # serial: %-6i#\n",nodeserialnr);
printf(" # letter: %-6c#\n",letter);
printf(" # offset: %-6i#\n",firstoffset);
printf(" # count:  %-6i#\n",(nrofoccurences <= 0? 0:nrofoccurences));
printf(" # end?:   %-6i#\n",wordend);
printf(" #---------------#\n");
for(long j=0 ; j<256;j++)
if(links[j]!=-1)
printf(" #%6c->%-6i #\n",j,links[j]);
printf(" #################\n");
}