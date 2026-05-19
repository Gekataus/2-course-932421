#include <iostream>
#include <fstream>
#include <string>
#include "huffmantree.h"

int main()
{
    std::ifstream inputFile("input.txt");
    if (!inputFile.is_open())
    {
        std::cerr << "Cannot open input.txt" << std::endl;
        return 1;
    }

    std::string text((std::istreambuf_iterator<char>(inputFile)),
        std::istreambuf_iterator<char>());
    inputFile.close();

    HuffmanTree huffman;
    huffman.build(text);

    return 0;
}