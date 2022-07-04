#include "SecondWay.h"

void DirectReader::printDict()
{
    for (auto it = dict.begin(); it != dict.end(); ++it)
    {
        cout << (*it).first << " : " << (*it).second << endl;
    }
    cout << "\r\n--------------------------------------------------------------------------------" << endl;
}

int DirectReader::fillOutDict(char* text, int textSize)
{
    string word;
    int startTime = clock();
    for (int i = 0; i < textSize; i++) {
        if (!isalpha((unsigned char)text[i])){
            if (word[0] == '\0')
                continue;
            if (dict.count(word) == 0) {
                dict[word] = 1;
            }
            else {
                dict[word]++;
            }
            word = "";
        }
        else {
            word += text[i];
        }
    }
    int systemTime = clock() - startTime;
    return systemTime;
}