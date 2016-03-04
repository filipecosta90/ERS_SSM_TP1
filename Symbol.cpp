#include <iomanip>
#include <stddef.h>
#include <stdlib.h>
#include <iostream>
#include <stdio.h>
#include <wchar.h>
#include <map>
#include <set>
#include <bitset>         // std::bitset
#include <vector>

#include "Symbol.h"

Symbol::Symbol( ) {
  absolut_freq = 0;
  relative_freq = 0.0;
  codification = 0;
};

Symbol::Symbol( char32_t ch ) {
  character = ch;
  absolut_freq = 0;
  relative_freq = 0.0;
  codification = 0;
};

Symbol& Symbol::operator=( const Symbol& other ) {
  character = other.character;
  absolut_freq = other.absolut_freq;
  relative_freq = other.relative_freq;
  codification = other.codification;
  return *this;
}

/* increases the absolut frequency */
void Symbol::spotted() {
  absolut_freq++;
}

/* adds a new less significant bit*/
void Symbol::add_less_sig_bit( int bit ){
  if (bit == 0){
    codification = codification * 10;
  }
  else {
    codification++;
  }
}

char32_t Symbol::get_character() const {
  return character;
}

int Symbol::get_absolut_freq() const {
  return absolut_freq;
}

float Symbol::get_relative_freq() const {
  return relative_freq;
}

void Symbol::calculate_relative_freq ( int total_symbols ){
  relative_freq =  ( float) ( absolut_freq / (float)  total_symbols );
}

/* void Symbol::print_codification ( std::ostream& stream ) const {
  std::vector<int>::const_iterator it = codification.begin();
  for ( ; it != codification.end() ; ++it ){
    int bit = *it;
    stream << bit;
  }
} */

std::ostream& operator<< ( std::ostream& os, const Symbol& obj ){
  os << obj.get_character() << "\t" << obj.get_absolut_freq() << "\t" << std::fixed << std::setprecision(5) << obj.get_relative_freq() << "\t" << obj.codification  ;
  os << std::endl;
  return os;
}

