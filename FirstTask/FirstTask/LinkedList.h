class Buffer
{
    public:
        int realSize;
        int maxSize;
        char* content = nullptr;
        Buffer* next = nullptr;
        Buffer(int bufferSize);
        ~Buffer();
};

class LinkedList
{
private:
    Buffer* head;
    Buffer* tail;
    void addBuffer();
public:
    int maxBufferSize;
    size_t length = 0;
    LinkedList(int bufferSize);
    ~LinkedList();
    int getLength();
    Buffer* getBuffer(int pos);
    void fillLinkedList(char* text, int textSize);
    void initializeEmptyBufferList();
    char* getWord();
    void addTextInBuffer(char* symbols, int textSize, int textPositionPointer);
    void addSymbolInBuffer(char symbol);
};
