#pragma once
#include<iostream>
#include<vector>
#include<string>
#include "HuffmanNode.h"
#include <queue>
#include <map>
using namespace std;

struct compare {
	bool operator()(HuffmanNode * l, HuffmanNode * r) {
		return(l->getFreq() > r->getFreq());
	}
};

class HuffmanTree{
	
public:
	HuffmanTree();
	void build(map <char, int> &freq);
	map <char, int> mapCodes(HuffmanNode *root);
private:
	HuffmanNode * root;
	priority_queue <HuffmanNode*, vector<HuffmanNode*>, compare > min_heap;
	void HuffmanCode(char data[], int freq[], int size);
	void printCodes(HuffmanNode *root,string str);
};

