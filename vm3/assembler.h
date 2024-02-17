#pragma once
#include "opcode.h"
class Assembler {
public:
  Opcode lookup_opcode(const std::string& opname);
};

