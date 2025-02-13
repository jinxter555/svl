#include <cassert>
#include "operand.hh"
//#include "svlm_ast.hh"
#include "ast.hh"

#include <catch2/catch_all.hpp>

#define SLOG_DEBUG_TRACE_FUNC
#include "scope_logger.hh"


TEST_CASE("check operand list 2") {
  trace_function.open("trace_svlm.log", std::ios::out);
  ScopeLogger::set_current_verbose_level(SLOG_FUNC_INFO + 1);


  auto t2 = make_unique<AstTuple>();
  //astnode_u_ptr t3 = make_unique<AstTuple>();


}
