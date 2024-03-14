#ifndef OPCODES_H
#define OPCODES_H

#include <unordered_map>
#include <string>

enum class Opcode {
  INVALID = -1,
  EXIT=0,
  NOOP,
  
  CALL,
  RET,
  RET_NM,
  RET_NP,

  IADD_R=100,
  IADD_C,
  ISUB_R,
  ISUB_C,

  MUL,
  DIV,

  MOV,

  PUSH_C,
  PUSH_R,
  POP_R,

  LOAD_G,
  STORE_G,
  DATA_ADD,

  // branching
  BEQ,
  BGT,
  BLT,
  BLE,
  BGE,

  CMPI,
  CMPF,

  LOAD_L,
  STORE_L,
  IPRINT,
  FPRINT,
  STACK_RESIZE,
  DATA_RESIZE,
  DATA_SIZE,
};

class Instruction  {
public:
  static std::unordered_map<Opcode, std::string> opcode_string_map;
//----
  static void setup();
  
};

extern std::unordered_map<std::string, Opcode> opcode_table ;


#endif
