#include <cassert>
#include <catch2/catch_all.hpp>

#include "operand.hh"
#include "ast_node.hh"
#include "ast_map.hh"
#include "ast_list.hh"
#include <memory>

#define SLOG_DEBUG_TRACE_FUNC
#include "scope_logger.hh"


#define CONTEXT_UNIV "universe"

TEST_CASE("check operand map 3 with tree like structure ") {
  trace_function.open("trace_svlm.log", std::ios::out);
  ScopeLogger::set_current_verbose_level(SLOG_FUNC_INFO + 20);

  MYLOGGER(trace_function, "TEST_CASE()", __func__, SLOG_FUNC_INFO);

  AstMap root;
  vector<string> keys0 = {CONTEXT_UNIV, "bigbang"};
  vector<string> keys1 = {CONTEXT_UNIV, "processes"};

  auto process  = make_unique<AstMap>();
  auto univ_ptr = root[CONTEXT_UNIV]._vrptr();
  (*process)["pid"] = 0l;
  //(*process)["frames"] = unique_ptr<AstNode >(make_unique<AstList>());
  //(*process)[CONTEXT_UNIV] = univ_ptr;
  auto processes = make_unique<AstList>();

  processes->add(move(process)); // add 


  root.add(keys1,  move(processes), true) ;
  root.add(keys0,  make_unique<AstList>(), true) ;
  root.add(keys0,  move(process), true) ;
  cout << "root: " << root << "\n";

  
}
