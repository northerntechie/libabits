/**
 * This is the unit test file for the liabits header-only
 * C++ library.  It strives for correctness at the bounds of
 * the expected values, and some random readable values for
 * examples.  But it does not cover all possible values or
 * cases.
 *
 * Each test is sent to stdout.
 * If all tests past, a final 'all=true' is output and the
 * unit test terminates.
 */
#include <iostream>
#include <libabits.h>

int main()
{
  // Construct an BaseEnc
  std::cout << "BaseEnc(\"Hello\"s)= " ;
  abits::BaseEnc<4,abits::num_type::hexadecimal> string1{"help"};
  std::cout << string1 << "\n";
  std::cout << "string1.getBitLength()= "
	    << string1.getBitLength() << "\n";
  std::cout << "string1.getCharLength()= "
	    << string1.getCharLength() << "\n";
  std::cout << "static getChar()test...\n"
	    << "pos=23: " << abits::getChar(23) << "\n";
  std::cout << "getCode('H')= "
	    << abits::getCode('H') << "\n";
  std::cout << "bitset of string1= "
	    << string1.getBitset().to_string() << "\n";
  //std::cout << "pos=64(out of bounds): " // error
  // << abits::getChar(64) << "\n";
}
