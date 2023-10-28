#pragma once
#include <fstream>

class BitWriter {
private:
    std::ofstream* file;
    int currIndex = 0;
    int indexCount = 0;
    unsigned char buffer = 0;

public:
    BitWriter(std::ofstream* file);
    void writeBit(int bit);
    void writeByte(uint8_t byte);
};
