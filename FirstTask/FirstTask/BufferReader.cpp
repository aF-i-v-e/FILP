#include "BufferReader.h" 
BufferReader::BufferReader(char* text, int textSize) {
    bufferList.fillLinkedList(text, textSize);
}


int BufferReader::fillOutDict()
{
    int wordLength = 0;
    LinkedList words = LinkedList(MAX_WORD_LENGTH);
    words.initializeEmptyBufferList();
    int bufferListLength = bufferList.length;
    int startTime = clock();
    for (int i = 0; i < bufferListLength; i++)
    {
        Buffer* current = bufferList.getBuffer(i);
        int size = current->realSize;
        for (int i = 0; i < size; i++) {
            char symbol = current->content[i];
            if (!isalpha((unsigned char)symbol)) {
                char* word = words.getWord();
                if (word[0] == '\0')
                    continue;
                if (dict.count(word) == 0) {
                    dict[word] = 1;
                }
                else {
                    dict[word]++;
                }
                words = LinkedList(MAX_WORD_LENGTH);
                words.initializeEmptyBufferList();
            }
            else
            {
                words.addSymbolInBuffer(symbol);
            }
        }
    }
    int systemTime = clock() - startTime;
    return systemTime;
}

void BufferReader::printDict() 
{
    for (auto it = dict.begin(); it != dict.end(); ++it)
    {
        cout << (*it).first << " : " << (*it).second << endl;
    }
    cout << "\r\n--------------------------------------------------------------------------------" << endl;
}