/**
 * Alphabet Bits Library (libabits)
 *
 * A header-only C++ library that represents different character
 * encoded alphabets, that includes the following built-in
 * alphabets:
 * 
 * - Binary                    2 bits/symbol
 * - Ternary, Octal            3 bits/symbol
 * - Quaternary, Hexadecimal   4 bits/symbol
 * - Quinary, Duotrigesimal    5 bits/symbol
 * - Senary, Tetrasexagesimal  6 bits/symbol
 *
 * The library is contained within a single include file (this file)
 * and is easily included in a project.
 * 
 * Unit tests can be found in the src/tests folder and a full
 * description of the library can be found in the README.md
 * file in the project root directory.
 *
 */
#pragma once

#ifndef __LIBABITS_HPP__
#define __LIBABITS_HPP__

#include <cassert>
#include <bitset>
#include <vector>
#include <map>
#include <string>
#include <sstream>
#include <utility>
#include <algorithm>

using namespace std::literals;

namespace abits {  
  namespace num_type {
    // Numeral system type constants
    // Integral value is the number of bits, length of bit field
    constexpr int Base2 = 1;
    const int binary = Base2;
    const int Base4 = 2;
    const int quaternary = Base4;
    const int Base8 = 3;
    const int octal = Base8;
    const int Base16 = 4;
    const int hexadecimal = Base16;
    const int Base32 = 5;
    const int duotrigesimal = Base32;
    const int Base64 = 6;
    const int tetrasexagesimal = Base64;    
  }

  // Base64 code to char (ASCII) constexpr map
  // All lower bases are subsets of the Base64
  // numeral type.
  const std::map<int,char> map_code_char =
    {                                               
      {0,'A'},{1,'B'},{2,'C'},{3,'D'},{4,'E'},      
      {5,'F'},{6,'G'},{7,'H'},{8,'I'},{9,'J'},      
      {10,'K'},{11,'L'},{12,'M'},{13,'N'},{14,'O'}, 
      {15,'P'},{16,'Q'},{17,'R'},{18,'S'},{19,'T'}, 
      {20,'U'},{21,'V'},{22,'W'},{23,'X'},{24,'Y'}, 
      {25,'Z'},{26,'a'},{27,'b'},{28,'c'},{29,'d'}, 
      {30,'e'},{31,'f'},{32,'g'},{33,'h'},{34,'i'},
      {35,'j'},{36,'k'},{37,'l'},{38,'m'},{39,'n'},
      {40,'o'},{41,'p'},{42,'q'},{43,'r'},{44,'s'},
      {45,'t'},{46,'u'},{47,'v'},{48,'w'},{49,'x'},
      {50,'y'},{51,'z'},{52,'0'},{53,'1'},{54,'2'},
      {55,'3'},{56,'4'},{57,'5'},{58,'6'},{59,'7'},
      {60,'8'},{61,'9'},{62,'+'},{63,'/'}
    };
  constexpr int map_size = sizeof(map_code_char) / sizeof(std::pair<int,int>);

  const static char get_char(int code, int range = map_size-1)
  {
    assert(range > -1 && range < map_size);
    auto it = map_code_char.find(code);
    if(it != map_code_char.end())
      return it->second;
    else
      {
	assert(false);
	return 0x00;
      }
  }

  const static int get_code(char character, int range = map_size-1)
  {
    assert(range > -1 && range < map_size);
    auto it = std::find_if(map_code_char.begin(),
			   map_code_char.end(),
			   [&character] (const std::pair<int,char>& pair) -> bool
			   {
			     return pair.second == character;
			   });
    if(it != map_code_char.end())
      return it->first;
    else
      {
	assert(false);
	return -1;
      }
  }
  
  constexpr static int mask[] =
    { 0x00,  /* Base0 */
      0x01,  /* Base2 */
      0x03,  /* Base4 */
      0x07,  /* Base8 */
      0x0F,  /* Base16 */
      0x1F,  /* Base32 */
      0x3F   /* Base64 */
    };
  
  /* Forward declarations */
  template<int T = num_type::Base16>
  class base_enc;
  
  template<int T>
  std::ostream& operator<<(std::ostream& os,
			   const base_enc<T>& obj);
  /* End of forward declarations */
  
  /**
   * This class is the root class of the library.  It represents a
   * public interface to the underlying bitset storage of the encoded
   * integer value.
   */
  template<int T>
  class base_enc
  {
  private:
    std::vector<bool> _store{};

    /**
     * char_insert inserts the binary underlying
     * representation least-bit first.
     */
    std::vector<bool>& char_insert(char ch, std::vector<bool>& vec)
    {
      int chh = ch;
      for(int i=0; i<T; i++)
	{
	  vec.push_back(chh & 0x01);
	  chh >>= 1;
	}
      return vec;
    };
    
  public:
    // TODO(Todd): implement a default ctor
    base_enc() {};
    base_enc(const std::string value)
      {
	assert(T >= num_type::Base2 && T <= num_type::Base64);
	_store = string_to_bits(value);
      };
    int get_bitlength()
    {
      return _store.size();
    };
    
    int get_charlength()
    {
      return T;
    };

    /**
     * This method produces a string representation of
     * the bit storage of the encoded string.
     *
     * Complexity: O(n) where n is the bit length of the
     * bit storage.
     *
     * @return a string representation of the bit storage.
     */
    std::string bitstring()
    {
      std::stringstream ss;

      for(bool b : _store)
	{
	  ss << (b == true) ? 1 : 0;
	}
      return ss.str();
    };

    /**
     * This method produces a vector<bool> object
     * derived from the supplied std::string.
     *
     *
     * @param str a std::string used to generate the 
     * bit representation using the underlying class
     * numeral type.
     */
    std::vector<bool> string_to_bits(const std::string& str)
    {
      std::vector<bool> ret;
      std::string revStr{str};
      std::reverse(revStr.begin(),revStr.end());
      
      for(auto ch : revStr)
	{
	  ret = char_insert(get_code(ch), ret);
	}
      return ret;
    };
    
    /**
     * This function converts the internal bit storage
     * to a string representation using the object
     * underlying numeral type.
     *
     * 
     */
    std::string bits_to_string() const
    {
      std::stringstream ss;
      std::vector<bool> bits{_store};
      
      int n = _store.size() / T;
      while(n>0)
	{
	  int ch = 0;
	  for(int i=0; i<T; i++)
	    {
	      ch <<= 1;
	      ch |= bits.back();
	      bits.pop_back();
	    }
	  ss << get_char(ch);
	  n--;
	}
      
      return ss.str();
    };
    
    friend std::ostream& operator<< <>(std::ostream& os,
				       const base_enc<T>& obj);
  };
  
  template<int N>
    std::ostream& operator<<(std::ostream& os,
			     const base_enc<N>& obj)
    {
      os << obj.bits_to_string();
      return os;
    }
}
#endif
