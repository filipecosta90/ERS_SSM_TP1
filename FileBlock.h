#include <stddef.h>
#include <stdlib.h>
#include <iostream>
#include <stdio.h>
#include <wchar.h>
#include <map>
#include <set>
#include <string.h>
#include <bitset>         // std::bitset
#include <vector>
#include "SymbolTable.h"

#ifndef FILE_BLOCK_H
#define FILE_BLOCK_H

class FileBlock{
  private:
    std::vector <char> input_chars;
    std::vector <std::bitset<1>> output_bits;
    SymbolTable symbol_table;
    int block_number;
    int block_start;
    int block_end;
    std::string input_name;
    float input_bits_size;
    float output_bits_size;
    float compression_ratio;

  public:
    FileBlock( 
        std::string input, 
        int number, int start, int end
        );

    void read_chars();
    void produce_symbols();
    void codify_huffman();
    void produce_bitstream();

    std::vector <std::bitset<1>> get_bitstream() const;
    int get_block_number() const;
    float get_compression_ratio() const;
    float get_input_bits_size() const;
    float get_output_bits_size() const;
    void print_fileblock_symbols (std::ostream& ostream) const;

    friend std::ostream& operator<<(std::ostream&, const FileBlock&);
};

#endif
