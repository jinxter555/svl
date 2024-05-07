#pragma once
#include "vm_type.hh"
#include "frame.hh"

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
  inline void set_lv_av();
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
