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
#include <algorithm>    // std::for_each

#include "FileCompress.h"

#include <iostream>     // std::cout
#include <fstream>      // std::ifstream

FileCompress::FileCompress( std::string input, std::string output, int size_block ){
  input_file = input;
  output_file = output;
  block_size = size_block;
};

bool FileCompress::read_file( ){
  std::ifstream ifs ( input_file, std::ifstream::binary | std::ifstream::in  );
  ifs.seekg (0, ifs.end);
  file_size = ifs.tellg();
  std::cout << "size in bytes" << file_size << std::endl;
  std::cout << "block size " << block_size << std::endl;
  int current_block_start = 0;
  int current_block_end = block_size;
  int left_file_size = file_size;
  int next_block_size;
  for ( int block = 0; left_file_size > 0 ; block++ ){
    if (left_file_size > block_size){
      left_file_size = left_file_size - block_size;
      next_block_size = block_size;
    }
    else {
      next_block_size = left_file_size;
      left_file_size = 0;
    }

    current_block_end = current_block_start + next_block_size;
    FileBlock new_block ( input_file, block,  current_block_start ,current_block_end );  
    new_block.read_chars();
    new_block.produce_symbols();

    current_block_start+=block_size;
  }
  return true;
}

std::ostream& operator<< (std::ostream& os, const FileCompress& obj) {
  os << "---------------------" << std::endl;
  os << "Tabela de Frequencias" << std::endl;
  os << "---------------------" << std::endl;
  return os;
}

