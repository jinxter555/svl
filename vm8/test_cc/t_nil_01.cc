#include <cassert>
#include "../operand.hh"

  astexpr_u_ptr nil_ast_ptr=nullptr;
  const astexpr_u_ptr nil_ast_ptr_c=nullptr;

const astexpr_u_ptr& err1()  {
  return nil_ast_ptr;
}

class EC {
private:
  astexpr_u_ptr nil_ast_ptr2=nullptr;
public:
  astexpr_u_ptr& err1() { return nil_ast_ptr2;}
};

class FC {
private:
  astexpr_u_ptr nil_ast_ptr3=nullptr;
public:
  const astexpr_u_ptr& err1() { return nil_ast_ptr3;}
};

int main() {
  cout  << "nil_operand: " << nil_operand << "\n";
  cout  << "nil_ast_ptr: " << nil_ast_ptr << "\n";
  cout  << "const nil_ast_ptr_c: " << nil_ast_ptr_c << "\n";
  if(nil_ast_ptr == nil_ast_ptr_c) {
    cout  << "nil_ast_ptr == nil_ast_ptr_c\n";
  }
  if(nil_ast_ptr == err1()) {
    cout  << "nil_ast_ptr == err1()\n";
  }
  if(nil_ast_ptr == nullptr) {
    cout  << "nil_ast_ptr == nullptr \n";
  }
  if(nil_ast_ptr.get() == nullptr) {
    cout  << "nil_ast_ptr.get() == nullptr \n";
  }

  EC ec1;
  FC fc1;
  if(ec1.err1() == nil_ast_ptr) {
    cout  << "ec1.err1() == nil_ast_ptr\n";
  }
  if(ec1.err1() == nullptr) {
    cout  << "ec1.err1() == nullptr\n";
  }
  if(ec1.err1() == fc1.err1()) {
    cout  << "ec1.err1() == fc1.err1()\n";
  }
  auto &b = ec1.err1();
  cout << "b=ec1.err1(): " << ec1.err1() << "\n";
}
