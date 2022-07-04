#include "BuddyAllocator.h"
int main() {
	BuddyAllocator* allocator = new BuddyAllocator(4096);
    allocator->OutputAll();

    void* ptr11 = allocator->Insert(42);
    allocator->OutputAll();

    void* ptr12 = allocator->Insert(100);
    allocator->OutputAll();

    void* ptr13 = allocator->Insert(20);
    allocator->OutputAll();

    void* ptr14 = allocator->Insert(42);
    allocator->OutputAll();


    allocator->Remove(ptr13);
    allocator->OutputAll();

    allocator->Remove(ptr14);
    allocator->OutputAll();
    
    allocator->Remove(ptr11);
    allocator->OutputAll();

    allocator->Remove(ptr12);
    allocator->OutputAll();

    return 0;
}