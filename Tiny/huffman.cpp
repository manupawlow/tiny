#include "huffman.h"

using namespace std;

Node* compress(ifstream* file, ofstream* outputFile) {

    BitWriter* writter = new BitWriter(outputFile);
    char c;

    map<char, int> frequencies;
    while (file->get(c)) {
        frequencies[c]++;
    }

    auto root = createTree(frequencies);

    map<char, vector<bool>> codes;
    createCodes(root, codes);

    int padding = getPadding(frequencies, codes);
    for (size_t i = 0; i < padding; i++) {
        writter->writeBit(1);
    }
    writter->writeBit(0);

    encodeTree(root, writter);

    file->clear();
    file->seekg(0, ios::beg);

    while (file->get(c)) {
        for (int i = 0; i < codes[c].size(); i++) {
            writter->writeBit(codes[c][i]);
        }
    }

    return root;
}

Node* decompress(ifstream* file, ofstream* output) {
    BitReader* reader = new BitReader(file);

    while (reader->readBit());

    Node* root = decodeTree(reader);

    Node* currNode = root;
    //stringstream stream;
    while (reader->canRead()) {
        bool bit = reader->readBit();
        currNode = bit ? currNode->right : currNode->left;
        if (currNode->isLeaf()) {
            output->put(currNode->character);
            //stream << currNode->character;
            currNode = root;
        }
    }
    //*output << stream.str();
    return root;
}

vector<bool> addBit(const vector<bool>& bits, bool bit) {
    vector<bool> result = bits;
    result.push_back(bit);
    return result;
}

void createCodes(Node* node, map<char, vector<bool>>& codes, vector<bool> code) {
    if (node) {
        if (node->isLeaf()) {
            codes[node->character] = code;
            return;
        }
        createCodes(node->left, codes, addBit(code, 0));
        createCodes(node->right, codes, addBit(code, 1));
    }
}

void encodeTree(Node* node, BitWriter* writter) {
    if (node) {
        if (!node->isLeaf()) {
            writter->writeBit(0);
            encodeTree(node->left, writter);
            encodeTree(node->right, writter);
        }
        else
        {
            writter->writeBit(1);
            writter->writeByte(node->character);
        }
    }
}

int findSmallestIndex(vector<Node*> nodes) {
    int minIndex = 0;
    for (size_t i = 0; i < nodes.size(); i++)
    {
        if (nodes[i]->frequency <= nodes[minIndex]->frequency)
            minIndex = i;
    }
    return minIndex;
}

Node* createTree(map<char, int>& frequencies) {

    vector<Node*> nodes;
    for (const auto& el : frequencies) {
        nodes.push_back(new Node{ el.first, el.second, NULL, NULL });
    }

    while (nodes.size() > 1) {
        int leftIndex = findSmallestIndex(nodes);
        auto left = nodes[leftIndex];
        nodes.erase(nodes.begin() + leftIndex);

        int rightIndex = findSmallestIndex(nodes);
        auto right = nodes[rightIndex];
        nodes.erase(nodes.begin() + rightIndex);

        nodes.push_back(new Node{ NULL, left->frequency + right->frequency, left, right });
    }

    return nodes[0];
}

int getPadding(map<char, int> frequencies, map<char, vector<bool>> codes) {
    int totalBits = 10 * frequencies.size() - 1;
    for (const auto& el : frequencies)
        totalBits += el.second * codes[el.first].size();
    totalBits += 1;
    return (totalBits + 7) / 8 * 8 - totalBits;
}

Node* decodeTree(BitReader* bitReader) {
    if (bitReader->readBit()) {
        return new Node{ (char)bitReader->readByte() };
    }
    Node* left = decodeTree(bitReader);
    Node* right = decodeTree(bitReader);
    return new Node{ NULL, 0, left, right };
}