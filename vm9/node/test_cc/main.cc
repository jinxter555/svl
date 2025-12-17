#include <string>
#include <istream>
#include <sstream>
#include <fstream>
#include <readline/readline.h>


#include "../commandline.hh"
#include "../interactive.hh"



#define SLOG_DEBUG_TRACE_FUNC
#include "../scope_logger.hh"







//extern char** AssemblerInteractive_command_completion(const char *text, int start, int end) ;

//void setup_readline_autocomplete(LangPrompt *lp);
void asm_setup_readline_autocomplete();
void svlm_setup_readline_autocomplete();
PromptSwitch p_run(LangPrompt *lp, const Commandline& cml) ;
PromptSwitch p_run_init(LangPrompt *lp, const Commandline& cml) ;



int main(int argc, char *argv[]) {

  bool init_flag = true;

  //log_output.open("svlm.log", std::ios::out);
  trace_function.open("trace.log", std::ios::out);
  ScopeLogger::set_current_verbose_level(SLOG_FUNC_INFO+30);
  MYLOGGER(trace_function, "int main(int, char*[])", __func__, SLOG_FUNC_INFO);

  Interactive lang_it(".svlm_history", "svlm> ");
  Commandline cml(argc, argv);
  lang_it.interact(cml);
  cout << "\n\n";
  lang_it.print();
  cout << "\n";



}
