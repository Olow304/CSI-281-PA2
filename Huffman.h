#include <queue>
#include <unordered_map>
#include <string>
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

Tree* create_node(char, int, Tree*, Tree*);
void encode_characters(Tree* root, string str, unordered_map<char, string> &huffCode);
void decode_characters(Tree* root, int &pos, string str);
void create_huff(string data);
