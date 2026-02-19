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

#include "../io_file.hh"


// init some static vars 
void init() {
  File::init();
  Error::init();

}



int main(int argc, char *argv[]) {



  trace_function.open("trace.log", std::ios::out);
  ScopeLogger::set_current_verbose_level(SLOG_FUNC_INFO+30);
 //ScopeLogger::set_current_verbose_level(SLOG_TO_STR+31);
  MYLOGGER(trace_function, "int main(int, char*[])", __func__, SLOG_FUNC_INFO);

  init();

  Interactive lang_iteractive(".loosh_history", "loosh> ");
  Commandline cml(argc, argv);
  lang_iteractive.interact(cml);
  lang_iteractive.pop_last_exit_history();
  lang_iteractive.save_history();
  //cout << "\n"; lang_it.print(); cout << "\n";



}
