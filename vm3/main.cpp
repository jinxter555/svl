#include <string>
#include <istream>
#include <sstream>
#include <FlexLexer.h>
#include "Parser2.hh"
#include "Scanner2.hh"
#include "assembler.hh"
#include  "assembler_interactive.hh"

#include "commandline.hh"

int main(int argc, char *argv[]) {
  PromptInteractive myprompt;
  Commandline cml(argc, argv);
  AssemblerInteractive ait(".vm_history", "asm> ");

  if(cml.infile_name !="")
    ait.load(cml.infile_name);
  if(cml.run) 
    ait.run_program();

  myprompt.load_history(ait);
  myprompt.ready(ait);
  myprompt.save_history(ait);

  return 0;
}
/*

int main2() {
  Assembler asmblr;

  //vslasm::Scanner scanner{ std::cin, std::cerr };
  //vslasm::Parser parser{ &scanner, &asmblr };

  vslasm::Scanner *scanner;
  scanner = new vslasm::Scanner{ std::cin, std::cerr };
  vslasm::Parser parser2{ scanner, &asmblr };
  vslasm::Parser *parser = &parser2;

  std::string test_string = "add r1, r2\nSUB 3, 4, 5";
  std::istringstream input_buffer(test_string);
  scanner->switch_streams(&input_buffer, NULL);
  std::cout.precision(10);
  parser->parse();

  scanner->switch_streams(&std::cin, &std::cerr);
  parser->parse();


}
*/

int yyFlexLexer::yylex() {
  throw std::runtime_error("Bad call to yyFlexLexer::yylex()");
}

/*

int main() {
  Assembler asmblr;

  vslasm::Scanner scanner{ std::cin, std::cerr };
  vslasm::Parser parser{ &scanner, &asmblr };


  std::string test_string = "add r1, r2\nSUB 3, 4, 5";
  std::istringstream input_buffer(test_string);
  scanner.switch_streams(&input_buffer, NULL);
  std::cout.precision(10);
  parser.parse();

  scanner.switch_streams(&std::cin, &std::cerr);
  parser.parse();


}
*/