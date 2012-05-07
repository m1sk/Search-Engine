#include "trienode.h"
#include <limits>

using namespace Library;

long trienode::lastserialnr = 0;

trienode::trienode()
	: nodeserialnr(0),
	firstoffset(0),
	letter('\0'),
	wordend(false)
{for (int i = 0; i < LINKS_LENGTH; ++i) links[i] = NULL_LINK;}

trienode::trienode(long _firstoffset,
	long _nrofoccurences, unsigned char _letter,
	bool _wordend)
	: nodeserialnr(++lastserialnr),
	firstoffset(_firstoffset),
	nrofoccurences(_nrofoccurences),
	letter(_letter),
	wordend(_wordend)
{for (int i = 0; i < LINKS_LENGTH; ++i) links[i] = NULL_LINK;}

long trienode::operator[](char c)
{
	return links[(int) c];
}

void trienode::set_link(long idx, long val)
{
	links[idx] = val;
}

inline int long_length(){
	return 0;//strlen(itoa(LONG_MAX, NULL, 10));
}
/*
string trienode::serialize(trienode conv){
/*	string padded_long = "%0(" + long_length() + ")ld";
	string serial;
	sprintf(serial, padded_long + padded_long + padded_long + "%c" + padded_long,
		conv.nodeserialnr,conv.firstoffset,conv.nrofoccurences,conv.letter,conv.wordend);
	for(int i = 0; i < LINKS_LENGTH; ++i){
		serial += conv.links[i];
	}
	return serial;///
	return string();
}

trienode trienode::deserialize(string conv){return trienode();}
*/