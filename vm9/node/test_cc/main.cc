#include <string>
#include <istream>
#include <sstream>
#include <fstream>
#include <readline/readline.h>


#include "../commandline.hh"
#include "../interactive.hh"



#define SLOG_DEBUG_TRACE_FUNC
#include "../scope_logger.hh"
#include "../error.hh"






//extern char** AssemblerInteractive_command_completion(const char *text, int start, int end) ;

//void setup_readline_autocomplete(LangPrompt *lp);
//void asm_setup_readline_autocomplete();
//PromptSwitch p_run(LangPrompt *lp, const Commandline& cml) ;
//PromptSwitch p_run_init(LangPrompt *lp, const Commandline& cml) ;


int main(int argc, char *argv[]) {



  trace_function.open("trace.log", std::ios::out);
  ScopeLogger::set_current_verbose_level(SLOG_FUNC_INFO+30);
 //ScopeLogger::set_current_verbose_level(SLOG_TO_STR+31);
  MYLOGGER(trace_function, "int main(int, char*[])", __func__, SLOG_FUNC_INFO);

  Error::init();

  Interactive lang_iteractive(".loosh_history", "loosh> ");
  Commandline cml(argc, argv);
  lang_iteractive.interact(cml);
  //cout << "\n"; lang_it.print(); cout << "\n";



}
