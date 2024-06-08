#include "vm_type.hh"
#include "lang.hh"
#include "ast.hh"
#include "number.hh"
#include "operand.hh"
#include <any>
#include <memory>



std::ostream& operator << (std::ostream& out, std::any& a) {
  if(a.type()  == typeid(char))
    out << std::any_cast<char>(a);
  if(a.type()  == typeid(bool)) {
    out << std::any_cast<bool>(a);
    return  out; }
  if(a.type()  == typeid(ast_op)) {
    std::string oc;
    ast_op op = std::any_cast<ast_op>(a);
    switch(op) {
    case ast_op::noop:  oc="-noop-"; break;
    case ast_op::ast_default:  oc="default"; break;
    case ast_op::assign:  oc="="; break;
    case ast_op::plus:  oc="+"; break;
    case ast_op::minus: oc="-"; break;
    case ast_op::mul:   oc="*"; break;
    case ast_op::div:   oc="/"; break;
    case ast_op::eql:   oc="=="; break;
    case ast_op::neql:  oc="!="; break;
    case ast_op::gt:    oc=">"; break;
    case ast_op::lt:    oc="<"; break;
    case ast_op::lteq:  oc="<="; break;
    case ast_op::gteq:  oc=">="; break;
    case ast_op::and_:  oc="&&"; break;
    case ast_op::or_:  oc="||"; break;
    case ast_op::not_:  oc="!"; break;
    default: oc="out wrong type"; break;
    } 
    out << oc ; }
  else if(a.type()  == typeid(int))
    out << std::any_cast<int>(a);
  else if(a.type()  == typeid(double))
    out << std::any_cast<double>(a);
  else if(a.type()  == typeid(float))
    out << std::any_cast<float>(a);
  else if(a.type()  == typeid(long int))
    out << std::any_cast<long int>(a);
  else if(a.type()  == typeid(unsigned long int))
    out << std::any_cast<unsigned long int>(a);
  else if(a.type()  == typeid(long long))
    out << std::any_cast<long long>(a);
  else if(a.type()  == typeid(long double))
    out << std::any_cast<long double>(a);
  else if(a.type()  == typeid(std::string))
    out << std::any_cast<std::string>(a);
  else if(a.type()  == typeid(char *))
    printf("%s\n", std::any_cast<char *>(a));
  else if(a.type()  == typeid(Number)) {
    Number num= std::any_cast<Number>(a);
    num.print(); }
  else if(a.type()  == typeid(Operand)) {
    Operand  opr= std::any_cast<Operand>(a);
     out << opr; }
  else if(a.type()  == typeid(Tuple)) {
    Tuple t= std::any_cast<Tuple>(a);
    t.print(); }
  else if(a.type()  == typeid(std::vector<std::any>)) {
    std::vector<std::any> any_vector = std::any_cast<std::vector<std::any>>(a);
    for (std::any element : any_vector) {
      out << element << " "; } }
  else if(a.type()  == typeid(std::shared_ptr<ExprAst>)) {
    std::cout  << "code block\n";
    std::shared_ptr ast = std::any_cast<std::shared_ptr<ExprAst>>(a);
    ast->print(); }
  else if(a.type()  == typeid(TM)) {
    TM lvars = std::any_cast<TM>(a);
    std::cout  << "Tree node\n";
    for (const auto& [key, _] :  lvars) {
      std::any  v = lvars[key]->get_data();
      std::cout << "k: " << key << ", v: " << v << "\n";
    }}
  else
    out << "unknown value type!";
  return out;
}
