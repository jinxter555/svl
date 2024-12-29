#include <cassert>
#include "operand.hh"

#include <catch2/catch_all.hpp>

std::uint64_t Fibonacci(std::uint64_t number) {
    return number < 2 ? 1 : Fibonacci(number - 1) + Fibonacci(number - 2);
}

TEST_CASE("Fibonacci") {
    CHECK(Fibonacci(0) == 1);
    // some more asserts..
    CHECK(Fibonacci(5) == 8);
    // some more asserts..
}

int main(int argc, char *argv[]) {
  Operand i1(11l);
  cout << "i1: " << i1 << "\n";
  Operand f1(12.345);
  cout << "f1: " << f1 << "\n";
  Operand s1(string("str1"));
  cout << "s1: " << s1 << "\n";
  Operand s2(string("str2"));
  cout << "s2: " << s2 << "\n";
  Operand s3("str3");
  Operand s4("str4");

  Operand sh_i1(make_shared<Operand>(123456789l));
  cout << "sh_i1: " << sh_i1 << "\n";
  Operand n;
  cout << "n: " << n<< "\n";



  Catch::Session session; // There must be exactly one instance

  // writing to session.configData() here sets defaults
  // this is the preferred way to set them

  int returnCode = session.applyCommandLine( argc, argv );
  if( returnCode != 0 ) // Indicates a command line error
        return returnCode;

  // writing to session.configData() or session.Config() here
  // overrides command line args
  // only do this if you know you need to

  int numFailed = session.run();

  // numFailed is clamped to 255 as some unices only use the lower 8 bits.
  // This clamping has already been applied, so just return it here
  // You can also do any post run clean-up here
  return numFailed;

  //vector<Operand> l1 = { make_unique<Operand>("hello"), make_unique<Operand>("world")};
  //auto l1a = {Operand(string("hello")), Operand(string("world"))};
  //auto l1b = {Operand("hello"), Operand("world")};
  //auto l1c = { make_unique<Operand>("hello"), make_unique<Operand>("world")};
  //vector<Operand> l1a = {Operand(string("hello55")), Operand(string("world66"))};




  return 0;
}
