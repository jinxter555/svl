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

typedef struct frts {
  bool N ;
  bool Z ;
  bool C ;
  bool V ;
} flag_rt;

typedef union {
  s_int_t i;
  s_float_t f;
  s_int_t adr;
  char c[sizeof(s_float_t)];
  flag_rt flag;

} reg_t;

enum Reg {
  r0 = 0,
  r1, r2, r3, r4, 
  r5, r6, r7, r8,
  pc = 9, fp, sp, flag
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
  s_int_t func=0;  // function addr being called , for debug reverse lookup
  Frame(const s_int_t pc, const s_int_t fp, const s_int_t sp, const s_int_t func) 
    : pc(pc), fp(fp), sp(sp), func(func) {}
};  

class VM {
  friend class Assembly;
  friend class Assembler;
  friend class AssemblerInteractive; // for now to printout stack and frames

private:
  //Assembly *assembly = nullptr;
  instr_t *instruction=nullptr; // pointer for instruction arthimatic 
  reg_t R[MAXREG];
  std::stack<Frame> vmframes;
  std::vector<reg_t> vmstack;
  std::vector<reg_t> *data_seg;

  // flag_rt flag;
  // reg_t flag;


// s_int_t fp = 0;
s_int_t pc = 0;
// s_int_t sp = 0;
s_int_t exit_max_pc=999999999999;

public:
  VM();
  void set_data_seg(std::vector<reg_t>*);
  void dispatch(instr_t &itt);
  inline void dispatch();

  const Frame get_current_frame();
  const Frame& get_calling_frame();

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

  // global vars data segment
  inline void load_g();
  inline void store_g();
  inline void data_add();

  //local vars
  inline void load_l();
  inline void store_l();
  inline void iprint();
  inline void fprint();
  inline void cprint();

  // stack and data segment
  inline void set_d_av();
  inline void set_s_av();
  inline void stack_resize();
  inline void data_resize();
  inline void data_size();

  //
  inline void mov();

  // comparing
  inline void cmpi();
  inline void cmpf();

  // branching
  inline void beq();
  inline void bgt();
  inline void blt();
  inline void ble();
  inline void bge();


  inline void call();
  inline void call_r();
  inline void ret();
  inline void ret_nm();
  inline void ret_np();
  inline void vmexit();

};
