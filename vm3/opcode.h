#ifndef OPCODES_H
#define OPCODES_H

#include <unordered_map>
#include <string>

enum class Opcode {
  INVALID = -1,
  ADD=100,
  SUB,
  MUL,
  DIV,
};

extern std::unordered_map<std::string, Opcode> opcode_table ;


#endif
