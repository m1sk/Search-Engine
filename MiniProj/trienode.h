#pragma once
class trienode
{
private:
	long nodeserialnr;
	long firstoffset;
	long nrofoccurences;
	unsigned char letter;
	bool wordend;
	unsigned char links [256];
public:
	trienode(void);
	~trienode(void);
};

