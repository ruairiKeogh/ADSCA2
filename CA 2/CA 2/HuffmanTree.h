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
	map<char, string> mappings = map<char,string>();
	HuffmanTree();
	void build(map <char, int> &freq);
	void decode();
private:
	HuffmanNode * root;
	priority_queue <HuffmanNode*, vector<HuffmanNode*>, compare > min_heap;
	void HuffmanCode(char data[], int freq[], int size);
	map<char,string> printCodes(HuffmanNode *root,string str);
	void encode(map<char, string> &mappings);
	void decode(HuffmanNode *root, ifstream &file, ofstream &newFile);
};

