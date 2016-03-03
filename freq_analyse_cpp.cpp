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


class Symbol {
  public:
    char32_t character;
    long int absolut_freq;
    float relative_freq;
    std::vector < std::bitset<1>> codification;

    bool operator<(const Symbol& other) const
    {
      return character < other.character;
    }

    void spotted(){
      absolut_freq++;
    };

    struct compare {
      bool operator()(const Symbol& a, const Symbol& b)const
      {if (a.relative_freq != b.relative_freq) return a.relative_freq > b.relative_freq;
        return a.character > b.character;
      };
    };

    /* adds a new less significant bit*/
    void add_less_sig_bit( std::bitset<1> s_bit ){
      std::vector<std::bitset<1>>::iterator it;
      it = codification.end();
      codification.insert ( it , s_bit );
    };

};

class SymbolTable{
  public:
    std::set <Symbol, Symbol::compare> symbols_table;
    int distinct_symbols;
    int total_count;

    bool read_file( FILE* infile ){
      for ( char32_t wc; wc != WEOF; wc = getwc(infile)){
        Symbol current;
        current.character = wc;
        std::set<Symbol>::iterator got = symbols_table.find (current);
        /* if the key doesn't exists*/
        if ( got == symbols_table.end() ){
          current.absolut_freq++;
          symbols_table.insert(got,current);
          distinct_symbols++;
        }
        /* if the key exists*/
        else {
          (*got)->spotted();
        }
        total_count++;
      }
      fclose(infile);
      return EXIT_SUCCESS;
    };
};

int main (int argc, char* argv[])
{
  FILE* in;
  in = fopen(argv[2], "r");
  SymbolTable table;
  bool result = table.read_file(in);
  if ( result ){
    return EXIT_SUCCESS;
  }
  else {
    std::cerr << "invalid file type" << std::endl;
    return EXIT_FAILURE;
  }
}

