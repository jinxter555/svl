#include <string>
#include <istream>
#include <sstream>
#include <FlexLexer.h>
#include "Parser2.hh"
#include "Scanner2.hh"
#include "assembler.hh"
#include  "assembler_interactive.hh"

#include "commandline.hh"
#include <readline/readline.h>

AssemblerInteractive ait(".vm_history", "asm> ");

extern char** AssemblerInteractive_command_completion(const char *text, int start, int end) ;
void setup_readline_autocomplete();


int main(int argc, char *argv[]) {
  PromptInteractive myprompt;
  Commandline cml(argc, argv);

  setup_readline_autocomplete();

  if(cml.infile_name !="")
    ait.load(cml.infile_name);
  if(cml.run) 
    ait.run_program();

  myprompt.load_history(ait);
  myprompt.ready(ait);
  myprompt.save_history(ait);

  return 0;
}

int yyFlexLexer::yylex() {
  throw std::runtime_error("Bad call to yyFlexLexer::yylex()");
}

void setup_readline_autocomplete() {
  ait.set_ui_commands();
  rl_attempted_completion_function
    = AssemblerInteractive_command_completion;

}