#include <iostream>
#include "../node.hh"
#include "../interactive.hh"

#define SLOG_DEBUG_TRACE_FUNC
#include "../scope_logger.hh"

using namespace  std;
  

int main() {
  trace_function.open("test.log", ios::out);
  ScopeLogger::set_current_verbose_level(SLOG_FUNC_INFO + 3100);
  MYLOGGER(trace_function, "test_interactive_1 main()", __func__, SLOG_FUNC_INFO);

  Interactive ball("ball_history", "ball>");

  string hf = "hello.lisp";
  auto f = ball.load(hf);
  if(!f.first) {
    cerr << "can't open file: " << hf << "\n";
  }
  cout << "file\n";
  Node::print_value_recursive(*f.second);


}