#include <map>
#include <string>
#include <unordered_map>
#include <any>
#include <vector>
#include "expr.hh"
#include "token.hh"
#include "readinputline.hh"

#pragma once

using namespace std;

class Frame {
public:
    int pc=0; // Current instruction pointer
    int sp=0; // Current stack pointer, current size is the current index
    int vp=0; // variable pointer stack[fp+vp]
    int fp=0;
    // Current heap size
    int heap_size=0;
    // Garbage collection status
    bool gc_enabled=false;

    // Current stack frame
    //StackFrame* current_frame;
    // Local variables
    std::unordered_map<std::string, int> locals;    // int is from fp + int

    Frame(int pc, int fp) : pc(pc), fp(fp) {}
};

class VMsvl {
private:
  vector<Token> code; // postfix expressions
  stack<Token> stack; // tokens stack
  vector<Frame> frames;
  Frame context;
  int pc = 0;         // program counter
  int fp = 0;         // frame counter

public:
  void run();
  void add_expr(Expr& expr);

  void push(Token v); 
  void call(int address);
  void decl(const string& name);    // declare local variable
  Token pop();


};

int main() {
  ReadInputLine ril;
  VMsvl vm;
  ril.tokenize("1 + 2");
  Expr e(ril);
  vm.add_expr(e);
}
