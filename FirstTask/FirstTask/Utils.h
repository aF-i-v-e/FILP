#include <iostream>
#include <map>
#include <string>
#define BUFFER_SIZE 1024*1024
#define MAX_WORD_LENGTH 5
class MyCompare
{
public:
    //регистр букв различаем
    bool operator()(char* a, char* b) const {
        while (isalpha(*a)) {
            char valA = *a;
            char valB = *b;
            if (valA < valB) {
                return true;
            }
            if (valA > valB) {
                return false;
            }

            a++;
            b++;
        }

        return isalpha(*b);
    }
};
