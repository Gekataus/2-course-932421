#include <iostream>
#include <fstream>
#include "huffmantree.h"

int main()
{
    HuffmanTree huffman;

    double ratio = huffman.encode("input.txt", "encoded.txt");

    if (ratio >= 0)
    {
        std::cout << ratio << std::endl;
    }

    return 0;
}