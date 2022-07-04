#include "Block.h"
class BuddyAllocator {
    char* memory;
    int maxLevel;
    size_t mask;
    const int structureFieldsSize = 8;
    Block* freeBlocksList[32];

public:
    BuddyAllocator(size_t buffer);
    BuddyAllocator(const BuddyAllocator& other);
    ~BuddyAllocator();
    void* Insert(size_t size);
    void Remove(void* dataPointer);
    void OutputAll();
private:

    void* alloc(size_t dataSize);

    void divideBlock(Block* block, size_t fullSize);

    Block* removeFreeBlock(int level);

    void addFreeBlock(Block* block);

    size_t getSuitableBlock(size_t fullSize);

    size_t getMostSuitableSize(size_t fullSize);

    int bsr(int number);

    int bsf(int number);

    Block* mergeBuddies(Block* firstBuddyBlock);

    void removeBuddy(Block* buddy);
};

