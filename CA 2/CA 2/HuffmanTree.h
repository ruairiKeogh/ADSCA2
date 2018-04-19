#pragma once
#include<iostream>
#include<vector>
#include<string>
#include "HuffmanNode.h"
#include <queue>
#include <map>
using namespace std;

struct compare {
	bool operator()(HuffmanNode * l, HuffmanNode * r) { // Compare utility method for the min heap to be able to compare two nodes
		return(l->getFreq() > r->getFreq());
	}
};

class HuffmanTree{
	
public:
	map<char, string> mappings = map<char,string>();	// map of the character and its code for tree traversal
	HuffmanTree();										// Default constructor
	void build(map <char, int> &freq);					// Build method to create the tree and encode file
	void decode();										// Decode method to decode an encoded file
	void compress();									// Compress file takes 8 bits and converts to ascii
	void decompress();									// Decompresses ascii back to an encoded file
private:
	HuffmanNode * root; // Pointer to top of tree
	priority_queue <HuffmanNode*, vector<HuffmanNode*>, compare > min_heap; // Min heap for the tree
	map<char,string> printCodes(HuffmanNode *root,string str);				// Utility method used to print and set the codes of each character
	void encode(map<char, string> &mappings);								// Encodeds file to a set of ones and zeros based on codes for tree traversal
	void decode(HuffmanNode *root, ifstream &file, ofstream &newFile);		// Decode ones and zeros back to original ascii characters
	
};

