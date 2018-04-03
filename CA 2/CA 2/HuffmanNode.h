#pragma once
#include<iostream>
#include<vector>
#include<string>
using namespace std;

class HuffmanNode {
	friend class HuffmanTree;
public:
	HuffmanNode() {
		
	}
	HuffmanNode(char contentIn, int freqIn) {
		content = contentIn;
		frequency = freqIn;
	}
	int getFreq(){
		return frequency;
	}
private:
	HuffmanNode *leftChild;
	HuffmanNode *rightChild;
	int frequency;
	char content;
	string code;
};