#include "huffman.h"

using namespace std;

void compress(ifstream* file, ofstream* outputFile) {

    BitWriter* writter = new BitWriter(outputFile);
    char c;

    map<char, int> frequencies;
    while (file->get(c)) {
        frequencies[c]++;
    }

    auto root = create_tree(frequencies);

    map<char, vector<bool>> codes;
    create_codes(root, codes);

    int padding = get_padding(frequencies, codes);
    for (size_t i = 0; i < padding; i++) {
        writter->writeBit(1);
    }
    writter->writeBit(0);

    encode_tree(root, writter);

    file->clear();
    file->seekg(0, ios::beg);

    while (file->get(c)) {
        for (int i = 0; i < codes[c].size(); i++) {
            writter->writeBit(codes[c][i]);
        }
    }

    free_tree(root);
    delete writter;
}

void decompress(ifstream* file, ofstream* output) {
    BitReader* reader = new BitReader(file);

    while (reader->readBit());

    Node* root = decode_tree(reader);
    Node* currNode = root;
    
    while (reader->canRead()) {
        
        currNode = reader->readBit() 
            ? currNode->right 
            : currNode->left;

        if (currNode->isLeaf()) {
            output->put(currNode->character);
            currNode = root;
        }
    }

    free_tree(root);
    delete reader;
}

vector<bool> addBit(const vector<bool>& bits, bool bit) {
    vector<bool> result = bits;
    result.push_back(bit);
    return result;
}

void create_codes(Node* node, map<char, vector<bool>>& codes, vector<bool> code) {
    if (node) {
        if (node->isLeaf()) {
            codes[node->character] = code;
            return;
        }
        create_codes(node->left, codes, addBit(code, 0));
        create_codes(node->right, codes, addBit(code, 1));
    }
}

void encode_tree(Node* node, BitWriter* writter) {
    if (node) {
        if (!node->isLeaf()) {
            writter->writeBit(0);
            encode_tree(node->left, writter);
            encode_tree(node->right, writter);
        }
        else
        {
            writter->writeBit(1);
            writter->writeByte(node->character);
        }
    }
}

int find_smallest_index(vector<Node*> nodes) {
    int minIndex = 0;
    for (size_t i = 0; i < nodes.size(); i++)
    {
        if (nodes[i]->frequency <= nodes[minIndex]->frequency)
            minIndex = i;
    }
    return minIndex;
}

Node* create_tree(map<char, int>& frequencies) {

    vector<Node*> nodes;
    for (const auto& el : frequencies) {
        nodes.push_back(new Node{ el.first, el.second, NULL, NULL });
    }

    while (nodes.size() > 1) {
        int leftIndex = find_smallest_index(nodes);
        auto left = nodes[leftIndex];
        nodes.erase(nodes.begin() + leftIndex);

        int rightIndex = find_smallest_index(nodes);
        auto right = nodes[rightIndex];
        nodes.erase(nodes.begin() + rightIndex);

        nodes.push_back(new Node{ NULL, left->frequency + right->frequency, left, right });
    }

    return nodes[0];
}

int get_padding(map<char, int> frequencies, map<char, vector<bool>> codes) {
    int totalBits = 10 * frequencies.size() - 1;
    for (const auto& el : frequencies)
        totalBits += el.second * codes[el.first].size();
    totalBits += 1;
    return (totalBits + 7) / 8 * 8 - totalBits;
}

Node* decode_tree(BitReader* bitReader) {
    if (bitReader->readBit()) {
        return new Node{ (char)bitReader->readByte() };
    }
    Node* left = decode_tree(bitReader);
    Node* right = decode_tree(bitReader);
    return new Node{ NULL, 0, left, right };
}

void free_tree(Node* node) {
    if (node == nullptr)
        return;
    
    free_tree(node->left);
    free_tree(node->right);

    delete node;
}