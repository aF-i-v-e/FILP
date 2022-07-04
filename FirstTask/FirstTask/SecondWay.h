#include <iostream>
#include <map>
#include <string>
#include <algorithm>

using namespace std;

class DirectReader {
	map<string, int> dict;
public:
	void printDict();
	int fillOutDict(char* ktext, int textSize);
};