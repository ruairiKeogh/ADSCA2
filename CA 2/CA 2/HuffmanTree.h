#pragma once
#include<iostream>
#include<vector>
#include<string>
#include "HuffmanNode.h"
#include <queue>
using namespace std;

struct compare {
	bool operator()(HuffmanNode * l, HuffmanNode * r) {
		return(l->getFreq() > r->getFreq());
	}
};

class HuffmanTree{
	
public:
	HuffmanTree();
	~HuffmanTree();
	int getFreq();
	void HuffmanCode();
private:
	HuffmanNode * root;
	HuffmanTree(const HuffmanTree &);
	void print(HuffmanNode *node, int) const;
	priority_queue <HuffmanNode, vector<HuffmanNode>, compare > min_heap;
	void HuffmanCode(char data[], int freq[], int size);
};

