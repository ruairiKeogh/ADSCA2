#pragma once
#include<iostream>
#include<vector>
#include<string>
using namespace std;

class HuffmanNode {
	friend class HuffmanTree;
public:
	HuffmanNode();
	int getFreq(){
		return frequency;
	}
private:
	HuffmanNode * leftChild;
	HuffmanNode *rightChild;
	int frequency;
	string content;
	string code;
};