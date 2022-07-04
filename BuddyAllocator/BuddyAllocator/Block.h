struct Block {
    int level;
    bool free;

    union {
        struct {
            Block* next;
            Block* prev;
        };
        char data[0];
    };
};