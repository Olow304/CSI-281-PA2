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
};

// Source: https://stackoverflow.com/questions/19535644/how-to-use-the-priority-queue-stl-for-objects
struct compareTrees
{
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
// Define them here so that we can access them from functions.cpp
unordered_map<string, int> charFreqs;
unordered_map<string, string> huffmanSequence;
priority_queue<Tree*, vector<Tree*>, compareTrees> huffForest;

void encode_characters(Tree* root, string byteString);
void decode_characters(Tree* root, int &huffCodeIndex, string byteString);
void create_huff();

void addToMap(string data);
void codeTree();