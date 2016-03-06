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
#include <iostream>     // std::cout
#include <fstream>      // std::filebuf, std::ifstream

#include <iomanip>
#include <locale>
#include <sstream>
#include <string> // this should be already included in <sstream>
#include "FileBlock.h"
#include "SymbolTable.h"

FileBlock::FileBlock( 
    std::string input, 
    int number, int start, int end
    ){
  input_name = input;
  block_number = number;
  block_start = start;
  block_end = end;
};

void FileBlock::read_chars( ){
  std::ifstream ifs ( input_name , std::ifstream::binary | std::ifstream::in  );
  ifs.seekg (block_start, std::ios::cur);
  int blocksize = block_end - block_start;
  input_chars.resize(blocksize);
  ifs.read(&input_chars[0], blocksize);
}

void FileBlock::produce_symbols(){
  symbol_table.read_symbols(input_chars);
}

std::ostream& operator<< (std::ostream& os, const FileBlock& obj) {
  os << "--------------------" << std::endl;
  return os;
}

