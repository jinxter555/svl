#include <map>
#include <string>
#include <unordered_map>
#include <any>
#include <vector>
#include "expr.hh"
#include "token.hh"
#include "readinputline.hh"

using namespace std;

struct InterpreterContext {
    // Current instruction pointer
    int ip;
    // Current stack pointer
    int sp;
    int fp;
    // Current heap size
    int heap_size;
    // Garbage collection status
    bool gc_enabled;

    // Current stack frame
    //StackFrame* current_frame;
    // Local variables
    std::unordered_map<std::string, any> locals;
};

class VMsvl {
private:
  vector<Token> code; // postfix expressions
  stack<Token> stack; // postfix expressions
public:
  void add_expr(Expr& expr) { // takes variable expr modify th
    auto ep = expr.ToPostfix();
    code.insert(code.end(), ep.begin(), ep.end());

  }


  void run();
  void push(Token v); 
  Token pop();


};

int main() {
  ReadInputLine ril;
  vm_svl vm;
  ril.tokenize("1 + 2");
  Expr e(ril);
  vm.add_expr(e);
}
