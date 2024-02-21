#pragma once
#include <variant>
#include <stack>
#include <vector>
#include <iostream>
#include "opcode.hh"

#define MAXREG 256
#define MAX_STACK_SIZE 100000

typedef unsigned long int us_int_t;
typedef long int s_int_t;
typedef long double s_float_t;

typedef union {
  s_int_t i;
  s_float_t f;
  s_int_t adr;
} reg_t;

typedef struct {
  Opcode opcode;
  reg_t operands[3];
} instr_t;

class Frame {
public:
  us_int_t pc=0; // current insturction pointer
  us_int_t sp=0; // current stack pointer, current size is current index
  us_int_t vp=0; // variable pointer stack[fp+vp]
  us_int_t fp=0; 
  Frame(int pc, int fp) : pc(pc), fp(fp) {}
};  

class VM {
  friend class Assembly;
  //friend class Assembler;
  friend class AssemblerInteractive; // for now to printout stack and frames

private:
  //Assembly *assembly = nullptr;
  instr_t *instruction=nullptr; // pointer for instruction arthimatic 
  reg_t R[MAXREG];
  std::stack<Frame> vmframes;
  std::vector<reg_t> vmstack;

  us_int_t pc = 0;
  us_int_t fp = 0;
  us_int_t exit_max_pc=999999;

public:
  VM(){}
  void dispatch(instr_t &itt);
  inline void dispatch();

  inline void iadd_r();      // reg
  inline void iadd_c();      // constant
  inline void fadd_r();      // reg
  inline void fadd_c();      // constant
 //
  inline void isub_r();     
  inline void isub_c();     
  inline void fsub_r();     
  inline void fsub_c();     

  inline void imul_c();    
  inline void idiv_c();

  inline void push_c();
  inline void push_r();
  inline void pop_r();

  inline void call();
  inline void ret();
  inline void vmexit();
};
