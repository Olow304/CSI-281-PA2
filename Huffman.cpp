/*
Authors:		Saleban Olow, Victor Alves
Class:			CSI-281-01
Assignment:		Programming Assignment 2: Huffman Coding
Assigned:		Week 5 Day 2
Due Date:		Thursday, March 1, 2018 11:59 PM
*/
#include "Huffman.h"

using namespace std;

/*
Data structures used in this project:
- Priority queue: stores forest of Trees, takes the Tree with the smallest value and adds to the Huffman Tree.
- Tree: Starts out with each character having its own Tree, stored in priority queue.
- Huffman Tree: Tree constructed from forest of trees in the priority queue
- Unordered Lists: Stores the codes of the individual letters in one of them, and the codes of the edges in the other.
*/

unordered_map<string, int> charFreqs;
unordered_map<string, string> huffmanSequence;

priority_queue<Tree, vector<Tree>, Tree> huffForest;

Tree::Tree(string letterToEncode, int letterFreq, Tree* leftChild, Tree* rightChild)
{
    encodedChars = letterToEncode;
    charFreq = letterFreq;
	this->leftNode = leftChild;
	this->rightNode = rightChild;
}

Tree::Tree(string letterToEncode, int letterFreq, Tree leftChild, Tree rightChild)
{
	encodedChars = letterToEncode;
	charFreq = letterFreq;
	this->leftNode = &leftChild;
	this->rightNode = &rightChild;
}

// Adapted from https://stackoverflow.com/questions/21886654/encoding-a-huffman-binary-tree
string encodeCharacters(Tree* node, string byteString, string search)
{
	if (node == NULL)
	{
		return "";
	}

	if (node->encodedChars == search)
	{
		 // return the byte string
		huffmanSequence[node->encodedChars] = byteString;
		return byteString;
	}
    
	// Adapted from https://stackoverflow.com/questions/2340281/check-if-a-string-contains-a-string-in-c
	if (node->leftNode->encodedChars.find(search) != string::npos) 
	{
		return encodeCharacters(node->leftNode, byteString + "0", search);
	}
	else
		//(node->rightNode->encodedChars.find(search) != string::npos) 
	{
		return encodeCharacters(node->rightNode, byteString + "1", search);
	}
}

// Adapted from https://stackoverflow.com/questions/21854069/decoding-huffman-tree
string decodeCharacters(Tree* root, string byteEncoding)
{
	string decoded;
	Tree* node = root; // initially set to root
	for (int i = 0; i != byteEncoding.size(); ++i)
	{
		if (byteEncoding[i] == '0') // traverse tree until leaf, add encoding
		{ 
			node = node->leftNode;
		}
		else 
		{
			node = node->rightNode;
		}
		if (!node->leftNode)
		{
			decoded += node->encodedChars;
			node = root;
		}
	}
	return decoded;
}

void addToMap(string data)
{
	// STEP 1: Get characters from string and add them to an unordered map charFreqs
	for (unsigned int i = 0; i < data.size(); i++)
	{
		string theKey = "";
		theKey += (data[i]);
		cout << "Key: " << theKey << endl;
		charFreqs[theKey]++;
		cout << "Value: " << charFreqs[theKey] << endl;
	}

	cout << charFreqs.size() << endl;
	// STEP 2: create nodes/trees and initially store them in the priority queue huffForest
	for (auto tree : charFreqs)
	{
		Tree* newNode = new Tree(tree.first, tree.second, NULL, NULL);
		cout << "Adding new node with the name " << tree.first << " and value of " << tree.second << endl;
		huffForest.push(*newNode);
	}
}

Tree createHuffmanTree()
{
	Tree	lowestFreq,
			secondLowestFreq;

	int		newFreq;
	string	treeName;

	bool	twoRemaining = false;
	
	// STEP 3: construct the huffman tree
	while (!twoRemaining)
	{
		// Tree with lowest freq
		 lowestFreq = huffForest.top();
		//huffForest.pop(); Triggers destuctor which breaks program, don't uncomment

		// Tree with second lowest freq
		secondLowestFreq = huffForest.top();
		//huffForest.pop();
		if (lowestFreq.charFreq == INT_MAX && secondLowestFreq.charFreq == INT_MAX)
		{
			twoRemaining = true;
		}
		// Get the frequency of the root of the new tree
		newFreq = lowestFreq.charFreq + secondLowestFreq.charFreq;

		// Create a new string containing both of the letters being inserted
		treeName = lowestFreq.encodedChars + secondLowestFreq.encodedChars;

		// Create a new tree by inserting the roots of the trees with lowest frequencies as nodes
		Tree* newTree = new Tree(treeName, newFreq, lowestFreq, secondLowestFreq);
		// change frequency after creating tree in order to push to the back of the priority queue, allowing
		// for the creation of more trees
		// stop when < 2 trees with an actual frequency remain
		lowestFreq.charFreq = INT_MAX; // max int const
		secondLowestFreq.charFreq = INT_MAX;

		huffForest.push(*newTree);
	}

	return huffForest.top();
}

string getEncoding(string word)
{
	Tree		root = huffForest.top();

	// STEP 4: Encode data, store in unordered map
	return encodeCharacters(&root, string(), word);
}

string decodeTree(string byteString)
{
	string		decodedWord;
	Tree		root = huffForest.top();

	// STEP 5: Decode huffman encoding of data from unordered map
	cout << "Decoded huffman code is: ";
	decodedWord = decodeCharacters(&root, byteString);
    // add couts to track encoding
	return decodedWord;
}

void writeHuffmanOutput(ofstream &stream, string word)
{
	// Writes encoded output to "huffmanoutput.txt"
	cout << "Huffman Code: " << endl;
	stream << "Huffman Code for the word " << word << ":" << "\n";

	for (auto tree : huffmanSequence)
	{
		cout << tree.first << " " << tree.second << endl;
		stream << "Letter: " << tree.first << "\n";
		stream << "Sequence: " << tree.second << "\n\n";
	}

	cout << endl;
}

void writeHuffmanDecoded(ofstream &stream, string byteString)
{
	// Decodes and writes output to "reconstructedinput.txt"
	string output = "";

	cout << "Reconstructed Input: " << endl;
	stream << "Original binary code for the word " << byteString << ":" << "\n";

	for (auto character : byteString)
	{
		string letter;
		string letterCode;

		letter += character;
		letterCode = huffmanSequence[letter];
		output += letterCode;

		stream << "Letter: " << letter << "\n";
		stream << "Corresponding code: " << letterCode << "\n\n";
	}

	stream << "Final decoding: " << output << "\n";
	cout << "Final decoding: " << output << endl;
}