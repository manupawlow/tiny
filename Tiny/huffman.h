#pragma once
#include <map>
#include <vector>
#include <sstream>
#include <fstream>
#include "BitReader.h"
#include "BitWriter.h"

struct Node {
    char character;
    int frequency;
    Node* left;
    Node* right;
    bool isLeaf() { return !left && !right; }
};

Node* compress(std::ifstream* file, std::ofstream* outputFile);
Node* decompress(std::ifstream* file, std::ofstream* output);

void encodeTree(Node* node, BitWriter* writter);
void createCodes(Node* node, std::map<char, std::vector<bool>>& codes, std::vector<bool> code = {});
int findSmallestIndex(std::vector<Node*> nodes);
Node* createTree(std::map<char, int>& frequencies);
int getPadding(std::map<char, int> frequencies, std::map<char, std::vector<bool>> codes);
Node* decodeTree(BitReader* bitReader);