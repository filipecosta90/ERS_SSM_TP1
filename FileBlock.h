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
    std::vector <std::bitset<1>> output_bytes;
    SymbolTable symbol_table;
    int block_number;
    int block_start;
    int block_end;
    std::string input_name;

  public:
    FileBlock( 
        std::string input, 
        int number, int start, int end
        );

    void read_chars();
   void produce_symbols();
    //  bool codify();
//    bool write_bytes();


    friend std::ostream& operator<<(std::ostream&, const FileBlock&);
};

#endif
