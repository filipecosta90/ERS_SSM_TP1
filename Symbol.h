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

#ifndef SYMBOL_H
#define SYMBOL_H

class Symbol {
  private:
    char character;
    int absolut_freq;
    float relative_freq;
    std::vector<std::bitset<1>> codification;

  public:
    Symbol( char ch );
    Symbol( );
    Symbol& operator =(const Symbol &other);
    struct compare {
      bool operator()(const Symbol& a, const Symbol& b)const{
        if (a.relative_freq != b.relative_freq) {
          return a.relative_freq > b.relative_freq;
        }
        else {
          return a.character < b.character;
        }
      };
    };

    /* adds a new less significant bit*/
    void add_less_sig_bit( int s_bit );

    /* increases the absolut frequency */
    void spotted();

    char get_character() const;
    int get_absolut_freq() const ;
    float get_relative_freq() const;

    void calculate_relative_freq( int total_symbols );
    void print_codification (std::ostream& ostream) const;
    friend std::ostream& operator<< (std::ostream&, const Symbol&);
};


#endif
