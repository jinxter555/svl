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

