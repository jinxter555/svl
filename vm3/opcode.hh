#ifndef OPCODES_H
#define OPCODES_H

#include <unordered_map>
#include <string>

enum class Opcode {
  INVALID = -1,
  EXIT=0,
  CALL,
  RET,
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
};

extern std::unordered_map<std::string, Opcode> opcode_table ;


#endif