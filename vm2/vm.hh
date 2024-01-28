#pragma once
#include <iostream>
#include <fstream>
#include <stack>
#include <vector>
#include <variant>
#include <readline/readline.h>
#include <readline/history.h>
#include <unordered_map>


using namespace std;
#define MAXREG 256
#define MAX_STACK_SIZE 100000
typedef unsigned long int us_int_t;
typedef long int s_int_t;
typedef long double s_float_t;
typedef union {
    s_int_t i;
    s_float_t f;
    us_int_t adr;
} reg_t;


typedef unsigned char byte_code_t;
typedef byte_code_t regnum_t;

typedef struct {
  byte_code_t opcode;  // byte code opcode
  reg_t operands[3];
} instr_t;

enum {
  reg_r0 = 0,
  reg_r1, reg_r2, reg_r3, reg_r4,
  reg_r5, reg_r6, reg_r7, reg_r8,
  reg_pc =16,
  reg_fp,
};

typedef struct frts {
  bool N = false; 
  bool Z = false;
  bool C = false;
  bool V = false;
} flag_rt;

class Frame {
public:
  us_int_t pc=0; // current insturction pointer
  us_int_t sp=0; // current stack pointer, current size is current index
  us_int_t vp=0; // variable pointer stack[fp+vp]
  us_int_t fp=0; 
  unordered_map<string, reg_t> locals;
  Frame(int pc, int fp) : pc(pc), fp(fp) {}

};

class Assembly;
class VM {
  friend class Assembly;
  friend class Assembler;
  friend class AssemblerInteractive;
private:
  // std::stack<reg_t> vmstack; //reg_t stack[MAX_STACK_SIZE];
  std::vector<reg_t> vmstack; //reg_t stack[MAX_STACK_SIZE];
  std::stack<Frame> vmframes; // vector<Frame> frames;
  us_int_t pc = 0;
  us_int_t fp = 0;
  flag_rt flag;

  reg_t R[MAXREG];

  instr_t *instruction=nullptr; // pointer for instruction arthimatic 
  Assembly *assembly=nullptr;
public:

  VM();
  void set_assembly(Assembly *);
  void dispatch(instr_t &itt);
  inline void dispatch();

  inline void pushc();
  inline void pushr();

  inline void popr();

  inline void mov();
  inline void addi();               // addi r0,r1,ci, result = register + constant_int
  inline void subi();               // subi r0,r1,ci, result = register - constant_int
  inline void muli();               // addi r0,r1,ci, result = register + constant_int
  inline void divi();               // subi r0,r1,ci, result = register - constant_int

  inline void load();
  inline void store();

  inline void cmpr();
  inline void beq();

  inline void call();
  inline void ret();
  inline void vmexit();


  // void print_stack_int() ;
  // void print_registers_int() ;
   void print_instruction();
  // void print_registers(byte_code_t n=8);


  // void push(); void pop(); // not sure why

};