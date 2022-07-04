#include <iostream>
#include "BuddyAllocator.h"
using namespace std;

BuddyAllocator::BuddyAllocator(size_t buffer) {
    maxLevel = log2(buffer);
    memory = (char*)malloc(buffer);
    Block* block = reinterpret_cast<Block*>(memory);
    block->level = maxLevel;
    addFreeBlock(block);
}

BuddyAllocator::~BuddyAllocator() {
    free(memory);
}

BuddyAllocator::BuddyAllocator(const BuddyAllocator & other) {
    memory = other.memory;
}


void* BuddyAllocator::Insert(size_t size) {
    void* memoryPlace = alloc(size);
    return memoryPlace;
}
    
void BuddyAllocator::Remove(void* dataPointer) {
    Block* firstBuddyBlock = reinterpret_cast<Block*>((char*)dataPointer - structureFieldsSize);//�������� ��������� �� ������ �� ������ ����� ���������
    Block* mergedBuddyBlock = mergeBuddies(firstBuddyBlock);
    addFreeBlock(mergedBuddyBlock);
}

void BuddyAllocator::OutputAll() {
    cout << "Free blocks: " << endl;
    size_t maskLevel = mask;
    while (maskLevel) {
        int blockLevel = bsr(maskLevel);
        cout << "Level " << blockLevel << " : " << endl;
        Block* block = freeBlocksList[blockLevel];
        while (block != nullptr) {
            cout << block << " ";
            block = block->next;
        }
        cout << endl;
        maskLevel = maskLevel & (~(static_cast<unsigned long long>(1) << blockLevel));
    }
    cout << endl;
    cout << "-------------------------------------------------------------------------" << endl;
}

void* BuddyAllocator::alloc(size_t dataSize) {
    size_t fullSize = dataSize + structureFieldsSize;
    size_t smallestExistingSuitableBlock = getSuitableBlock(fullSize);
    Block* block = removeFreeBlock(smallestExistingSuitableBlock);
    divideBlock(block, fullSize); //���� ���� ���� ������� �������, �� �� ��� ������� �� ���������
    return block->data;
}

void BuddyAllocator::divideBlock(Block* block, size_t fullSize) {
    size_t mostSuitableSize = getMostSuitableSize(fullSize);
    while (mostSuitableSize < (1 << (block->level))) {
        block->level = block->level - 1;
        Block* smallerBlock = reinterpret_cast<Block*> (block->data - structureFieldsSize
            + (1 << block->level));
        //����� ��������� �� ���� ������ � �������� ��� �� ������ ����� ��������� = �������� ��������� �� ������ �����. ����� ����� ��������� ����� ������ ��� �������� �����
        smallerBlock->level = block->level;
        addFreeBlock(smallerBlock);
    }
}

Block* BuddyAllocator::removeFreeBlock(int level) {
    Block* block = freeBlocksList[level];
    if (block->next == nullptr) { //��������, ��� � ������ � ������ level ��� ������ ���� ����
        mask &= (~(1 << level)); //������� ���������� �� mask, ������ ������ � ������ level ����
    }
    else {
        block->next->prev = nullptr;
        freeBlocksList[level] = block->next;
    }
    block->free = false;
    return block;
}

void BuddyAllocator::addFreeBlock(Block* block) {
    block->free = true;
    block->prev = nullptr;
    //��������, ��� ������, � ������� ����� �������� ���� �� ����
    if (mask & (static_cast<unsigned long long>(1) << block->level)) {
        block->next = freeBlocksList[block->level];//��������� ���� � ������ ������ 
        freeBlocksList[block->level]->prev = block;
    }
    else {
        block->next = nullptr;
        //���������� � mask, ��� ������ ������ ������� block->level �� ����
        mask = mask | (static_cast<unsigned long long>(1) << block->level);
    }
    freeBlocksList[block->level] = block;
}

size_t BuddyAllocator::getSuitableBlock(size_t fullSize) {
    size_t mostSuitableSize = getMostSuitableSize(fullSize);
    size_t suitableLevelsMask = ~(mostSuitableSize - 1);
    size_t freeSuitableLevelsMask = suitableLevelsMask & mask;
    return bsf(freeSuitableLevelsMask);
}

size_t BuddyAllocator::getMostSuitableSize(size_t fullSize) {
    return (1 << bsr(fullSize) + 1);
}

/*bsr = bit scan reverse - �������� ������ ����� ������� ���� ������, �������� �������� ����� 1
    ���� ����� ������� � �������� ����� ������� ����, �������� �������� ����� 1 */
int BuddyAllocator::bsr(int number) {
    int pos = 0;
    while (number >>= 1)
        pos++;
    return pos;
}

/* bfs = bit scan forward - ������� ������ ����� ������� ���� �����, �������� �������� ����� 1
       ���� ������ ������ � �������� ����� ������� ����, �������� �������� ����� 1  */
int BuddyAllocator::bsf(int number) {
    int pos = 0;
    while ((number & 1) == 0) {
        number = number >> 1; //������� ����� ������, ��� ����� ��� ����� �� 2
        pos++;
    }
    return pos;
}


Block* BuddyAllocator::mergeBuddies(Block* firstBuddyBlock) {
    while (true) {
        if (firstBuddyBlock->level == maxLevel)
            break;
        char* address = firstBuddyBlock->data - structureFieldsSize;
        int blockSize = 1 << firstBuddyBlock->level;
        int blockSequenceNumber = (address - memory) / blockSize;
        //���� ���������� ����� ������, ������ �� �����, �������� - �� ������, 0�, 1�, 2�, 3� :L R L R
        Block* secondBuddyBlock;
        if (blockSequenceNumber % 2 == 0) {
            secondBuddyBlock = reinterpret_cast<Block*> (address + blockSize);
        }
        else { //��� ���� ������, � ����� �����
            secondBuddyBlock = reinterpret_cast<Block*> (address - blockSize);
            if (secondBuddyBlock->level == firstBuddyBlock->level && secondBuddyBlock->free) {
                firstBuddyBlock = secondBuddyBlock;
            }
        }
        if (secondBuddyBlock->level == firstBuddyBlock->level && secondBuddyBlock->free) {
            removeBuddy(secondBuddyBlock);
            firstBuddyBlock->level++;
            firstBuddyBlock->free = true;
        }
        else {
            break;
        }
    }
    return firstBuddyBlock;
}


void BuddyAllocator::removeBuddy(Block* buddy) {
    if (buddy->prev == nullptr && buddy->next == nullptr) {
        mask = mask & (~(1 << buddy->level));
    }
    if (buddy->prev != nullptr) {
        buddy->prev->next = buddy->next;
    }
    if (buddy->next != nullptr) {
        buddy->next->prev = buddy->prev;
    }
}

