#include <iostream>
#include "../node.hh"
#include "../lisp_expr.hh"

#define SLOG_DEBUG_TRACE_FUNC
#include "../scope_logger.hh"

using namespace  std;
  

int main() {
  trace_function.open("test.log", ios::out);
  ScopeLogger::set_current_verbose_level(SLOG_FUNC_INFO + 3100);
  MYLOGGER(trace_function, "test_node_1 main()", __func__, SLOG_FUNC_INFO);

  LispExpr lisp;
  //string input="(add 1 2 3 (add 5 3))"; //string input;
  //string input="(add 1 2 3 (def :mod 5 3))"; //string input;
  //string input="(def :module 5 3)"; //string input;
  //string input="(def :module Main (def :fun main(+ 5 3)))"; //string input;
  //string input="(def :module Main (def :fun main(+ 5 3)))"; //string input;
  //lisp.print(); cout << "\n";
  //string input="(add 1 2 3)"; //string input;
  string input="(print (list 1 2 3))"; //string input;
  //string input="(def :module 2 3)"; //string input;
  //cout << "input: ";
  //cin >> input;
  //auto tokens = reader.tokenize("(plus 1 2)");
  auto result  = lisp.build_program(input);
  //cout << "result: " <<  *result.second << "\n";
  cout << "result:\n " ;
  //cout << *result.second << "\n";



}