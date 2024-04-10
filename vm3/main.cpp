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

PromptInteractive myprompt;
LangPrompt *lang_it = &ait;

//extern char** AssemblerInteractive_command_completion(const char *text, int start, int end) ;

//void setup_readline_autocomplete(LangPrompt *lp);
void asm_setup_readline_autocomplete();
void svlm_setup_readline_autocomplete();
PromptSwitch prun(LangPrompt *lp, const Commandline& cml) ;


int main(int argc, char *argv[]) {
  Commandline cml(argc, argv);
  PromptSwitch ps = PromptSwitch::begin;

  Instruction::setup();

  while(ps != PromptSwitch::exit) {
    if(cml.assembly_lang) {
      lang_it = &ait;
      asm_setup_readline_autocomplete(); // switch to lang_it pointer
    } else if( cml.svlm_lang) {
      lang_it = &svlm_it;
      svlm_setup_readline_autocomplete();
    } else {
      std::cerr << "lang not specified! \n";
      return(1); 
    }
    ps = prun(lang_it, cml);

    switch(ps) {
    case PromptSwitch::svlm:
      cml.assembly_lang = false;
      cml.svlm_lang = true;
      break;
    case PromptSwitch::vasm:
      cml.assembly_lang = true;
      cml.svlm_lang = false;
      break;
    default: break;
    }
  }

  return 0;
}

PromptSwitch prun(LangPrompt *lp, const Commandline& cml) {
  PromptSwitch ps;
  if(cml.infile_name !="") lp->load(cml.infile_name);
  if(cml.run) lang_it->run_program();
  myprompt.load_history(*lp);
  ps = myprompt.ready(*lp);
  myprompt.save_history(*lp);
  return ps;
}


void asm_setup_readline_autocomplete() {
  ait.set_ui_commands();
  rl_attempted_completion_function = ait.command_completion;
}
void svlm_setup_readline_autocomplete() {
  svlm_it.set_ui_commands();
  rl_attempted_completion_function = svlm_it.command_completion;
}


//----------------
int yyFlexLexer::yylex() { throw std::runtime_error("Bad call to yyFlexLexer::yylex()"); }
int AsmFlexLexer::yylex() { throw std::runtime_error("Bad call to AsmFlexLexer::yylex()"); }