#include <iostream>
#include <fstream>
#include <queue>
#include <fstream>
#include <string>
#include <unordered_map>

using namespace std;

struct Tree
{
	char characts;
	int frequentChar;
	Tree *leftNode, *rightNode;

	bool operator()(Tree* lt, Tree* rt)
	{
		return lt->frequentChar > rt->frequentChar;
	}
};

//DEFINE - STL CLASSES
priority_queue<Tree*, vector<Tree*>, Tree> priority_q;
unordered_map<char, int> fq;
unordered_map<char, string> hcode;

Tree* create_node(char, int, Tree*, Tree*);
void encode_characters(Tree* root, string str, unordered_map<char, string> &huffCode);
void decode_characters(Tree* root, int &pos, string str);
void create_huff(string data);