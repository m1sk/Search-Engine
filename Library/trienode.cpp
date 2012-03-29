#include "trienode.h"
#include <limits>

using namespace Library;

trienode::trienode(void)
{
}


trienode::~trienode(void)
{
}

inline int long_length(){
	return 0;//strlen(itoa(LONG_MAX, NULL, 10));
}

string trienode::serialize(trienode conv){
/*	string padded_long = "%0(" + long_length() + ")ld";
	string serial;
	sprintf(serial, padded_long + padded_long + padded_long + "%c" + padded_long,
		conv.nodeserialnr,conv.firstoffset,conv.nrofoccurences,conv.letter,conv.wordend);
	for(int i = 0; i < LINKS_LENGTH; ++i){
		serial += conv.links[i];
	}
	return serial;*/
	return string();
}

trienode trienode::deserialize(string conv){return trienode();}