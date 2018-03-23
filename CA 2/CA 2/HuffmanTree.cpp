#include<iostream>
#include<vector>
#include<string>
#include "HuffmanTree.h"
#include <queue>
#include <map>
using namespace std;

HuffmanTree::HuffmanTree() {

}

void HuffmanTree::build(map <char, int> &freq) {
	HuffmanNode *left, *right, *top;
	
	for (auto elem : freq)
	{
		HuffmanNode *node = new HuffmanNode();;
		node->content = elem.first;
		node->frequency = elem.second;
		min_heap.push(node);
	}

	while (min_heap.size() != 1) {
		// Extract the two minimum
		// freq items from min heap
		left = min_heap.top();
		min_heap.pop();

		right = min_heap.top();
		min_heap.pop();


		top = new HuffmanNode("$", left->frequency + right->frequency);

		top->leftChild = left;
		top->rightChild = right;

		min_heap.push(top);
	}

	printCodes(min_heap.top(), "");
}

void HuffmanTree::printCodes(HuffmanNode* root, string str)
{
	
	if (!root)
		return;

	if (root->content != "$")
		cout << root->content << ": " << str << "\n";

	printCodes(root->leftChild, str + "0");
	printCodes(root->rightChild, str + "1");
	if (root->content != "$") {
		string code = str;
		root->code = code;
		cout << "Stored Code for: " << root->content << " is: " << root->code << "\n";
	}
		
}


map <char, int> HuffmanTree::mapCodes(HuffmanNode *root) {

}