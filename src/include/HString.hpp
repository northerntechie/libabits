/**
 * VoxelArt Game
 *
 * Author: Todd Saharchuk, AScT.
 * Date:   July 18, 2018
 *
 * Hash String - HString.
 *
 * A class of a hash code using a subset of the ASCII
 * to be represented in a string.
 *
 */
#pragma once
#ifndef __LHSTRING_HPP__
#define __LHSTRING_HPP__

#include <string>
#include <ostream>
#include <random>
#include <bitset>

namespace twg {
  /**
   * This class stores a variable length string that 
   * represents a hascode in the ASCII range of [49,120]
   * This yields a fairly human-readable string version
   * of a hash.
   * The template parameter N determines the following
   * types:
   *     | 0: length is length of supplied string
   * N = |
   *     | >0: length is N
   *
   */
  template<int B, int N = 0>
  class HString
  {
  private:
    std::string value;
    std::bitset<N> bits;
    
  public:
    explicit HString(std::string&& value)
    {
      int length;
      if(N == 0 || N > value.length())
	length = value.length();
      else
	length = N;
      auto it = bits.begin();
      for(int i=0; i<length; i++)
	{
	  ;
	}
    };
    explicit HString(const std::string value)
      : value(value)
    {};
    /**
     * This function returns the human-readable
     * string.
     */
    std::string str() { return value; };
    static HString<B,N> hashString();
    std::string toString()
    {
      return value;
    };
  };
  
  template<int B, int N>
  HString<B,N> HString<B,N>::hashString()
  {
    std::string ret;
      
      std::random_device rd;
      std::uniform_int_distribution<int> dist(49,120);
      for(int i=0; i<N; i++)
	{
	  ret += (char)dist(rd);
	}
      return HString<B,N>(ret);
  };
} /* End of twg namespace */
#endif
    
