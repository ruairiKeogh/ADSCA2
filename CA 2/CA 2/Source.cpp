#include <iostream>
#include <map>
#include <fstream>
#include <string>
#include <queue>
#include "HuffmanTree.h"

using namespace std;

// utility methods
void calcFreq(map <char,int> &freq, ifstream &file);
void print(map <char, int> &freq);

int main() {
	ifstream file ("testText.txt"); // Open text file
	char eof = '¨';
	map<char, int> freqs = map<char, int>(); // Create map of characters and there frequencies
	freqs.insert(pair<char, int>(eof, 1));
	calcFreq(freqs, file); // Call utility method to calculate frequencies

	print(freqs); // Print the frequencies for debugging purposes

	HuffmanTree newTree; // Create a new tree

	newTree.build(freqs); // Build and encode the tree

	newTree.decode(); // Decode the encoded file
	
	newTree.compress();	// Compress the encoded file

	newTree.decompress(); // Decompress and decode the compressed file
	// Close file
	file.close();
	system("Pause");
	return 0;
}

// Part 1. Calculating frequency of each character and storing to map of char and int.
/***************************************************************************************
*    Title: <Counting characters in the given string using C++ STL map>
*    Author: <Ravi Chandra Enaganti>
*    Date: <Tuesday, May 7, 2013>
*    Code version: <C++11:>
*    Availability: <http://comproguide.blogspot.ie/2013/05/counting-characters-in-given-string.html>
*
***************************************************************************************/
void calcFreq(map <char, int> &freq, ifstream &file) {
	char c;
	while (file.get(c)) { // Loop through the file getting each character
		if (!freq.empty()) { // when the map for frequency isn't empty
			auto item = freq.find(c); // Try find the character from file in the map
			if (item != freq.end()) { // If its in the map increment it's frequency
				item->second++;
			}
			// Else add to the map
			freq.insert(pair<char, int >(c, 1));
		}
		else { // If the map is empty add to the map
			freq.insert(pair<char, int >(c, 1));
		}
	}
}

void print(map <char, int> &freq) {
	for (auto elem : freq)
	{ // Loop throught the map and print each character and its frequency
		cout << elem.first << " " << elem.second << "\n";
	}
}