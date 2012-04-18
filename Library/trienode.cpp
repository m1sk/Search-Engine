#include "trienode.h"
#include <limits>

using namespace Library;

trienode::trienode()
	: nodeserialnr(0),
	firstoffset(0),
	letter('\0'),
	wordend(false)
{for (int i = 0; i < LINKS_LENGTH; ++i) links[i] = NULL_LINK;}

trienode::trienode(long _nodeserialnr, long _firstoffset,
	long _nrofoccurences, unsigned char _letter,
	bool _wordend, long int _links [LINKS_LENGTH])
	: nodeserialnr(_nodeserialnr),
	firstoffset(_firstoffset),
	nrofoccurences(_nrofoccurences),
	letter(_letter),
	wordend(_wordend)
{for (int i = 0; i < LINKS_LENGTH; ++i) links[i] = _links[i];}


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