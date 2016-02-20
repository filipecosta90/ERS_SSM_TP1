#include <stddef.h>
#include <stdlib.h>
#include <iostream>
#include <stdio.h>
#include <wchar.h>
#include <map>
#include <string.h>


int main (int argc, char* argv[])
{
  if (argc != 3){
    std::cerr << "invalid argument number" << std::endl;
    return EXIT_FAILURE;
  }
  else {
    FILE *infile;
    if (strcmp(argv[1],"rt")== 0){
      infile=fopen(argv[2],"r,ccs=UTF-8");
    }
    else {
      if (strcmp(argv[1],"rb")== 0){
        infile=fopen(argv[2],"rb,ccs=UTF-8");
      }
      else {
        std::cerr << "invalid file type" << std::endl;
        return EXIT_FAILURE;
      }
    }
    char32_t wc;

    /* key: char32_t, value: absolute frequency */
    std::map<char32_t, long int> frequency_map;

    if (infile!=NULL){
      while ((wc = getwc (infile))!=WEOF){
        std::map<char32_t,long int>::const_iterator got = frequency_map.find (wc);
        /* if the key exists*/
        if ( got == frequency_map.end() ){
          std::pair<char32_t,long int> new_pair (wc,1);
          frequency_map.insert (new_pair); 
        }
        /* if the key doesn't exists*/
        else {
          frequency_map.at(wc)++;
        }
      }
      fclose(infile);
      /* print the frequency table*/
      std::cout << "------------------" << std::endl;
      std::cout << "Tabela Frequencias" << std::endl;
      std::cout << "------------------" << std::endl;
      long int total_caracters = 0;
      long int total_distinct = frequency_map.size();
      for ( auto it = frequency_map.begin(); it != frequency_map.end(); ++it ){
        std::cout << it->first << "\t" << (it->second) <<std::endl;
        total_caracters += it->second;
      }
      std::cout << "------------------" << std::endl;
      std::cout <<  "total caracteres: " << total_caracters  << std::endl;
      std::cout <<  "total caracteres distintos: " << total_distinct  << std::endl;
    }
    return EXIT_SUCCESS;
  }
}

