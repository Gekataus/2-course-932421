#include <iostream>
#include <fstream>
#include <string>
#include "huffmantree.h"

int main()
{
    setlocale(LC_ALL, "Rus");
    HuffmanTree huffman;

    double ratio = huffman.encode("input.txt", "encoded.txt");

    if (ratio >= 0)
    {
        std::cout << "Коэффициент сжатия: " << ratio << std::endl;

        bool success = huffman.decode("encoded.txt", "output.txt");

        if (success)
        {
            std::cout << "Кодирование сохранено в файл encoded.txt, декодирование в output.txt";
        }
    }

    return 0;
}