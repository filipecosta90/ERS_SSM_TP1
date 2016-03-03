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

Symbol::Symbol( char32_t ch ) {
  character = ch;
};

/* increases the absolut frequency */
void Symbol::spotted() {
  absolut_freq++;
}

/* adds a new less significant bit*/
void Symbol::add_less_sig_bit( std::bitset<1> s_bit ){
  std::vector<std::bitset<1>>::iterator it;
  it = codification.end();
  codification.insert ( it , s_bit );
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


std::ostream& operator<< ( std::ostream& os, const Symbol& obj ){
  
  os << obj.get_character() << "\t" << obj.get_absolut_freq();
  os << std::endl;
  return os;
}

