#include <iostream>
#include <fstream>
#include <iomanip>
#include "huffman.h"

using namespace std;

string rename_file_path(const string& path, const string& newExtension, const string& extraName = "") {
    size_t lastDotPos = path.find_last_of(".");
    if (lastDotPos == string::npos)
        return path;
    string currentName = path.substr(0, lastDotPos);
    string newPath = currentName + extraName + "." + newExtension;
    return newPath;
}

bool endsWith(const std::string& mainString, const std::string& ending) {
    if (mainString.length() >= ending.length()) {
        std::string extractedEnding = mainString.substr(mainString.length() - ending.length());
        return (extractedEnding == ending);
    }
    else {
        return false;
    }
}

int decompress_step(string input_filename, string output_extension) {
    if (!endsWith(input_filename, ".tiny")) {
        cerr << "[ERROR] Could not decompress a file that`s not has a .tiny extension";
        return 1;
    }

    ifstream input(input_filename, ios::binary);
    if (!input.is_open()) {
        cerr << "[ERROR] Could not open file " << input_filename;
        return 1;
    }

    string output_filename = rename_file_path(input_filename, output_extension, " (untiny)");
    ofstream output = ofstream(output_filename);
    if (!output.is_open()) {
        cerr << "[ERROR] Could not create file " << output_filename;
        input.close();
        return 1;
    }

    decompress(&input, &output);

    input.close();
    output.close();

    cout << "Done decompressing!" << endl;
    cout << "Output file located at \"" << output_filename << "\"" << endl;
}

int compress_step(string input_filename) {
    ifstream input(input_filename);
    if (!input.is_open()) {
        cerr << "[ERROR] Could not open file " << input_filename;
        return 1;
    }

    string output_filename = rename_file_path(input_filename, "tiny");
    ofstream output = ofstream(output_filename, ios::binary);
    if (!output.is_open()) {
        cerr << "[ERROR] Could not create file " << output_filename;
        input.close();
        return 1;
    }
    
    compress(&input, &output);

    input.close();
    output.close();

    cout << "Done compressing!" << endl;
    cout << "Output file located at \"" << output_filename << "\"" << endl;
}

int main(int argc, char* argv[]) {

    if (argc < 4 || strcmp(argv[1], "tiny") != 0)
        goto invalid_params_error;

    if (strcmp(argv[3], "c") == 0 || strcmp(argv[3], "compress") == 0)
        return compress_step(argv[2]);

    if (strcmp(argv[3], "d") == 0 || strcmp(argv[3], "decompress") == 0)
        return decompress_step(argv[2], argc >= 4 ? argv[4] : "txt");

invalid_params_error:
    cerr << "[ERROR] Invalid params, correct use: tiny <filename> [compress|decompress] [extension]" << endl;
    return 1;
}