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

void compress(std::ifstream* file, std::ofstream* outputFile);
void decompress(std::ifstream* file, std::ofstream* output);

void free_tree(Node* node);
void encode_tree(Node* node, BitWriter* writter);
void create_codes(Node* node, std::map<char, std::vector<bool>>& codes, std::vector<bool> code = {});
int find_smallest_index(std::vector<Node*> nodes);
Node* create_tree(std::map<char, int>& frequencies);
int get_padding(std::map<char, int> frequencies, std::map<char, std::vector<bool>> codes);
Node* decode_tree(BitReader* bitReader);