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

int main (int argc, char* argv[])
{
  FILE* in;
  in = fopen(argv[1], "r");
  SymbolTable table;
  bool result = table.read_file(in);
  if ( result == EXIT_SUCCESS ){
    std::cout << table;
    table.codify_huffman();
    table.print_huffman(std::cout);
    return EXIT_SUCCESS;
  }
  else {
    std::cerr << "invalid file type" << std::endl;
    return EXIT_FAILURE;
  }
}

