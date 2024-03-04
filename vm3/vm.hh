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

enum Reg {
  r0 = 0,
  r1, r2, r3, r4, 
  r5, r6, r7, r8,
  pc = 9, fp, sp, vp
};


typedef struct {
  Opcode opcode;
  reg_t operands[3];
} instr_t;

class Frame {
public:
  s_int_t pc=0; // current insturction pointer
  s_int_t sp=0; // current stack pointer, current size is current index
  s_int_t vp=0; // variable pointer stack[fp+vp]
  s_int_t fp=0; 
  Frame(const s_int_t pc, const s_int_t fp, const s_int_t sp) : pc(pc), fp(fp), sp(sp) {}
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

// s_int_t fp = 0;
s_int_t pc = 0;
s_int_t sp = 0;
s_int_t exit_max_pc=999999999999;

public:
  VM();
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

  // entire stack
  inline void load();
  inline void store();

  //local vars
  //inline void load_l();
  //inline void store_l();

  inline void mov();

  inline void call();
  inline void ret();
  inline void ret_n();
  inline void ret_np();
  inline void vmexit();
};
