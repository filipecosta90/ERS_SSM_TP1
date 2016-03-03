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


#ifndef SYMBOL_TABLE_H
#define SYMBOL_TABLE_H

class SymbolTable{
  public:
    std::set <Symbol, Symbol::compare> symbols_table;
    int distinct_symbols;
    int total_symbols;

// public:
    SymbolTable();
    bool read_file( FILE* infile );
    int get_distinct_symbols() const;
    int get_total_symbols() const;
    void printSymbols (std::ostream& ostream) const;
    
    friend std::ostream& operator<<(std::ostream&, const SymbolTable&);
};




#endif
