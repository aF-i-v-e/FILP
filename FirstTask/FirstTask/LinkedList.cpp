#include "LinkedList.h"
Buffer::Buffer(int mSize)
{
    int real_size = 0;
    maxSize = mSize;
    content = new char[maxSize + 1]{0};
    Buffer* next = nullptr;
}

Buffer::~Buffer()
{
    if (content != nullptr)
        delete[] content;
    if (next != nullptr)
        next->~Buffer();
}

LinkedList::LinkedList(int size)
{
    length = 0;
    maxBufferSize = size;
    head = nullptr;
    tail = nullptr;
}

LinkedList::~LinkedList()
{
    if (head != nullptr)
        head->~Buffer();
}

int LinkedList::getLength()
{
    return length;
}
void LinkedList::addTextInBuffer(char* symbols, int textSize, int textPositionPointer)
{
    Buffer* bufferForText;
    int lastBufferIndex = length;
    if (lastBufferIndex > 0) 
    {
        bufferForText = getBuffer(lastBufferIndex - 1);
    }
    else 
    {
        addBuffer();
        bufferForText = getBuffer(0);
    }

    while (bufferForText->realSize < bufferForText->maxSize && textPositionPointer < textSize) 
    {
        bufferForText->content[bufferForText->realSize] = symbols[textPositionPointer];
        textPositionPointer += 1;
        bufferForText-> realSize += 1;
    }
    if (textPositionPointer < textSize) {
        addBuffer();
        addTextInBuffer(symbols, textSize, textPositionPointer);
    }
}

void LinkedList::addSymbolInBuffer(char symbol) {
    Buffer* bufferForText;
    int lastBufferIndex = length;
    if (lastBufferIndex > 0)
    {
        bufferForText = getBuffer(lastBufferIndex - 1);
    }
    else
    {
        addBuffer();
        bufferForText = getBuffer(0);
    }
    if (bufferForText->realSize < bufferForText->maxSize) {
        bufferForText->content[bufferForText->realSize] = symbol;
        bufferForText->realSize += 1;
    }
    else {
        addBuffer();
        addSymbolInBuffer(symbol);
    }
}

void LinkedList::addBuffer() 
{
    Buffer* new_buff = new Buffer(maxBufferSize);
    if (length == 0)
    {
        head = new_buff;
        tail = new_buff;
    }
    else
    {
        tail->next = new_buff;
        tail = tail->next;
    }
    length++;
}

Buffer* LinkedList::getBuffer(int pos)
{
    Buffer* current = head;
    if (pos > 0) {
        for (int i = 0; i < pos; i++) {
            current = current->next;
        }
    }
    return current;
}

void LinkedList::fillLinkedList(char* text, int textSize)
{
    addTextInBuffer(text, textSize, 0);
}

void LinkedList::initializeEmptyBufferList()
{
    addBuffer();
}

char* LinkedList::getWord() {
    int listLength = length;
    int buffer_size = maxBufferSize;
    char* word = new char[listLength * buffer_size + 1]{0};
    int symbol_pointer = 0;
    int leftBorder = 0;
    for (int i = 0; i < listLength; i++) {
        char* content = getBuffer(i)->content;
        buffer_size = getBuffer(i)->realSize;
        int content_pointer = 0;
        leftBorder += buffer_size;
        for (int j = symbol_pointer; j < leftBorder; j++){
            word[j] = content[content_pointer];
            content_pointer += 1;
            symbol_pointer += 1;
        }
    }
    return word;
}
