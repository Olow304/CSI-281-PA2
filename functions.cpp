#include "functions.h"

using namespace std;

void writeHuffmanOutput(ofstream &stream, string word)
{
	// we need to output this data into file called huffmanoutput.txt
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

void writeHuffmanDecoded(ofstream &stream, string word)
{
	// we need to output this data into file called reconstructedinput.txt
	for (char c : data)
		byteString += huffmanSequence[c] + " ";
	cout << endl;
	cout << "Encoded huffman code: " << byteString << " " << endl;
}