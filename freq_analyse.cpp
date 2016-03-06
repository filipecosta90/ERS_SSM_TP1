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
  compress.codify_huffman();
  compress.produce_bitstream();  
  compress.write_file();
    std::cout << compress;
    return EXIT_SUCCESS;
  }
  else {
    std::cerr << "invalid file type" << std::endl;
    return EXIT_FAILURE;
  }
}

