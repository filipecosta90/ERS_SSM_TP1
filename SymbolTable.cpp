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

#include "Symbol.h"
#include "SymbolTable.h"

SymbolTable::SymbolTable(){

}

bool SymbolTable::read_file( FILE* infile ){
  for ( char32_t wc; wc != WEOF; wc = getwc(infile) ){
    Symbol current( wc );
    std::set<Symbol, Symbol::compare>::iterator got = symbols_table.find (current);
    /* if the key doesn't exists*/
    if ( got == symbols_table.end() ){
      current.spotted();
      symbols_table.insert(current);
      distinct_symbols++;
    }
    /* if the key exists*/
    else {
      current.spotted();
      symbols_table.erase(got);
      symbols_table.insert(current);
    }
    total_symbols++;
  }
  fclose(infile);
  return EXIT_SUCCESS;
}

int SymbolTable::get_distinct_symbols() const {
  return distinct_symbols;
}

int SymbolTable::get_total_symbols() const {
  return total_symbols;
}

std::ostream& operator<< (std::ostream& os, const SymbolTable& obj) {
  os << "------------------" << std::endl;
  /*for ( auto it = obj.symbols_table.begin(); it != obj.symbols_table.end(); ++it ){
    Symbol actualSymbol = *it.
      os << actualSymbol;
  }
*/
  os << "------------------" << std::endl;
  os <<  "total caracteres: " << obj.get_total_symbols()  << std::endl;  
  os <<  "total caracteres distintos: " << obj.get_distinct_symbols()  << std::endl;

  return os;
}

