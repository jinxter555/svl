#include "opcode.h"
std::unordered_map<std::string, Opcode> opcode_table = {
  {"add", Opcode::ADD},
  {"sub", Opcode::SUB},
  {"mul", Opcode::MUL},
  {"div", Opcode::DIV},
};


