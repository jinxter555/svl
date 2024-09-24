#include "lang.hh"
#include <any>



std::ostream& operator << (std::ostream& out, const std::any& a) {
  if(a.type()  == typeid(char))
    out << std::any_cast<char>(a);
  if(a.type()  == typeid(bool)) {
    out << std::any_cast<bool>(a);
    return  out; 
  } else if(a.type()  == typeid(int))
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
  else
    out << "unknown any value type!";
  return out;
}
