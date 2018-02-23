#include "Huffman.h"
#include "functions.h"

using namespace std;

int main()
{
	string			word;
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
			create_huff(word);
		}
	}

	system("pause");
	return 0;
}
