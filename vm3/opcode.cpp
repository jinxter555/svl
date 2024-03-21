#include "opcode.hh"
#include <iostream>

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
  {"load_g", Opcode::LOAD_G},
  {"store_g", Opcode::STORE_G},
  {"load_l", Opcode::LOAD_L},
  {"store_l", Opcode::STORE_L},
  {"iprint", Opcode::IPRINT},
  {"fprint", Opcode::FPRINT},
  {"cprint", Opcode::CPRINT},
  {"set_d_av", Opcode::SET_D_AV},
  {"set_s_av", Opcode::SET_S_AV},
  {"stack_resize", Opcode::STACK_RESIZE},
  {"data_resize", Opcode::DATA_RESIZE},
  {"data_size", Opcode::DATA_SIZE},
  {"data_add", Opcode::DATA_ADD},
  {"mov", Opcode::MOV},

  {"beq", Opcode::BEQ},
  {"bgt", Opcode::BGT},
  {"blt", Opcode::BLT},
  {"ble", Opcode::BLE},
  {"bge", Opcode::BGE},
  
  {"cmpi", Opcode::CMPI},
  {"cmpf", Opcode::CMPF},


  {"call", Opcode::CALL},
  {"call_r", Opcode::CALL_R},
  {"exit", Opcode::EXIT},
  {"ret", Opcode::RET},
  {"ret_nm", Opcode::RET_NM},
  {"ret_np", Opcode::RET_NP},
};

std::unordered_map<Opcode, std::string> Instruction::opcode_string_map;

void Instruction::setup() {
  for (const auto& [key, value] : opcode_table) 
    Instruction::opcode_string_map[value] = key;
}