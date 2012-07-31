#include "trienode.h"
#include <sstream>

using namespace Library;

trienode::trienode(long serialnr, long _firstoffset,
	long _nrofoccurences, unsigned char _letter,
	bool _wordend)
	: nodeserialnr(serialnr),
	firstoffset(_firstoffset),
	nrofoccurences(_nrofoccurences),
	letter(_letter),
	wordend(_wordend)
{for (long i = 0; i < LINKS_LENGTH; ++i) links[i] = INVALID_NODE;}

long& trienode::operator[](char c) { return links[(long) c]; }

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
if(links[j] != INVALID_NODE)
printf(" #%6c->%-6i #\n",j,links[j]);
printf(" #################\n");
}

void trienode::write(trienode& node, ofstream* file)
{
	file->seekp(node.nodeserialnr * sizeof(trienode));
	file->write(reinterpret_cast<const char *>(&node), sizeof(trienode));
}

trienode trienode::read(const long serialnr, ifstream* file)
{
	trienode node(serialnr);
	file->seekg(node.nodeserialnr * sizeof(trienode));
	file->read(reinterpret_cast<char *>(&node), sizeof(trienode));
	return node;
}