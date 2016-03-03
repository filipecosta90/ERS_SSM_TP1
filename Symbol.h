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

// A2DD.h
#ifndef SYMBOL_H
#define SYMBOL_H

class Symbol {
  private:
    char32_t character;
    int absolut_freq;
    float relative_freq;
    std::vector < std::bitset<1>> codification;

  public:
    Symbol( char32_t ch );
    struct compare {
      bool operator()(const Symbol& a, const Symbol& b)const
      {if (a.relative_freq != b.relative_freq) return a.relative_freq > b.relative_freq;
        return a.character > b.character;
      };
    };

    /* adds a new less significant bit*/
    void add_less_sig_bit( std::bitset<1> s_bit );

    /* increases the absolut frequency */
    void spotted();

    char32_t get_character() const;
    int get_absolut_freq() const ;
    float get_relative_freq() const;

    friend std::ostream& operator<< (std::ostream&, const Symbol&);
};


#endif
