#include <stddef.h>
#include <stdlib.h>
#include <iostream>
#include <stdio.h>
#include <map>
#include <set>
#include <string.h>
#include <bitset>         // std::bitset
#include <vector>
#include <algorithm>    // std::for_each
#include <math.h>       // log2
#include <iostream>     // std::cout
#include <fstream>      // std::ifstream

#include "FileCompress.h"

FileCompress::FileCompress( std::string input, std::string output, int size_block ){
  input_file = input;
  output_file = output;
  block_size = size_block;
  number_blocks = 0;
};

bool FileCompress::write_file(){
  std::ofstream ofs( output_file.c_str() , std::ios_base::binary );
  std::vector <std::bitset<8>>::iterator it = output_bytes.begin();
  for ( ; it != output_bytes.end(); ++it ){
    std::bitset<8> current_byte = *it;
    char byte_char = current_byte.to_ulong(); 
    ofs.write( &byte_char, 1);
  }
  ofs.close();
  return true;
}

bool FileCompress::read_file(){
  std::ifstream ifs ( input_file, std::ifstream::binary | std::ifstream::in  );
  ifs.seekg (0, ifs.end);
  input_file_size = ifs.tellg();
  int current_block_start = 0;
  int current_block_end = block_size;
  int left_file_size = input_file_size;
  int next_block_size;
  for ( int block = 0; left_file_size > 0 ; block++ ){
    if (left_file_size > block_size){
      left_file_size = left_file_size - block_size;
      next_block_size = block_size;
    }
    else {
      next_block_size = left_file_size;
      left_file_size = 0;
    }
    current_block_end = current_block_start + next_block_size;
    FileBlock new_block ( input_file, block,  current_block_start ,current_block_end );  
    new_block.read_chars();
    new_block.produce_symbols();
    table_blocks.push_back(new_block);
    current_block_start+=block_size;
    number_blocks++;
  }
  return true;
}

bool FileCompress::codify_huffman(){
  for ( std::vector<FileBlock>::iterator it = table_blocks.begin() ; it != table_blocks.end(); ++it){
    it->codify_huffman();
  }
  return true;
}

bool FileCompress::produce_bitstream(){
  std::vector<FileBlock>::iterator it = table_blocks.begin();
  for ( ; it != table_blocks.end(); ++it )
  {
    FileBlock current_block = *it;
    current_block.produce_bitstream();
    std::vector<std::bitset<1>> block_bitset = current_block.get_bitstream();
    output_encoding.insert( output_encoding.end(), block_bitset.begin(), block_bitset.end() );
  }
  std::vector<std::bitset<1>>::iterator output_bits = output_encoding.begin();
  for ( ; output_bits != output_encoding.end(); ){
    // current_byte: 00000000
    std::bitset<8> current_byte;
    int byte_pos = 0;
    for ( ; output_bits != output_encoding.end() && byte_pos < 8 ; ++output_bits,++byte_pos ){
      std::bitset<1> current_bit = *output_bits;
      current_byte.set(byte_pos,current_bit.to_ulong());

    }
    output_bytes.push_back(current_byte);
  }
  output_file_size = output_bytes.size();
  std::cout << "Final bitstream size: " << output_file_size << std::endl;
}

int FileCompress::get_input_file_size() const {
  return  input_file_size;
}

int FileCompress::get_output_file_size() const {
  return  output_file_size;
}

int FileCompress::get_number_blocks() const {
  return number_blocks;
}

int FileCompress::get_block_size() const {
  return block_size;
}

float FileCompress::get_compression_ratio() const {
  return ( input_file_size - output_file_size ) / input_file_size * 100 ; 
}

void FileCompress::print_encoding( std::ostream& stream ) const  {
  std::vector<FileBlock>::const_iterator it = table_blocks.begin();
  for ( ; it != table_blocks.end(); ++it )
  {
    FileBlock actual_block = *it;
    actual_block.print_fileblock_symbols( stream );
  }
}

void FileCompress::print_compression( std::ostream& stream ) const {
  std::vector<FileBlock>::const_iterator it = table_blocks.begin();
  for ( ; it != table_blocks.end(); ++it )
  {
    FileBlock actual_block = *it;
    stream << actual_block;
  }
}

std::ostream& operator<< (std::ostream& os, const FileCompress& obj) {
  os << "----------------------" << std::endl;
  os << "File Compressor" << std::endl;
  os << "----------------------" << std::endl;
  os << "File Size: " << obj.get_input_file_size() <<std::endl;
  os << "# Blocks: " << obj.get_number_blocks() << "("<< obj.get_block_size() << ")"<<std::endl;
  os << "----------------------" << std::endl;
  os << "Compression By Blocks" << std::endl;
  obj.print_compression( os );
  os << "----------------------" << std::endl;
  os << "Obtained Compression: " << obj.get_compression_ratio() << std::endl;
  os << "Output File Size: " << obj.get_output_file_size() << std::endl;
  os << "----------------------" << std::endl;
  return os;
}

