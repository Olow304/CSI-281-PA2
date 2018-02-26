#ifndef HUFFMAN_H
#define HUFFMAN_H

#include <iostream>
#include <fstream>
#include <queue>
#include <fstream>
#include <string>
#include <unordered_map>

using namespace std;

struct Tree
{
	Tree() { leftNode = rightNode = NULL; };
	Tree(string letters, int letterFreq, Tree* leftChild, Tree* rightChild);
	~Tree() { delete leftNode, rightNode; }
	
	string	encodedChars;
	int		charFreq;
	Tree*	leftNode;
	Tree*	rightNode;
	
	/*
	ERROR: C2664
	- bool Tree::operator ()(const Tree *&,const Tree *&) const':
		- cannot convert argument 1 from 'Tree *' to 'const Tree *&'
	- if I change it to 'Tree *', it crashes with Linker errors.
	*/

	// Source: https://stackoverflow.com/questions/19535644/how-to-use-the-priority-queue-stl-for-objects
	bool operator()(const Tree* &tree1, const Tree* &tree2) const
	{
		return tree1->charFreq < tree2->charFreq; // watch the sign
	}
};


/*
Data structures used in this project:
- Priority queue: stores forest of Trees, takes the Tree with the smallest value and adds to the Huffman Tree.
- Tree: Starts out with each character having its own Tree, stored in priority queue.
- Huffman Tree: Tree constructed from forest of trees in the priority queue
- Unordered Lists: Stores the codes of the individual letters in one of them, and the codes of the edges in the other.
*/

unordered_map<string, int> charFreqs;
unordered_map<string, string> huffmanSequence;

priority_queue<Tree*, vector<Tree*>, Tree> huffForest;

string encodeCharacters(Tree* root, string &byteString);
string getEncoding();

void decodeCharacters(const Tree* root, int &huffCodeIndex, string byteString);
void createHuffmanTree();
void addToMap(string data);
void decodeTree(string byteString);
#endif