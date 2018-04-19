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
	HuffmanNode *left, *right, *top; // Temporary pointers fr children nodes and a root node
	map<char, string> mappings = map<char, string>(); // Map for characters and its code

	for (auto elem : freq)
	{ // Loop through each character in the frequency map and add to the min heap
		HuffmanNode *node = new HuffmanNode();;
		node->content = elem.first;
		node->frequency = elem.second;
		min_heap.push(node);
	}

	while (min_heap.size() != 1) {
		// Extract the two minimum frequency nodes from min heap
		left = min_heap.top();
		min_heap.pop();

		right = min_heap.top();
		min_heap.pop();

		// Create a new node to act as the parent for the two minimum nodes with a frequency of both added together
		top = new HuffmanNode('$', left->frequency + right->frequency); // Marker character for a parent node is $
		// Set the pointers to the children nodes.
		top->leftChild = left;
		top->rightChild = right;

		min_heap.push(top); // Add to the min heap
	}

	root = min_heap.top(); // Set the root node to the top of the min heap, this should have a frequency of all the characters frequencies added together
	mappings = printCodes(root, ""); // Call print codes method to set the mappings and to set the codes for each character.

	encode(mappings); // call encode method and pass the mappings
}

map <char, string> HuffmanTree::printCodes(HuffmanNode* root, string str)
{
	if (!root)
		return mappings; // base case if root is null 

	if (root->content != '$') // If the content is not the marker
		cout << root->content << ": " << str << "\n"; // print content and string,

	printCodes(root->leftChild, str + "0"); // Recursive call to left nodes, if left add 0 to the string
	printCodes(root->rightChild, str + "1");// Recursive call to right nodes, if right add 1 to the string
	if (root->content != '$') {// If the content is not the marker
		string code = str;
		root->code = code; // Set the code to the string that has been added to with 0's and 1's
		mappings.insert(pair<char, string>(root->content, root->code)); // insert to the map the character and its code
		cout << "Stored Code for: " << root->content << " is: " << root->code << "\n"; // Output to console the character
	}

	return mappings; // Return the map collection
}

void HuffmanTree::encode(map<char,string> &mappings) {
	ifstream file("testText.txt"); // File to be read in
	ofstream outfile("encoded.txt"); // File to be output to
	char c;
	while (file.get(c)) { // Loop and get each character until no characters left
		for (auto elem : mappings) { // Loop for each character in the map
			if (c == elem.first) { // If the character in map matches the character from file
				outfile << elem.second; // Output to the file the characters code
			}
		}
	}
	// Close files
	file.close();	
	outfile.close();
}

void HuffmanTree::decode() { // Public decode method opens two files and passes to root and files to decode private
	ifstream file("encoded.txt");
	ofstream newFile("decoded.txt");
	decode(root, file, newFile);
}

void HuffmanTree::decode(HuffmanNode *root, ifstream &file, ofstream &newFile) {
	char c;
	HuffmanNode *curr = root; // set current node to the node passed in
	while (file.get(c)) { // Loop while getting each character from the file
		if (c == '0') { // If the character is a 0 move left in the tree
			curr = curr->leftChild;
		}
		else if (c == '1') { // If the character is a 1 move right in the tree
			curr = curr->rightChild;
		}

		if (curr->leftChild == NULL && curr->rightChild == NULL) { // If the node is a leaf node output the character to the new file
			if (curr->content == '¨') {
				return;
			}
			newFile << curr->content;
			curr = root; // Go back to the root of the tree.
		}
	}
	// Close files
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
	// Open in file and out file
	ifstream fileIn("encoded.txt");
	ofstream outFile("compressed.txt");

	while (fileIn.good()) { // Loop while the file has not reached the end
		bitset<8> bits; // Bitset to take 8 bits from the file
		fileIn >> bits;
		char c = char(bits.to_ulong()); // Convert 8 bits to an ascii character
		outFile << c; // Output ascii to the out file
	}
	outFile << '¨'; // End of file marker
	// Close files
	outFile.close();
	fileIn.close();
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
	// Open files to read in from and output to
	ifstream file("compressed.txt");
	ofstream newFile("decompressed.txt");
	char c;
	
	while (file.get(c)) { // Read in each character from the file
		// Else convert to a bitset of 8 bits and pass to the newfile
		bitset <8> binary(c);
		newFile << binary;
	}
	// Close files
	newFile.close();
	file.close();

	// Open new files for decoding back to the original file
	ifstream decFile("decompressed.txt");
	ofstream lastFile("LastFile.txt");
	// Decode to the original file
	decode(root, decFile,lastFile);

	// Close files
	decFile.close();
	lastFile.close();
}