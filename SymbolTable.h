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
    void fill_bit ( std::set <Symbol,Symbol::compare>::iterator it_start,
        std::set<Symbol,Symbol::compare>::iterator it_end, std::bitset<1> value_bit);

    float table_frequency ( std::set <Symbol, Symbol::compare> partial_table, 
        std::set <Symbol,Symbol::compare>::iterator it_start,
        std::set<Symbol,Symbol::compare>::iterator it_end );

    int subtable_size ( std::set <Symbol, Symbol::compare> partial_table, 
        std::set <Symbol,Symbol::compare>::iterator it_start,
        std::set<Symbol,Symbol::compare>::iterator it_end );

    void codify_huffman_partial ( std::set <Symbol, Symbol::compare> partial_table, 
        std::set<Symbol,Symbol::compare>::iterator it_start, 
        std::set<Symbol,Symbol::compare>::iterator it_end );

    bool codify_huffman();

    void printSymbols (std::ostream& ostream) const;

    friend std::ostream& operator<<(std::ostream&, const SymbolTable&);
};




#endif
