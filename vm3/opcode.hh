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
  RET_N,
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
  LOAD,
  STORE,
  LOAD_L,
  STORE_L,
};

extern std::unordered_map<std::string, Opcode> opcode_table ;


#endif
