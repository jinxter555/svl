#include <string>
#include <istream>
#include <sstream>
#include <fstream>
#include <readline/readline.h>


#include "commandline.hh"

#include "svlm_ast.hh"
#include "svlm_interactive.hh"


#define DEBUG_TRACE_FUNC
#include "scope_logger.hh"







//extern char** AssemblerInteractive_command_completion(const char *text, int start, int end) ;

//void setup_readline_autocomplete(LangPrompt *lp);
void asm_setup_readline_autocomplete();
void svlm_setup_readline_autocomplete();
PromptSwitch p_run(LangPrompt *lp, const Commandline& cml) ;
PromptSwitch p_run_init(LangPrompt *lp, const Commandline& cml) ;



int main(int argc, char *argv[]) {

  bool init_flag = true;

  log_output.open("svlm.log", std::ios::out);
  trace_function.open("svlm_trace.log", std::ios::out);

  Commandline cml(argc, argv);
  PromptSwitch ps = PromptSwitch::begin;



  MYLOGGER(trace_function, "int main", __func__);



  while(ps != PromptSwitch::exit) {
    if(cml.assembly_lang) {
      //lang_it = &ait;
      asm_setup_readline_autocomplete(); // switch to lang_it pointer
    } else if( cml.svlm_lang) {
      lang_it = &svlm_it;
      svlm_setup_readline_autocomplete();
    } else {
      std::cerr << "lang not specified! \n";
      return(1); 
    }
    if(init_flag) {
      ps = p_run_init(lang_it, cml);
      init_flag=false;
    }
    else
      ps = p_run(lang_it, cml);

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

PromptSwitch p_run_init(LangPrompt *lp, const Commandline& cml) {
  if(cml.infile_name !="") lp->load(cml.infile_name);
  if(cml.run) lang_it->run_program("");
  return p_run(lp, cml);
}

PromptSwitch p_run(LangPrompt *lp, const Commandline& cml) {
  PromptSwitch ps;
  myprompt.load_history(*lp);
  ps = myprompt.ready(*lp);
  myprompt.save_history(*lp);
  return ps;
}


void asm_setup_readline_autocomplete() {
  //ait.set_ui_commands();
  //rl_attempted_completion_function = ait.command_completion;
}
void svlm_setup_readline_autocomplete() {
  svlm_it.set_ui_commands();
  rl_attempted_completion_function = svlm_it.command_completion;
}


//----------------
int yyFlexLexer::yylex() { throw std::runtime_error("Bad call to yyFlexLexer::yylex()"); }


//int AsmFlexLexer::yylex() { throw std::runtime_error("Bad call to AsmFlexLexer::yylex()"); }