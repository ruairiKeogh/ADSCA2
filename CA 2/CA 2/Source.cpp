#include <iostream>
#include <map>
#include <fstream>
#include <string>
#include <queue>
#include "HuffmanTree.h"

using namespace std;

void calcFreq(map <char,int> &freq, ifstream &file);
void print(map <char, int> &freq);

int main() {
	ifstream file ("testText.txt");
	map<char, int> freqs = map<char, int>();
	calcFreq(freqs, file);

	print(freqs);

	HuffmanTree newTree;

	newTree.build(freqs);

	newTree.decode();
	
	system("Pause");
	return 0;
}

// Part 1. Calculating frequency of each character and storing to map of char and int.
// Referenced from GLalor GitHub account RIP
void calcFreq(map <char, int> &freq, ifstream &file) {
	char c;
	while (file.get(c)) {
		if (!freq.empty()) {
			auto item = freq.find(c);
			if (item != freq.end()) {
				item->second++;
			}
			freq.insert(pair<char, int >(c, 1));
		}
		else {
			freq.insert(pair<char, int >(c, 1));
		}
	}
}

void print(map <char, int> &freq) {
	for (auto elem : freq)
	{
		cout << elem.first << " " << elem.second << "\n";
	}
}