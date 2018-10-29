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
#include <string>
#include <sstream>
#include <utility>
#include <algorithm>

using namespace std::literals;

namespace abits {  
  namespace num_type {
    // Numeral system type constants
    // Integral value is the number of bits, length of bit field
    const int Base2 = 1;
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
  constexpr std::pair<int,int> map_code_char[] =
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

  constexpr static char getChar(int code, int range = map_size-1)
  {
    assert(range > -1 && range < map_size);
    return
      (code == map_code_char[range].first) ?
      map_code_char[range].second :
      getChar(code,range-1);
  }

  const static int getCode(char character, int range = map_size-1)
  {
    assert(range > -1 && range < map_size);
    return
      (character == map_code_char[range].second) ?
      map_code_char[range].first :
      getCode(character,range-1);
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
  template<int N, int T = num_type::Base16>
    class BaseEnc;

  template<int N>
    std::ostream& operator<<(std::ostream& os,
			     const BaseEnc<N>& obj);
  /* End of forward declarations */
  
  /**
   * This class is the root class of the library.  It represents a
   * public interface to the underlying bitset storage of the encoded
   * integer value.
   */
  template<int N, int T>
  class BaseEnc
  {
  private:
    std::bitset<N*T> store;
    std::string toString() const
      {
	return "toString() method call..."s;
      };
    std::bitset<N*T> stringToBits(const std::string str)
      {
	std::string revStr{str};
	assert(str.size() <= N);
	std::bitset<N*T> ret;

	std::reverse(revStr.begin(),revStr.end());

	for(auto ch : revStr)
	  {
	    int ichar = getCode(ch);
	    std::cout<< "ichar= "
		     << std::hex << ichar << "\n";
	    ret |= ichar;
	    ret <<= T;
	  }
	
	return ret;
      };

    std::string bitsToString()
      {
	std::stringstream ss;

	int i=N;
	while(i>0)
	  {
	    --i;
	    char ch = (char)(store & mask[T]);
	    ss << ch;
	    store <<= T;
	  }
	return ss.str();
      };
    
  public:
    // TODO(Todd): implement a default cstor
    BaseEnc() {};
    BaseEnc(const std::string value)
      {
	assert(T >= num_type::Base2 && T <= num_type::Base64);
	if(value.size() != N) throw("Bit limb size and string do no match");
	store = stringToBits(value);
      };
    int getBitLength()
    {
      return store.size();
    }
    int getCharLength()
    {
      return N;
    }
    std::bitset<T*N> getBitset()
      {
	return store;
      }
    friend std::ostream& operator<< <>(std::ostream& os,
				       const BaseEnc<N>& obj);
  };
  
  template<int N>
    std::ostream& operator<<(std::ostream& os,
			     const BaseEnc<N>& obj)
    {
      std::string out{obj.bitsToString()};
      os << out;
      return os;
    }
}
#endif
