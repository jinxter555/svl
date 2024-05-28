#include "ast.cpp"
int main() {
  std::shared_ptr<ListExprAst> program = std::make_shared<ListExprAst>();
  //NumberExprAst a(3);

  std::shared_ptr<ExprAst> n1 = std::make_shared<NumberExprAst>(3);
  std::shared_ptr<ExprAst> n2 = std::make_shared<NumberExprAst>(5);
  std::shared_ptr<ExprAst> f1 = std::make_shared<NumberExprAst>(3.145f);

  program->add(f1);
  program->print();

  //std::cout <<  std::any_cast<int>(n1->evaluate()) << "\n";
  //std::cout <<  std::any_cast<float>(f1->evaluate()) << "\n";

  op_t op1 = {BinOpcodeAST::INT_OP_INT, '-'};
  op_t op4 = {BinOpcodeAST::INT_OP_INT, '+'};

  op_t op2 = {BinOpcodeAST::FLT_OP_FLT, '*'};
  op_t op3 = {BinOpcodeAST::FLT_OP_INT, '/'};

  std::shared_ptr<ExprAst> b1 = std::make_shared<BinOpExprAst>(
    std::make_shared<NumberExprAst>(3),
    std::make_shared<NumberExprAst>(5), op1); 
  std::cout <<  std::any_cast<int>(b1->evaluate()) << "\n";

  std::shared_ptr<ExprAst> i1 = std::make_shared<BinOpExprAst>( 
    std::make_shared<NumberExprAst>(11), 
    std::make_shared<NumberExprAst>(22), op1); 
  std::cout <<  "i1: " << std::any_cast<int>(i1->evaluate()) << "\n";

  // std::shared_ptr<ExprAst> b2 = std::make_shared<BinOpExprAst>( std::make_shared<NumberExprAst>(3.145f), std::make_shared<NumberExprAst>(5.15f), op2); std::cout <<  std::any_cast<float>(b2->evaluate()) << "\n";

  std::shared_ptr<ExprAst> b3 = std::make_shared<BinOpExprAst>(
    std::make_shared<NumberExprAst>(3.145f),
    std::make_shared<NumberExprAst>(5.0f), 
    BinOpcodeAST::FLT_OP_FLT, '*');
  
  b3->print();
  std::cout <<  "b3: " << std::any_cast<float>(b3->evaluate()) << "\n\n";

  std::shared_ptr<ExprAst> b4 = std::make_shared<BinOpExprAst>(
    std::make_shared<NumberExprAst>(3.0f),
    std::make_shared<NumberExprAst>(75.5555f), 
    BinOpcodeAST::FLT_OP_FLT, '*');

  std::shared_ptr<ExprAst> b5 = std::make_shared<BinOpExprAst>(
      b3,
      b4,
    BinOpcodeAST::FLT_OP_FLT, '+');
  b5->print();
  std::cout <<  "b5: " << std::any_cast<float>(b5->evaluate()) << "\n\n";
  



  program->add(f1);
  program->add(b3);
  program->add(b4);
  program->print();



//  std::cout <<  std::any_cast<float>(b3->evaluate()) << "\n";
//  std::cout <<  std::any_cast<int>(b4->evaluate()) << "\n";

//  std::cout << "program print\n";
//  program->print();
}
