#include "../svlm_ast.hh"


int main() {
  auto a = make_unique<AstBinOp>(make_unique<Operand>(123l), make_unique<Operand>(456l), AstOpCode::plus); 
}