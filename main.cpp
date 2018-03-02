/*
Authors:		Saleban Olow, Victor Alves
Class:			CSI-281-01
Assignment:		Programming Assignment 2: Huffman Coding
Assigned:		Week 5 Day 2
Due Date:		Thursday, March 1, 2018 11:59 PM
Description:
This program reads in words from a file, and then encodes and decodes them 
according to their corresponding encoding, writing those outputs to their respective files.

Certification of Authenticity:
I  certify  that  this  is  entirely  my  own  work,  except  where  I  have  given fully-documented  references  to  the  work  of  others.
I  understand  the definition and consequences of plagiarism and acknowledge that the assessor of this assignment may, for the purpose of assessing this assignment:
-Reproduce  this  assignment  and  provide  a  copy  to  another  member  of academic staff; and/or
-Communicate  a  copy  of  this  assignment  to  a  plagiarism  checking service (which  may  then  retain  a  copy  of  this  assignment  on  its database for the purpose of future plagiarism checking)
*/
#include "Huffman.h"

using namespace std;

int main()
{
	string			word,
					decodedWord,
					byteString;
	ifstream		readOGInput("huffmaninput.txt");
	ofstream		writeHuffCode("huffmanoutput.txt"),
					writeHuffDecode("reconstructedinput.txt");

	Tree			huffTree;
	
	// Read from huffmaninput and store characters and their frequencies in an unordered list.
	if (readOGInput.good())
	{
		while (!readOGInput.eof())
		{
			readOGInput >> word;
			addToMap(word);

			huffTree = createHuffmanTree();
			byteString = getEncoding(word);
			decodedWord = decodeTree(byteString);

			if (writeHuffCode.good())
			{
				writeHuffmanOutput(writeHuffCode, decodedWord);
			}

			if (writeHuffDecode.good())
			{
				writeHuffmanDecoded(writeHuffDecode, byteString);
			}
		}
	}

	system("pause");
	return 0;
}
