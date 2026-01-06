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




Error NodeError;


//extern char** AssemblerInteractive_command_completion(const char *text, int start, int end) ;

//void setup_readline_autocomplete(LangPrompt *lp);
void asm_setup_readline_autocomplete();
void svlm_setup_readline_autocomplete();
PromptSwitch p_run(LangPrompt *lp, const Commandline& cml) ;
PromptSwitch p_run_init(LangPrompt *lp, const Commandline& cml) ;


Node::OpStatusRef rv1() {
  //return {false, *Node::create_error(Error::Type::InvalidOperation, "Node::back() is empty:1 " )};
  //return {false, Error[Error::Type::InvalidOperation]};
  return {false, Error::ref(Error::Type::DivideByZero, "oh boy dividied by zero")};
  //return {false, Error::ref(Error::Type::InvalidOperation)};
  //return {false, Error[Error::Type::InvalidOperation]};
  //return {false, e};
}

int main(int argc, char *argv[]) {
  //Error a;


  /*
  Node::Vector v;
  Node n1(move(v));
  auto b = n1.back();
  auto &err = b.second;
  cout << "n1 : " << n1 << "\n";
  if(!b.first) {
    cout << "b: " << b.second << "\n";
  }
  */


  

  //log_output.open("svlm.log", std::ios::out);
  trace_function.open("trace.log", std::ios::out);
  //ScopeLogger::set_current_verbose_level(SLOG_FUNC_INFO+30);
  ScopeLogger::set_current_verbose_level(SLOG_TO_STR+31);
  MYLOGGER(trace_function, "int main(int, char*[])", __func__, SLOG_FUNC_INFO);

  Error::init();
  auto err1 = rv1();
  cout << "err1 : " << err1 << "\n";



  Interactive lang_it(".svlm_history", "svlm> ");
  Commandline cml(argc, argv);
  lang_it.interact(cml);
  //cout << "\n"; lang_it.print(); cout << "\n";
  //lang_it.interact(cml);



}
