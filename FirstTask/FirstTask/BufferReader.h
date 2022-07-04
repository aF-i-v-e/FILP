#include "LinkedList.h" 
#include "Utils.h"
#include <iostream>
#include <map>
#include <string>

using namespace std;

class BufferReader
{
	LinkedList bufferList = LinkedList(BUFFER_SIZE);
	map<char*, int, MyCompare> dict;
public:
	BufferReader(char* text, int text_size);
	int fillOutDict();
	void printDict();
};

