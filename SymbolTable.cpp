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
#include <algorithm>    // std::for_each

#include "Symbol.h"
#include "SymbolTable.h"

SymbolTable::SymbolTable(){
  distinct_symbols = 0;
  total_symbols = 0;
};

bool SymbolTable::read_file( FILE* infile ){
  for ( char32_t wc; wc != WEOF; wc = getwc(infile) ){
    Symbol current( wc );
    std::set<Symbol, Symbol::compare>::const_iterator got = symbols_table.find (current);
    /* if the key doesn't exists*/
    if ( got == symbols_table.end() ){
      current.spotted();
      symbols_table.insert(current);
      distinct_symbols++;
    }
    /* if the key exists*/
    else {
      Symbol actual = *got;
      symbols_table.erase(got);
      actual.spotted();
      symbols_table.insert(actual);
    }
    total_symbols++;
  }
  fclose(infile);

  std::set<Symbol, Symbol::compare>::const_iterator it = symbols_table.begin();
  for ( ; it != symbols_table.end(); ++it )
  {
    Symbol actualSymbol = *it;
    symbols_table.erase(it);
    actualSymbol.calculate_relative_freq(total_symbols);
    symbols_table.insert(actualSymbol);
  }
  return EXIT_SUCCESS;
}

int SymbolTable::get_distinct_symbols() const {
  return distinct_symbols;
}

int SymbolTable::get_total_symbols() const {
  return total_symbols;
}

void SymbolTable::fill_bit ( std::vector <Symbol>& huffman_table, int start_position,
    int length, int value_bit ){
  for ( int pos = start_position; pos < (length+start_position) ; pos++ ){
    Symbol newS( huffman_table[pos] );
    newS.add_less_sig_bit( value_bit );
    huffman_table.at(pos) = newS;
  }
}

float SymbolTable::table_frequency ( 
    std::vector <Symbol>& partial_table, 
    int start,
    int size
    ){
  float accumulated_frequency = 0.0;
  for ( int pos = start ; pos < size ;  ++pos ){
    Symbol actualSymbol = huffman_table.at(pos);
    accumulated_frequency += actualSymbol.get_relative_freq();
  }
  return accumulated_frequency;
}

bool SymbolTable::codify_huffman_partial ( std::vector <Symbol>& huffman_table, int start_position, int end_position ){
  int size = end_position - start_position;
  if ( size  <= 1  ){ 
    return EXIT_SUCCESS;
  }
  else 
  {
    float accumulated_frequency = 0.0;
    float remaining_frequency = table_frequency ( huffman_table, start_position, size );
    int remaining_zero_elements = 0;
    int remaining_one_elements = size;
    int current_position = start_position;

    for ( ;  accumulated_frequency < remaining_frequency / 2.0 && current_position < size  ; ++current_position ){
      Symbol actual_symbol = huffman_table.at(current_position);
      float actual_frequency =  actual_symbol.get_relative_freq();
      accumulated_frequency += actual_frequency;
      remaining_zero_elements++;
      remaining_one_elements--;
    }

    if ( remaining_zero_elements > 1 ) {
       fill_bit ( huffman_table , start_position, remaining_zero_elements ,  0  );
      codify_huffman_partial ( huffman_table, start_position, remaining_zero_elements );   
    }
    if ( remaining_one_elements > 0 ){
      fill_bit ( huffman_table , start_position+remaining_zero_elements, remaining_one_elements ,  1 );
      codify_huffman_partial ( huffman_table, remaining_zero_elements ,  size );
    }
  }
}

bool SymbolTable::codify_huffman ( ){
  std::set<Symbol, Symbol::compare>::const_iterator it = symbols_table.begin();
  for ( ; it != symbols_table.end() ; ++it ){
    Symbol actualSymbol = *it;
      std::vector<Symbol>::iterator it = huffman_table.begin();

    huffman_table.push_back( actualSymbol );
  }
  int size = huffman_table.size();

  codify_huffman_partial ( huffman_table, 0 , size );   
  return EXIT_SUCCESS;
}

void SymbolTable::print_huffman( std::ostream& stream ) {
  
  for ( int pos=0; pos < huffman_table.size() ; ++pos )
  {
    stream <<  huffman_table.at(pos);
  }
}


void SymbolTable::printSymbols( std::ostream& stream ) const {
  std::set<Symbol, Symbol::compare>::const_iterator it = symbols_table.begin();
  for ( ; it != symbols_table.end(); ++it )
  {
    Symbol actualSymbol = *it;
    stream << actualSymbol;
  }
}

std::ostream& operator<< (std::ostream& os, const SymbolTable& obj) {
  os << "------------------" << std::endl;
  obj.printSymbols( os );
  os << "------------------" << std::endl;
  os <<  "total caracteres: " << obj.get_total_symbols()  << std::endl;  
  os <<  "total caracteres distintos: " << obj.get_distinct_symbols()  << std::endl;
  return os;
}

