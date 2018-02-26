#include "Huffman.h"

Tree::Tree(string letterToEncode, int letterFreq, Tree* leftChild, Tree* rightChild)
{
    encodedChars = letterToEncode;
    charFreq = letterFreq;
	this->leftNode = leftChild;
	this->rightNode = rightChild;
}

//inspired by >>> https://stackoverflow.com/questions/21886654/encoding-a-huffman-binary-tree
string encodeCharacters(Tree* root, string &byteString)
{
	if (byteString == "START")
	{
		byteString = "";
	}

	if (root == NULL)
	{
		return "";
	}

	if (!root->leftNode && !root->rightNode)
	{
		huffmanSequence[root->encodedChars] = byteString;
	}
    
	encodeCharacters(root->leftNode, byteString + "0");
	encodeCharacters(root->rightNode, byteString + "1");

	return byteString;
}

// credit goes to >>> https://stackoverflow.com/questions/21854069/decoding-huffman-tree
void decodeCharacters(Tree* root, int &huffCodeIndex, string byteString)
{
    //If root equals to null, just return
	if (root == NULL)
	{
		return;
	}

    //else we found a leaf
    if (!root->leftNode && !root->rightNode)
    {
        cout << root->encodedChars;
    }
	
	huffCodeIndex++;

	// If edge is 0, go to left node, else go right
	if (byteString[huffCodeIndex] == '0')
	{
		decodeCharacters(root->leftNode, huffCodeIndex, byteString);
	}
	else
	{
		decodeCharacters(root->rightNode, huffCodeIndex, byteString);
	}
}

void addToMap(string data)
{
	int freqCount = 0;

	// STEP 1: Get characters from string and add them to an unordered map charFreqs
	for (unsigned int i = 0; i < data.size(); i++)
	{
		string theKey = "";
		theKey += (data[i]);
		charFreqs[theKey] = ++freqCount;
		i++;
	}

	// STEP 2: create nodes/trees and initially store them in the priority queue huffForest
	for (auto tree : charFreqs)
	{
		Tree* newNode = new Tree(tree.first, tree.second, NULL, NULL);
		huffForest.push(newNode);
	}
}

void createHuffmanTree()
{
	// STEP 3: construct the huffman tree
	while (huffForest.size() != 1)
	{
		// Tree with lowest freq
		Tree* lowestFreq = huffForest.top();
		huffForest.pop();

		// Tree with second lowest freq
		Tree* secondLowestFreq = huffForest.top();
		huffForest.pop();

		// Get the frequency of the root of the new tree
		int newFreq = lowestFreq->charFreq + secondLowestFreq->charFreq;

		// Create a new string containing both of the letters being inserted
		string treeName = lowestFreq->encodedChars + secondLowestFreq->encodedChars;

		// Create a new tree by inserting the roots of the trees with lowest frequencies as nodes
		Tree* newTree = new Tree(treeName, newFreq, lowestFreq, secondLowestFreq);
		huffForest.push(newTree);
	}
}

string getEncoding()
{
	string finalEncoding = "START";
	Tree*	root = huffForest.top();

	// STEP 4: Encode data, store in unordered map
	finalEncoding += encodeCharacters(root, finalEncoding);

	return finalEncoding;
}

void decodeTree(string byteString)
{
    
	int		huffCodeIndex = 0;
	Tree*	root = huffForest.top();

	// STEP 5: Decode huffman encoding of data from unordered map
	cout << "Decoded huffman code is: ";
	while (huffCodeIndex < (int)byteString.size() - 1)
	{
		decodeCharacters(root, huffCodeIndex, byteString);
	}
    cout << endl;
}