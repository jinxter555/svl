#include "../node.hh"
#include <iostream>

using namespace  std;
  
#define SLOG_DEBUG_TRACE_FUNC
#include "../scope_logger.hh"


int main() {

  trace_function.open("test.log", ios::out);
  ScopeLogger::set_current_verbose_level(SLOG_FUNC_INFO + 11);
  MYLOGGER(trace_function, "test_node_1 main()", __func__, SLOG_FUNC_INFO);

  Node a(10);
  Node b(20);
  
  Node c = a + b;
  Node d = c + Node(123.333);
  string v1 = c._to_str();
  string v2 = d._to_str();

  cout << "v1: " << v1  << "\n";
  cout << "v2: " << v2  << "\n";

  cout << "v1: " << v1  << "\n";

  Node e;
  e.set(d.clone());
  cout << "e: " << e._to_str() << "\n";

  Node t1(Node::Type::Map);
  t1.set("line", 123l);
  t1.set("col", 456l);
  t1.set("value", 555.666f);
  cout << "t1: " <<  t1 << "\n";
  cout << "t1.to_str: " <<  t1._to_str() << "\n";
  Node::print_value_recursive(t1, 0);

  Node::Map m1;
  m1["hello"]=Node::create(123l);
  Node t2(move(m1));
  cout << "\nt2: " <<  t2 << "\n";
  Node::print_value_recursive(t2, 0);

  cout << "\nList\n";
  Node list(Node::Type::List);
  list.add(Node::create(123l));
  list.add(Node::create("hello"));
  list.add(Node::create("world"));
  cout << "list: " << list._to_str() << "\n";



}