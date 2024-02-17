#include <istream>
#include <FlexLexer.h>
#include <stdexcept>
#include "Parser2.hpp"
#include "Scanner2.hpp"

int main() {
  Assembler asmblr;
  vslasm::Scanner scanner{ std::cin, std::cerr };
  vslasm::Parser parser{ &scanner, &asmblr };
  std::cout.precision(10);
  parser.parse();
}
int yyFlexLexer::yylex() {
  throw std::runtime_error("Bad call to yyFlexLexer::yylex()");
}


