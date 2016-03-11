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
#include "FileBlock.h"

#ifndef FILE_COMPRESS_H
#define FILE_COMPRESS_H

class FileCompress{
  private:
    std::string input_file;
    std::string output_file;
    std::vector <FileBlock> table_blocks;
    std::vector <std::bitset<1>> output_encoding;
    std::vector <std::bitset<8>> output_bytes;
    float file_compress_ration;
    int block_size;
    int input_file_size;
    int output_file_size;
    int number_blocks;

  public:
    FileCompress( std::string input, std::string output, int block_size );

    bool read_file();
    bool write_file();
    bool codify_huffman();
    bool produce_bitstream();

    int get_input_file_size() const;
    int get_output_file_size() const;
    int get_number_blocks() const;
    int get_block_size() const;
    float get_compression_ratio() const;

     void print_encoding( std::ostream& stream ) const;
    void print_compression (std::ostream& stream) const;

    friend std::ostream& operator<<(std::ostream&, const FileCompress&);
};

#endif
