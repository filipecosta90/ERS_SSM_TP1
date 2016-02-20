#include <stddef.h>
#include <stdlib.h>
#include <iostream>
#include <stdio.h>
#include <wchar.h>
#include <map>

#include <unordered_map>
int main (int argc, char* argv[])
{
  if (argc < 2){
    std::cerr << "error";
    return 1;
  }
  else {
    FILE *infile;
    infile=fopen(argv[1],"r");
    wchar_t wc;
      wchar_t * pEnd;

  std::map<wchar_t, long int> frequency_map;

  if (infile!=NULL){
    while ((wc = getwc (infile))!=WEOF){
      std::map<wchar_t,long int>::const_iterator got = frequency_map.find (wc);
      if ( got == frequency_map.end() ){
        std::pair<wchar_t,long int> new_pair (wc,1);
          frequency_map.insert (new_pair); 
      }
      else {
        frequency_map.at(wc)++;
      }
    }
    fclose(infile);
    for ( auto it = frequency_map.begin(); it != frequency_map.end(); ++it ){
      std::cout << " " << it->first << ":" << (it->second) <<std::endl;

    }
  
  }
  return 0;
  }
}
