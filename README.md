# tiny

Welcome to the Huffman Compression and Decompression project! This C++ project provides functionality to compress and decompress files using Huffman coding, a popular algorithm for lossless data compression.

## What is Huffman Coding?
Huffman coding is a technique used for data compression. It assigns variable-length codes to input characters, with shorter codes for more frequent characters. This results in efficient compression and decompression of data.

## How to Use

To compress a file, use the following command. This will create a compressed file with a .tiny extension.
```bash
./Tiny tiny <filename> compress
```

To decompress a file, use the following command. This will create a decompressed file with the extension passed as parameter (or a txt extension as default).
```bash
./Tiny tiny <filename> decompress [extension]
```

## How It Works

### Compression

1. **Frequency Calculation:**
   - The program reads the input file and calculates the frequency of each character. This step determines how often each character appears in the input data.

2. **Building Huffman Tree:**
   - Using the calculated frequencies, the program constructs a Huffman tree. In this tree, characters with higher frequencies are placed closer to the root, and characters with lower frequencies are deeper in the tree. This hierarchical arrangement ensures that frequently occurring characters are represented by shorter codes, optimizing compression.

3. **Encoding:**
   - With the Huffman tree in place, the program traverses the tree to create a mapping of characters to Huffman codes. During this traversal, each character is assigned a unique binary code based on its position in the tree. These codes are then used to represent the characters in the compressed file.

4. **Output File:**
   - The generated Huffman codes, along with the encoded data, are written to the output file. To ensure accurate decompression, the program also includes information about the tree structure in the output, allowing for proper reconstruction during decompression.

### Decompression

1. **Tree Reconstruction:**
   - When decompressing, the program first reconstructs the Huffman tree from the encoded data and the tree structure information. This step is crucial for decoding the compressed data accurately.

2. **Decoding:**
   - Using the reconstructed Huffman tree, the program reads the encoded bits from the input file. As it traverses the tree following the encoded bits, it identifies the original characters. This process effectively decodes the compressed data, transforming it back into the original content.

3. **Output File:**
   - The decompressed characters are then written to the output file, reconstructing the original file content. The output file matches the content of the file before compression, ensuring lossless data recovery.

By following this systematic approach of frequency analysis, Huffman tree construction, encoding, and decoding, the program achieves efficient compression and decompression of data, making it a reliable tool for reducing file sizes while preserving data integrity.

*This project is open-source under the MIT License (check out the [LICENSE](LICENSE) file).*
