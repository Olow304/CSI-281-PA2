#include "functions.h"

using namespace std;

int main()
{
	string			word,
					byteString;
	ifstream		readOGInput("huffmaninput.txt");
	ofstream		writeHuffCode("huffmanoutput.txt"),
					writeHuffDecode("reconstructedinput.txt");
	
	// Read from huffmaninput and store characters and their frequencies in an unordered list.
	if (readOGInput.good())
	{
		while (!readOGInput.eof())
		{
			readOGInput >> word;
			readOGInput.ignore(); // ignore newline character
			addToMap(word);

			createHuffmanTree();
			byteString = getEncoding();
			decodeTree(byteString);

			if (writeHuffCode.good())
			{
				writeHuffmanOutput(writeHuffCode, word);
			}

			/*if (writeHuffDecode.good())
			{
				writeHuffmanDecoded(writeHuffDecode, byteString);
			}*/
		}
	}

	

	system("pause");
	return 0;
}
