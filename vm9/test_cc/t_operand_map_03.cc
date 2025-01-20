#include <cassert>
#include <catch2/catch_all.hpp>

#include "operand.hh"
#include "ast_map.hh"

#define SLOG_DEBUG_TRACE_FUNC
#include "scope_logger.hh"


#define CONTEXT_UNIV "universe"

TEST_CASE("check operand map 3 with tree like structure ") {
  trace_function.open("trace_svlm.log", std::ios::out);
  ScopeLogger::set_current_verbose_level(SLOG_FUNC_INFO + 20);

  MYLOGGER(trace_function, "TEST_CASE()", __func__, SLOG_FUNC_INFO);

  AstMap root;
  vector<string> keys0 = {CONTEXT_UNIV, "bigbang"};
  vector<string> keys1 = {CONTEXT_UNIV,"hello", "one", "two"};
  vector<string> keys2 = {CONTEXT_UNIV,"hello", "one", "two", "three", "four", "Five"};
  vector<string> keys3 = {CONTEXT_UNIV,"hello", "one-one", "two", "three", "four", "Five"};

  root.add(keys0, 55555l, true);
  cout << "root: " << root << "\n\n";
  root.add(keys1,  123l, true) ;
  cout << "root: " << root << "\n\n";
  if(root.add(keys2,  456l, true)) cout << "add keys 2 successfull\n";
  cout << "root: " << root << "\n\n";
  if(root.add(keys3,  33333l, true)) cout << "add keys 2 successfull\n";
  cout << "root: " << root << "\n\n";

  
}
