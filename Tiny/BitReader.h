#pragma once
#include <fstream>

class BitReader {
private:
    std::ifstream* file;
    char currByte = 0;
    int currIndex = 0;
    bool eof = false;

public:
    BitReader(std::ifstream* file);
    bool canRead();
    bool readBit(bool peek = false);
    bool peekBit();
    uint8_t readByte();
};
