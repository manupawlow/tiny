#include "BitWriter.h"

BitWriter::BitWriter(std::ofstream* file) : file(file) {}

void BitWriter::writeBit(int bit) {
    buffer = buffer | (bit << (7 - currIndex));
    indexCount++;
    if (++currIndex == 8) {
        file->put(buffer);
        buffer = 0;
        currIndex = 0;
    }
}

void BitWriter::writeByte(uint8_t byte) {
    for (int i = 7; i >= 0; --i) {
        writeBit((byte & (1 << i)) != 0);
    }
}
