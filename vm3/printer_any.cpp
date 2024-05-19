#include "vm_type.hh"
#include "lang.hh"
#include "ast.hh"
#include "number.hh"
#include <any>
#include <memory>


#define TM std::map<std::string, std::shared_ptr<TreeNode>>

std::ostream& operator << (std::ostream& out, std::any& a) {
  if(a.type()  == typeid(char))
    out << std::any_cast<char>(a);
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
  else if(a.type()  == typeid(Number)) {
    Number num= std::any_cast<Number>(a);
    num.printData(); }
  else if(a.type()  == typeid(std::shared_ptr<ExprAst>)) {
    std::cout  << "function code block\n";
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
