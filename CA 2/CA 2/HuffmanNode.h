#pragma once
#include<iostream>
#include<vector>
#include<string>
using namespace std;

class HuffmanNode {
	friend class HuffmanTree;
public:
	HuffmanNode() {
		// Default constructor	
	}
	HuffmanNode(char contentIn, int freqIn) { // Overloaded contructor
		content = contentIn;
		frequency = freqIn;
		leftChild = rightChild = NULL;
	}
	int getFreq(){ // Public method to return frequency
		return frequency;
	}
private:
	// Variables, two child nodes, the frequency, the character and the code for the tree traversal
	HuffmanNode *leftChild;
	HuffmanNode *rightChild;
	int frequency;
	char content;
	string code;
};