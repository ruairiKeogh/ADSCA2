#include<iostream>
#include <fstream> 
#include<vector>
#include<string>
#include "HuffmanTree.h"
#include <queue>
#include <map>
#include <bitset>
using namespace std;

HuffmanTree::HuffmanTree() {

}

/***************************************************************************************
*    Title: <Greedy Algorithms | Set 3 (Huffman Coding)>
*    Author: <GeeksforGeeks>
*    Date: <NA>
*    Code version: <C++11:>
*    Availability: <https://www.geeksforgeeks.org/greedy-algorithms-set-3-huffman-coding/>
*
***************************************************************************************/
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

	file.close();
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

	file.close();
	newFile.close();
}

/***************************************************************************************
*    Title: <Convert a string of binary into an ASCII string (C++)>
*    Author: <Dale Wilson>
*    Date: <Apr 28 '14 at 15:19>
*    Code version: <C++11:>
*    Availability: <https://stackoverflow.com/questions/23344257/convert-a-string-of-binary-into-an-ascii-string-c>
*
***************************************************************************************/

void HuffmanTree::compress() {
	ifstream file("encoded.txt");
	ofstream outFile("compressed.txt");
	
	while (file.good()) {
		bitset<8> bits;
		file >> bits;
		char c = char(bits.to_ulong());
		outFile << c;
	}
	outFile << '¨';
	
	outFile.close();
	file.close();
}

/***************************************************************************************
*    Title: <Convert a string of binary into an ASCII string (C++)>
*    Author: <Dale Wilson>
*    Date: <Apr 28 '14 at 15:19>
*    Code version: <C++11:>
*    Availability: <https://codereview.stackexchange.com/questions/2661/simple-text-to-binary-converter-written-in-c>
*
***************************************************************************************/
void HuffmanTree::decompress() {
	ifstream file("compressed.txt");
	ofstream newFile("decompressed.txt");
	char c;
	
	while (file.get(c)) {
		if (c == '¨') {
			newFile.close();
			file.close();

			ifstream decFile("decompressed.txt");
			ofstream lastFile("LastFile.txt");
			decode(root, decFile, lastFile);

			decFile.close();
			lastFile.close();
			return;
		}
		bitset <8> binary(c);
		newFile << binary;
	}
	newFile.close();
	file.close();

	ifstream decFile("decompressed.txt");
	ofstream lastFile("LastFile.txt");
	decode(root, decFile,lastFile);

	decFile.close();
	lastFile.close();
}