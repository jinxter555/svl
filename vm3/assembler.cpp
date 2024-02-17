#include "assembler.h"

Opcode Assembler::lookup_opcode(const std::string& opname) {
  auto it = opcode_table.find(opname);
  if(it != opcode_table.end()) {
    return it->second;
  } else {
    return Opcode::INVALID;
  }
}
