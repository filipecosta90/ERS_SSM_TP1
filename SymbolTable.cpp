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
      Symbol actual = *got;
      symbols_table.erase(got);
      actual.spotted();
      symbols_table.insert(actual);
    }
    total_symbols++;
  }
  fclose(infile);

  std::set<Symbol, Symbol::compare>::iterator it = symbols_table.begin();
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

void SymbolTable::fill_bit ( std::set <Symbol,Symbol::compare>::iterator it_start, 
    std::set<Symbol,Symbol::compare>::iterator it_end, std::bitset<1> value_bit ){
  std::set<Symbol, Symbol::compare>::iterator it_current = it_start ;

  for ( ; it_current != it_end; ++it_current ){
    Symbol actualSymbol = *it_current;
    symbols_table.erase(it_current);
    actualSymbol.add_less_sig_bit( value_bit );
    symbols_table.insert(actualSymbol);

  }
}


float SymbolTable::table_frequency ( std::set <Symbol, Symbol::compare> partial_table, 
    std::set <Symbol,Symbol::compare>::iterator it_start, 
    std::set<Symbol,Symbol::compare>::iterator it_end ){

  int remaining_elements = std::distance(it_start,it_end);

  std::set<Symbol, Symbol::compare>::iterator it_current = it_start ;
  float accumulated_frequency = 0.0;
  for ( ; remaining_elements > 0; ++it_current, remaining_elements-- ){
    Symbol actualSymbol = *it_current;
    accumulated_frequency += actualSymbol.get_relative_freq();
  }
  return accumulated_frequency;
}

bool SymbolTable::codify_huffman_partial ( std::set <Symbol, Symbol::compare> partial_table, 
    std::set<Symbol,Symbol::compare>::iterator it_start, 
    std::set<Symbol,Symbol::compare>::iterator it_end, int size ){
  int remaining_elements = std::distance(it_start,it_end);

  if ( size < 2  ){ 
    return EXIT_SUCESS;
  }
  else 
  {
  std::set<Symbol, Symbol::compare>::iterator it_current, it_one_start, it_zero_end;
  float accumulated_frequency = 0.0;
  float remaining_frequency = table_frequency ( partial_table, it_start, it_end );
  it_current =  it_start;


  
  for ( ;  accumulated_frequency < remaining_frequency / 2.0 && remaining_elements > 0 ; ++it_current, remaining_elements-- ){
    Symbol actual_symbol = *it_current;
    float actual_frequency =  actual_symbol.get_relative_freq();
    accumulated_frequency += actual_frequency;
  }
  it_one_start = it_current;
  int remaining_zero_elements = std::distance(it_start,it_one_start);
  int remaining_one_elements = std::distance(it_one_start, it_end);
  std::cout << "Remaining 0s: " << remaining_zero_elements << " Remaining 1s: " << remaining_one_elements <<  std::endl;
  std::bitset<1> b0 ("0");
  std::bitset<1> b1 ("1");
  if ( remaining_zero_elements > 1 ) {
    fill_bit ( it_start , it_zero_end ,  b0  );
    codify_huffman_partial ( partial_table, it_start, it_one_start );   
  }
  if ( remaining_one_elements > 0 ){
    fill_bit ( it_one_start , it_end ,  b1 );
    codify_huffman_partial ( partial_table, it_one_start , it_end );   
  }
  }
}

bool SymbolTable::codify_huffman ( ){
  std::set<Symbol, Symbol::compare>::iterator table_start = symbols_table.begin();
  std::set<Symbol, Symbol::compare>::iterator table_end = symbols_table.end();
  int size = symbols_table.size();
  codify_huffman_partial ( symbols_table, table_start, table_end, size );   
  return EXIT_SUCCESS;
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

