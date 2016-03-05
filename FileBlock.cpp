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
#include <iostream>     // std::cout
#include <fstream>      // std::filebuf, std::ifstream

#include "FileBlock.h"
#include "SymbolTable.h"

FileBlock::FileBlock( 
    std::string input, 
    int number, int start, int end
    ){
  input_name = input;
  block_number = number;
  block_start = start;
  block_end = end;
};

void FileBlock::read_chars( ){
  std::ifstream ifs ( input_name , std::ifstream::binary | std::ifstream::in  );
  ifs.seekg (block_start, std::ios::cur);
  int blocksize = block_end - block_start;
  std::cout << "\tFileBlock Reading " << blocksize << "(" << block_start << "," << block_end<< ")" << std::endl;
  input_chars.resize(blocksize);

  ifs.read(&input_chars[0], blocksize);
  std::cout << "\t\tblock chars size: " << input_chars.size() << '\n';

}

/*
// get pointer to associated buffer object
std::filebuf* pbuf = ifs.rdbuf();

for ( char32_t wc; wc != WEOF; wc = getwc( i) ){
Symbol current( wc );
std::set<Symbol, Symbol::compare>::const_iterator got = symbols_table.find (current);
if ( got == symbols_table.end() ){
current.spotted();
symbols_table.insert(current);
distinct_symbols++;
}
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
int end_position, int value_bit ){
for ( int pos = start_position; pos < end_position ; pos++ ){
Symbol newS( huffman_table[pos] );
newS.add_less_sig_bit( value_bit );
huffman_table.at(pos) = newS;
}
}

int SymbolTable::table_frequency ( 
std::vector <Symbol>& partial_table, 
int start,
int end
){
int accumulated_frequency = 0;
for ( int pos = start ; pos < end ;  ++pos ){
Symbol actualSymbol = huffman_table.at(pos);
accumulated_frequency += actualSymbol.get_absolut_freq();
}
return accumulated_frequency;
}

bool SymbolTable::codify_huffman_partial ( std::vector <Symbol>& huffman_table, int start_position, int end_position ){
int accumulated_frequency = 0;
int remaining_frequency = table_frequency ( huffman_table, start_position, end_position );
int current_position = start_position;

for ( ;  accumulated_frequency < remaining_frequency / 2.0 && current_position < end_position  ; ++current_position ){
Symbol actual_symbol = huffman_table.at(current_position);
int actual_frequency =  actual_symbol.get_absolut_freq();
accumulated_frequency += actual_frequency;
}

int zero_end_position = current_position  ;
int one_start_position = zero_end_position  ;
//std::cout << "zero: (" << start_position << ","<< zero_end_position  << ") one: (" << one_start_position << "," << end_position << ")" << std::endl ;

fill_bit ( huffman_table , start_position, zero_end_position ,  0 );
fill_bit ( huffman_table , one_start_position , end_position ,  1 );

if ( zero_end_position - start_position > 1 ) {
  codify_huffman_partial ( huffman_table, start_position , zero_end_position );   
}
if ( end_position - one_start_position > 1  ){
  codify_huffman_partial ( huffman_table, one_start_position ,  end_position );
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

  codify_huffman_partial ( huffman_table, 0 , size  );   
  return EXIT_SUCCESS;
}

void SymbolTable::print_huffman( std::ostream& stream ) {
  stream << "---------------------" << std::endl;
  stream << "Codificação de Hufman" << std::endl;
  stream << "---------------------" << std::endl;
  for ( int pos=0; pos < huffman_table.size() ; ++pos )
  {
    stream <<  huffman_table.at(pos);
  }
  stream << "---------------------" << std::endl;

}


void SymbolTable::printSymbols( std::ostream& stream ) const {
  std::set<Symbol, Symbol::compare>::const_iterator it = symbols_table.begin();
  for ( ; it != symbols_table.end(); ++it )
  {
    Symbol actualSymbol = *it;
    stream << actualSymbol;
  }
}
*/

std::ostream& operator<< (std::ostream& os, const FileBlock& obj) {
  os << "--------------------" << std::endl;
  return os;
}

