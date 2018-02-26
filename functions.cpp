#include "functions.h"

using namespace std;

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
	string output;

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
