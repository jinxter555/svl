#pragma once
#include "vm_type.hh"
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
