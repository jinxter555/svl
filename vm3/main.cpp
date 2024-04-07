#include <string>
#include <istream>
#include <sstream>
#include <readline/readline.h>

#include "assembler.hh"
#include  "assembler_interactive.hh"

#include "commandline.hh"

#include "svlm_lang.hh"
#include "svlm_interactive.hh"

AssemblerInteractive ait(".vm_history", "asm> ");
SvlmInteractive svlm_it(".svlm_history", "svlm> ");

extern char** AssemblerInteractive_command_completion(const char *text, int start, int end) ;

void asm_setup_readline_autocomplete();
void svlm_setup_readline_autocomplete();


int main(int argc, char *argv[]) {
  PromptInteractive myprompt;
  Commandline cml(argc, argv);

  Instruction::setup();



  if(cml.assembly_lang) {
    if(cml.infile_name !="")
      ait.load(cml.infile_name);

    if(cml.run) 
      ait.run_program();
    asm_setup_readline_autocomplete();
    myprompt.load_history(ait);
    myprompt.ready(ait);
    myprompt.save_history(ait);
  } else if( cml.svlm_lang) {
    if(cml.infile_name !="")
      svlm_it.load(cml.infile_name);

    svlm_setup_readline_autocomplete();
    myprompt.load_history(svlm_it);
    myprompt.ready(svlm_it);
    myprompt.save_history(svlm_it);
  } else {
    std::cerr << "specify lang option\n";
  }

  return 0;
}

int yyFlexLexer::yylex() { throw std::runtime_error("Bad call to yyFlexLexer::yylex()"); }
int AsmFlexLexer::yylex() { throw std::runtime_error("Bad call to AsmFlexLexer::yylex()"); }

void asm_setup_readline_autocomplete() {
  ait.set_ui_commands();
  rl_attempted_completion_function
    = AssemblerInteractive_command_completion;
}
void svlm_setup_readline_autocomplete() {
  svlm_it.set_ui_commands();
  rl_attempted_completion_function
    = SvlmInteractive::command_completion;
}