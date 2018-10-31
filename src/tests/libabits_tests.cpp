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
#include <libabits.hpp>

int main()
{
  // Construct an BaseEnc
  std::cout << "base_enc(\"help\"s)= " ;
  abits::base_enc<abits::num_type::Base64> string1{"Thisisatestofthecapabilitiesoftheabitslibrary"};
  std::cout << string1 << "\n";
  std::cout << "string1.get_bitlength()= "
	    << string1.get_bitlength() << "\n";
  std::cout << "string1.get_charlength()= "
	    << string1.get_charlength() << "\n";
  std::cout << "static get_char()test...\n"
	    << "pos=23: " << abits::get_char(23) << "\n";
  std::cout << "get_code('H')= "
	    << abits::get_code('H') << "\n";
  std::cout << "bitset of string1= "
	    << string1.bitstring() << "\n";
  std::cout << "string of string1= "
	    << string1 << "\n";
  //std::cout << "pos=64(out of bounds): " // error
  // << abits::getChar(64) << "\n";
}
