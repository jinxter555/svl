#include "../node.hh"
#include <iostream>

using namespace  std;
  
#define SLOG_DEBUG_TRACE_FUNC
#include "../scope_logger.hh"


int main() {

  trace_function.open("test.log", ios::out);
  ScopeLogger::set_current_verbose_level(SLOG_FUNC_INFO + 3100);
  MYLOGGER(trace_function, "test_node_1 main()", __func__, SLOG_FUNC_INFO);

  Node tm2(Node::Type::Map);
  cout << "\ntm2: " <<  tm2 << "\n";
  vector<string> p = {"hello", "world"};
  vector<string> p2 = {"hello", "world", "mundo"};
  vector<string> p3 = {"hello", "world", "hola", "mundo"};
  tm2.extend(p, true);
  cout << "tm2: " <<  tm2 << "\n";
  tm2.set(p2, Node::create(123), true);
  cout << "tm2: " <<  tm2 << "\n";
  tm2.set(p2, Node::create(456));
  cout << "tm2: " <<  tm2 << "\n";

}