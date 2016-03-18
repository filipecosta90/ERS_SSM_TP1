#include <stddef.h>
#include <stdlib.h>
#include <iostream>
#include <stdio.h>
#include <set>
#include <string.h>
#include <bitset>         // std::bitset
#include <vector>
#include <algorithm>    // std::for_each
#include <fstream>      // std::filebuf, std::ifstream

#include <iomanip>
#include <locale>
#include <sstream>
#include <string> // this should be already included in <sstream>
#include "FileBlock.h"
#include "SymbolTable.h"
#include <math.h>       /* log2 */

FileBlock::FileBlock( 
    std::string input, 
    int number, int start, int end
    ){
  input_name = input;
  block_number = number;
  block_start = start;
  block_end = end;
  input_bits_size = 0.0;
  output_bits_size = 0.0;
  compression_ratio;
};

void FileBlock::read_chars( ){
  std::ifstream ifs ( input_name , std::ifstream::binary | std::ifstream::in  );
  ifs.seekg (block_start, std::ios::cur);
  int blocksize = block_end - block_start;
  input_chars.resize(blocksize);
  ifs.read(&input_chars[0], blocksize);
  input_bits_size = input_chars.size() * sizeof (char) * 8;
}

void FileBlock::produce_symbols(){
  symbol_table.read_symbols(input_chars);
}

void FileBlock::codify_huffman(){
  symbol_table.codify_huffman();
}

void FileBlock::produce_bitstream(){
  std::vector<std::bitset<1>> header_encoded;
  symbol_table.produce_header();
  header_encoded = symbol_table.get_header(); 
  output_bits.insert( output_bits.end(), header_encoded.begin(), header_encoded.end() );
  std::vector<char>::iterator it = input_chars.begin();
  for  ( ; it != input_chars.end() ; ++it )
  {
    std::vector<std::bitset<1>> char_encoded;
    char symbol_char = *it;
    char_encoded = symbol_table.encode_symbol ( symbol_char );
    output_bits.insert( output_bits.end(), char_encoded.begin(), char_encoded.end() );
  }
  output_bits_size = output_bits.size() ; 
}

std::vector <std::bitset<1>> FileBlock::get_bitstream() const {
  return output_bits;
}

int FileBlock::get_block_number() const {
  return block_number;
}

float FileBlock::get_compression_ratio() const  {
  float comp = output_bits_size / input_bits_size;
  return comp; 
}

float FileBlock::get_input_bits_size() const { 
  return input_bits_size;
}

float FileBlock::get_output_bits_size() const {
  return output_bits_size;
}

void  FileBlock::print_fileblock_symbols (std::ostream& ostream) const {
  symbol_table.printSymbols( ostream );
}

std::ostream& operator<< (std::ostream& os, const FileBlock& obj) {
  os << "\t#" << obj.get_block_number() << " Compression Ratio: " <<obj.get_compression_ratio() <<"(" << obj.get_input_bits_size() << "/" << obj.get_output_bits_size() << ")"<< std::endl;
  return os;
}

