# Alphabits Library(libabits) - ASCII Variable Bitlength Encoder/Decoder #

A header-only C++ library that represents different character encoded alphabets, that includes the following built-in alphabets:
  
  * Base2    1 bit/symbol
  * Base4    2 bits/symbol
  * Base8    3 bits/symbol
  * Base16   4 bits/symbol
  * Base32   5 bits/symbol
  * Base64   6 bits/symbol
  * _
  
  
Each base smaller than the largest Base64 is a subset of the Base64 character encoding.  Specifically, the Base16 is not a hexamdecimal enumeration, i.e. 0-9,a-f.  Base16 is the first 16 characters of the larger Base64 encoding library.  The intent of the library is to store the Base64 (or smaller) encoding with the minimum amount of bits required using no compression.  The data store for this implementation is std::vector<bool>.

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

The library is contained within a single include file (this file) and is easily included in a project.  Unit tests can be found in the src/tests folder and a full description of the library can be found in the README.md file in the project root directory.

