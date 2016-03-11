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
#include <unistd.h>


#include "FileCompress.h"

int main (int argc, char* argv[])
{
  if(const char* env_p = std::getenv("OMP_NUM_THREADS")){
    std::cout << "OMP ENABLED " << std::endl;
  }
  long pagesize = sysconf(_SC_PAGESIZE);
  std::cout << "_SC_PAGESIZE " << pagesize << std::endl;

  FileCompress compress (argv[1], argv[2], pagesize );
  bool result = compress.read_file( );
  if ( result == true ){
    std::cout << "Finalized reading file" << std::endl;
    compress.codify_huffman();
    std::cout << "Finalized codifying" << std::endl;
    compress.produce_bitstream();
    std::cout << "Finalized producing bitstream" << std::endl;
    compress.write_file();
    std::cout << "Finalized writing file" << std::endl;
    std::cout << "Printing Enconding Tables" << std::endl;
    std::cout << "Finalized printing encoding" << std::endl;
    std::cout << compress;
    return EXIT_SUCCESS;
  }
  else {
    std::cerr << "invalid file type" << std::endl;
    return EXIT_FAILURE;
  }
}

