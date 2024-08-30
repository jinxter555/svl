#include "tree.hh"
#include <memory.h>

using namespace std;
class ExprAst : public TreeNode {
public:
  virtual ~ExprAst() {}
};

class NumberExprAst: public ExprAst {
};

class BinOpExprAst: public ExprAst {
  void abc() {
    shared_ptr<NumberExprAst> nbasePtr = 
    dynamic_pointer_cast<NumberExprAst>(TreeNode::get_child("right"));
  }
};

int main() {



}
