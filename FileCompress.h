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
    float file_compress_ration;
    int block_size;
    int file_size;

  public:
    FileCompress( std::string input, std::string output, int block_size );
    bool read_file( );
    //    bool write_file();
  //  bool codify_huffman();

    friend std::ostream& operator<<(std::ostream&, const FileCompress&);
};

#endif
