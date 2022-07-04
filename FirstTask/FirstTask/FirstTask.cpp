#include <fstream>
#include <iostream>
#include <string>
#include "SecondWay.h"
#include "BufferReader.h"
using namespace std;

int main()
{
    const char* filename = "./medicalBook.txt";
    ifstream file(filename, ifstream::ate | ifstream::binary);
    if (!file) {
        cout << "File wasn't opened!" << endl;
        return -1;
    }
    int file_size = file.tellg();
    char* text = new char[file_size + 1]{ 0 };
    file.seekg(0, ios::beg);
    file.read(text, file_size);
    file.close();

    BufferReader bufferReader = BufferReader(text, file_size);
    int timeBufferReader = bufferReader.fillOutDict();
    cout << "Buffer reading time: " << timeBufferReader << " ms" << endl;
    bufferReader.printDict();

    DirectReader directReader;
    int timeDirectReader = directReader.fillOutDict(text, file_size);
    cout << "Direct reading from file time: " << timeDirectReader << " ms" << endl;
    directReader.printDict();

    if (timeBufferReader > timeDirectReader) {
        cout << "Direct reader is faster on " << (timeBufferReader - timeDirectReader) << " ms" << endl;
    }
    else {
        cout << "Buffer reader is faster on " << (timeDirectReader - timeBufferReader) << " ms" << endl;
    }
}

