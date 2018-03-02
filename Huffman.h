#pragma once
#include <iostream>
#include <fstream>
#include <queue>
#include <string>
#include <unordered_map>

using namespace std;

struct Tree
{
	Tree() { leftNode = NULL; rightNode = NULL; };
	Tree(string letters, int letterFreq, Tree* leftChild, Tree* rightChild);
	Tree(string letters, int letterFreq, Tree leftChild, Tree rightChild);
	~Tree() { delete leftNode; delete rightNode; }
	
	string	encodedChars;
	int		charFreq;
	Tree*	leftNode;
	Tree*	rightNode;

	// Source: https://stackoverflow.com/questions/19535644/how-to-use-the-priority-queue-stl-for-objects
	bool operator()(const Tree &tree1, const Tree &tree2) const
	{
		return tree1.charFreq < tree2.charFreq; 
	}
};

string getEncoding(string word);

string encodeCharacters(Tree* root, string byteString, string search);
string decodeCharacters(Tree* node, string byteString);

Tree createHuffmanTree();

void addToMap(string data);
string decodeTree(string byteString);

void writeHuffmanOutput(ofstream &stream, string word);
void writeHuffmanDecoded(ofstream &stream, string byteString);