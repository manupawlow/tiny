#include "BitReader.h"

BitReader::BitReader(std::ifstream* file) : file(file) {
    file->get(currByte);
}

bool BitReader::canRead() {
    return !eof;
}

bool BitReader::readBit(bool peek) {
    int bitOffset = 7 - currIndex % 8;
    bool bit = (currByte & (1 << bitOffset)) != 0;

    if (!peek && ++currIndex % 8 == 0) {
        if (!file->get(currByte)) {
            eof = true;
        }
    }
    return bit;
}

bool BitReader::peekBit() {
    return readBit(true);
}

uint8_t BitReader::readByte() {
    uint8_t result = 0;
    for (size_t i = 0; i < 8; ++i) {
        size_t bitOffset = 7 - i % 8;
        if (readBit()) {
            result |= (1 << bitOffset);
        }
    }
    return result;
}
