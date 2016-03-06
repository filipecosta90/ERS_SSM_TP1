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
  private:
    /* The set of symbols that the original file contains ordered by 
     * absolut frequency and by character if the frequency is equal*/
    std::set <Symbol, Symbol::compare> symbols_table;
    /* The number of distinct symbols read from the original file */
    int distinct_symbols;
    /* The total symbols read from the original file */
    int total_symbols;
    /* The huffman table for the symbols from the the original file */
    std::vector<Symbol> huffman_table;

  public:
    SymbolTable();
    void read_symbols( std::vector<char> symbols );
    int get_distinct_symbols() const;
    int get_total_symbols() const;
    void fill_bit ( std::vector <Symbol>& huffman_table,
        int start_position, int length , int value_bit);

    int table_frequency ( std::vector <Symbol>& partial_table, 
        int pos_start,
        int size
        );

    bool codify_huffman_partial ( std::vector <Symbol>& partial_table, 
        int pos_start, 
        int size );

    bool codify_huffman();

    std::vector <std::bitset<1>> encode_symbol ( char symbol);

    void print_huffman (std::ostream& ostream) ;

    void printSymbols (std::ostream& ostream) const;

    friend std::ostream& operator<<(std::ostream&, const SymbolTable&);
};

#endif
