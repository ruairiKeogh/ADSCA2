#include<iostream>
#include <fstream> 
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
	map<char, string> mappings = map<char, string>();

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


		top = new HuffmanNode('$', left->frequency + right->frequency);

		top->leftChild = left;
		top->rightChild = right;

		min_heap.push(top);
	}
	root = min_heap.top();
	mappings = printCodes(min_heap.top(), "");

	encode(mappings);
}

map <char, string> HuffmanTree::printCodes(HuffmanNode* root, string str)
{
	if (!root)
		return mappings;

	if (root->content != '$')
		cout << root->content << ": " << str << "\n";

	printCodes(root->leftChild, str + "0");
	printCodes(root->rightChild, str + "1");
	if (root->content != '$') {
		string code = str;
		root->code = code;
		mappings.insert(pair<char, string>(root->content, root->code));
		cout << "Stored Code for: " << root->content << " is: " << root->code << "\n";
	}

	return mappings;
}

void HuffmanTree::encode(map<char,string> &mappings) {
	ifstream file("testText.txt");
	ofstream outfile("encoded.txt");
	char c;
	while (file.get(c)) {
		for (auto elem : mappings) {
			if (c == elem.first) {
				outfile << elem.second;
			}
		}
	}

	outfile.close();
}

void HuffmanTree::decode() {
	ifstream file("encoded.txt");
	ofstream newFile("decoded.txt");
	decode(root, file, newFile);
}

void HuffmanTree::decode(HuffmanNode *root, ifstream &file, ofstream &newFile) {
	char c;
	HuffmanNode *curr = root;
	while (file.get(c)) {
		if (c == '0') {
			curr = curr->leftChild;
		}
		else if (c == '1') {
			curr = curr->rightChild;
		}

		if (curr->leftChild == NULL && curr->rightChild == NULL) {
			newFile << curr->content;
			curr = root;
		}
	}

	newFile.close();
}