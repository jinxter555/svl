#pragma once
#include "opcode.hh"
#include "assembly.hh"
#include "vm.hh"

class Assembler : public Assembly {
private:
public:
  Opcode lookup_opcode(const std::string& opname);
  void run(VM& vm);
};

