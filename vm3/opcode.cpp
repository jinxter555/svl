#include "opcode.hh"
std::unordered_map<std::string, Opcode> opcode_table = {
  {"iadd_r", Opcode::IADD_R},
  {"iadd_c", Opcode::IADD_C},
  {"isub_r", Opcode::ISUB_R},
  {"isub_c", Opcode::ISUB_C},
  {"mul", Opcode::MUL},
  {"div", Opcode::DIV},
  {"push_c", Opcode::PUSH_C},
  {"push_r", Opcode::PUSH_R},
  {"pop_r", Opcode::POP_R},
  {"mov", Opcode::MOV},
  {"call", Opcode::CALL},
  {"exit", Opcode::EXIT},
  {"ret", Opcode::RET},
};


