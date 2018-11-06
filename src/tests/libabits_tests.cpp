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
#include <functional>
#include <sstream>
#include <libabits.hpp>
#include <cassert>

using namespace std::literals;

template<typename T, typename R>
class Test
{
private:
  std::function<T> _test;
  R _expectedResult;
  bool _result;
  std::string _name;
  
public:
  explicit Test(std::function<T>& test,
		R& expectedResult,
		std::string& name = "anon")
    : _test(test),
      _expectedResult(expectedResult),
      _result(false),
      _name(name)
  {};

  template<typename... Targs>
  Test<T,R>& run_test(Targs... args)
  {
    _result = test(args...) == _expectedResult;
    return *this;
  }

  template<typename Type, typename Result>
  friend std::string to_string(Test<Type,Result>& test);
};

template<typename T, typename R>
std::string to_string(Test<T,R>& test)
{
  std::stringstream ss;

  ss << "Test: " << test._name;
  return ss.str();
}

template<typename Test, typename Result>
const bool test(const Test test, const Result result)
{
  return test == result;
}

std::string process(const bool test,
		    const std::string name = "anon"s)
{
  std::stringstream ss;
  ss << name << ": ";
  ss << ((test) ? "Passed" : "Failed");
  ss << "\n";
  return ss.str();
}

// TODO(): Simplify
template<typename O, typename T, typename R>
bool runObjectTest(O obj,
		   const std::vector<R> results,
		   const std::vector<std::string> titles)
{
  bool retVal = true;
  std::string result = process(test<T,R>
		       (obj.bits_to_string(),
			results[0]),
		       titles[0]);
  if(result == "Failed"s) retVal = false;
  std::cout << result;
  result = process(test<T,std::string>
		   (obj.bitstring(),
		    results[1]),
		   titles[1]);
  if(result == "Failed"s) retVal = false;
  std::cout << result;
  result = process(test<std::string,std::string>
		   (obj.get_numeral_string(),
		    results[2]),
		   titles[2]);
  if(result == "Failed"s) retVal = false;
  std::cout << result;

  return retVal;
};

int main()
{
  // Base2 Tests
  abits::base64_enc<abits::num_type::Base2> testBase2{"ABAAAAB"};
  runObjectTest<abits::base64_enc<abits::num_type::Base2>,
		std::string,std::string>
    (testBase2,
    {"ABAAAAB"s,"1000010"s,"abits::num_type::Base2"s},
    {"test1.bits_to_string()"s,"test1.bitstring()"s,"test1.get_numeral_string()"s});
	 
  // Base4 Tests
  abits::base64_enc<abits::num_type::Base4> testBase4{"ABCDCBA"};
  runObjectTest<abits::base64_enc<abits::num_type::Base4>,
		std::string,std::string>
    (testBase4,
    {"ABCDCBA"s,"00100111011000"s,"abits::num_type::Base4"s},
    {"test2.bits_to_string()"s,"test2.bitstring()"s,"test2.get_numeral_string()"s});  
  
}
