#include "Huffman.h"

Tree* create_node(char _ch, int _freq, Tree* left, Tree* right)
{
    Tree* node = new Tree();
    node->characts = _ch;
    node->frequentChar = _freq;
    node->leftNode = left;
    node->rightNode = right;
    return node;
}

//inspired by >>> https://stackoverflow.com/questions/21886654/encoding-a-huffman-binary-tree
void encode_characters(Tree* root, string str, unordered_map<char, string> &huffCode)
{
	if (root == NULL)
	{
		return;
	}

	if (!root->leftNode && !root->rightNode)
	{
		huffCode[root->characts] = str;
	}
    encode_characters(root->leftNode, str + "0", huffCode);
    encode_characters(root->rightNode, str + "1", huffCode);
}

// credit goes to >>> https://stackoverflow.com/questions/21854069/decoding-huffman-tree
void decode_characters(Tree* root, int &pos, string str)
{
    //If root equals to null, just return
    if (root == NULL) return;

    //else we found a leaf
    if (!root->leftNode && !root->rightNode)
    {
        cout << root->characts;
    }pos++;

    if (str[pos] == '0') decode_characters(root->leftNode, pos, str);
    else decode_characters(root->rightNode, pos, str);
}

//The fun thing happens here, like creating huffman coding and working with files, etc.
void create_huff(string data)
{
    //variables used in this function
    string str = "";
    int position = -1;

    //counting each char in the file
    for (char c : data)
        fq[c]++;

    //store trees on priority queue
    for (auto tree : fq)
        priority_q.push(create_node(tree.first, tree.second, NULL, NULL));

    //iterate untill there is some trees in our queue
    while (priority_q.size() != 1)
    {
        Tree* lt = priority_q.top(); priority_q.pop();
        Tree* rt = priority_q.top(); priority_q.pop();

        int count = lt->frequentChar + rt->frequentChar;
        priority_q.push(create_node('\0', count, lt, rt));
    }
    Tree* root = priority_q.top();

    //fun thing begins now...print our tree
    encode_characters(root, "", hcode);

    //we need to output this data into file called huffmanoutput.txt
    cout << "Huffman Code: " << endl;
    for (auto tree : hcode)
        cout << tree.first << " " << tree.second << endl;
    cout << endl;

    // we need to output this data into file called reconstructedinput.txt
    for (char c : data)
        str += hcode[c] + " ";
    cout << endl;
    cout << "Encoded huffman code: " << str << " " << endl;

    //Just display the original string
    cout << "Decoded huffman code is: ";
    while (position < (int)str.size() - 2)
        decode_characters(root, position, str);
    cout << endl;
}