#include <iostream>
#include <stdio.h>
#include "my_helpers.hh"
#include "assembler.hh"
#include <any>

Assembler::Assembler(std::shared_ptr<Tree> tp) {
  //context = new Tree();
  context = tp;
  current_context = {
    CONTEXT_UNIV, 
    "assembler", 
    "symbols",
    "", // mod
    "", // mvar
    "", // mfun
    "", // fbody only for  module svlm
    "", // larg
    "", // lvar
    "", // label
  };
};

Opcode Assembler::lookup_opcode(const std::string& opname) {
  auto it = opcode_table.find(opname);
  if(it != opcode_table.end()) {
    return it->second;
  } else {
    return Opcode::INVALID;
  }
}

void Assembler::run(VM& vm) {
  if(vm.data_seg!=nullptr) // reset data segment
    vm.data_seg->resize(0);
  Assembly::run(vm);
}

void Assembler::run_call(VM& vm, const std::string &m, const std::string &f) {
  full_symbol_t fst;
  if(m[0]!= ':') {// use fst's full app:api name :app.api.module.fun
    fst=current_context; 
    fst.smodule = m; fst.mfunction = f;
  }

  s_int_t old_pc =  pc_load;
  s_int_t fun_pc = get_sym_addr(key_tok_t::mfunction, fst);
  if(fun_pc < 0) {std::cerr << "Can't find function:'" << m+":"+ f << "'\n"; return;}
  set_instruction({Opcode(Opcode::CALL), fun_pc, 0, 0});  
  insert_instruction();
  set_instruction({Opcode(Opcode::EXIT), 0, 0, 0});  
  insert_instruction();
  Assembly::run_call(vm, old_pc);
  pc_load = old_pc;
}
void Assembler::set_dataseg_adr_value(s_int_t madr, reg_t v) {
  //std::cout << "madr: " << madr << " v:" << v.i << "\n";
  set_instruction({Opcode(Opcode::SET_D_AV), madr, v, 0});  
  insert_instruction();
}

void Assembler::run_single_instruction(VM &vm) {
  Assembly::run_single_instruction(vm);
}

void Assembler::set_breakpoint(us_int_t bpt) {
  Assembly::set_breakpoint(bpt);
}

void Assembler::run_break(VM &vm) {
  Assembly::run_break(vm);
}
void Assembler::run_step(VM &vm, s_int_t num) {
  Assembly::run_step(vm, num);
}
void Assembler::set_instruction(const instr_t &t) {
  Assembly::instruction = t;
}

void Assembler::insert_instruction() {
  Assembly::insert_instruction(line_total_read);

  // reset instruction, if vm:disatch being 
  // called from somewhere won't segmentfalt
  Assembly::instruction = {Opcode::INVALID, 0, 0,0}; 
}
void Assembler::print_program() {
  char istr[7];
  for(int i=0; i<pc_load; i++) {
    snprintf(istr, 7, "%06d", i);
    std::cout 
      << "code[" << istr << "]: " 
      << "lineno: " << line_no[i] << " "
      <<  Instruction::opcode_string_map[code[i].opcode] << " "  
      << "operands: "  
      <<  code[i].operands[0].i << ","  
      <<  code[i].operands[1].i << ","  
      <<  code[i].operands[2].i << "\n";
  }
}
void Assembler::print_program_f() {
  char istr[7];
  for(int i=0; i<pc_load; i++) {
    snprintf(istr, 7, "%06d", i);
    std::cout 
      << "code[" << istr << "]: " 
      // <<  int(code[i].opcode) << " "  
      <<  Instruction::opcode_string_map[code[i].opcode] << " "  
      << "operands: "  
      <<  code[i].operands[0].f << ","  
      <<  code[i].operands[1].f << ","  
      <<  code[i].operands[2].f << "\n";
  }
}
void Assembler::print_ds_i() {
  int i=0;
  for (std::vector<reg_t>::iterator it = data_seg.begin() ; it != data_seg.end(); ++it) {
    std::cout << i++ << ": " << (*it).i << "\n";
  }
  std::cout << '\n';
}
void Assembler::print_ds_f() {
  int i=0;
  for (std::vector<reg_t>::iterator it = data_seg.begin() ; it != data_seg.end(); ++it) {
    std::cout << i++ << ": " << (*it).f << "\n";
  }
  std::cout << '\n';
}

s_int_t Assembler::add_app_name(const std::string &app) {
  std::cout << "in add app to context: "  << app << "\n";
  current_context.app = app;
  context->add_node({
    current_context.uni, 
    current_context.app,
    "addr"}, pc_load);
  return pc_load;
}

s_int_t Assembler::add_api_name(const std::string &api) {
  // std::cout << "in add api to context: "  << api << "\n";
  current_context.api = api;
  context->add_node({
    current_context.uni, 
    current_context.app,
    current_context.api, 
    "addr"}, pc_load);
  return pc_load;
}

s_int_t Assembler::add_module_name(const std::string &m) {
  // std::cout << "in add module to context: '"  << m << "'\n";
  current_context.smodule = m; // update current context where are we
  full_symbol_t fst = current_context; fst.smodule = m;
  std::vector<std::string> keys = move(get_sym_key(key_tok_t::smodule, fst));
  keys.push_back("addr");
  context->add_node(keys, pc_load);
  return pc_load;
}

s_int_t Assembler::add_function_name(const std::string &f) {
  //std::cout << "in add function to context: "  << f << "\n";
  current_context.mfunction = f; 
  lvc = 0; // reset local var count to zero addr for every function
  lac = -1; // reset local arg count to zero addr for every function
  full_symbol_t fst = current_context; fst.mfunction = f;
  std::vector<std::string> keys = move(get_sym_key(key_tok_t::mfunction, fst));
  keys.push_back("addr");
  context->add_node(keys, pc_load); // name lookup addr
  addr2sym_map[pc_load] = fst;      // addr lookup name
  return pc_load;
}

s_int_t Assembler::add_label_name(const std::string &l) {
  current_context.label = l; 
  full_symbol_t fst = current_context; fst.label = l;
  std::vector<std::string> keys = move(get_sym_key(key_tok_t::label, fst));
  keys.push_back("addr");
  context->add_node(keys, pc_load);
  return pc_load;
}

s_int_t Assembler::add_lvar_name(const std::string &v, int n) { //  int n, with offset for array
  s_int_t adr = lvc;
  current_context.lvar = v;
  full_symbol_t fst = current_context; fst.lvar= v;
  std::vector<std::string> keys = move(get_sym_key(key_tok_t::lvar, fst));
  keys.push_back("addr");
  context->add_node(keys, lvc);
  lvc += n;
  return adr;       // return address of the local variable
}
s_int_t Assembler::add_mvar_name(const std::string &mv, int offset) { // int n, with offset for array
  s_int_t adr = mvc;
  current_context.mvar = mv;
  full_symbol_t fst = current_context; fst.mvar= mv;
  std::vector<std::string> keys = move(get_sym_key(key_tok_t::mvar, fst));
  keys.push_back("addr");
  context->add_node(keys, mvc);
  keys.pop_back();
  keys.push_back("size");
  context->add_node(keys, offset);
  mvc += offset;
  return adr;
}

s_int_t Assembler::add_larg_name(const std::string &a) {
  s_int_t adr = lac;
  current_context.larg = a;
  full_symbol_t fst = current_context; fst.larg= a;
  std::vector<std::string> keys = move(get_sym_key(key_tok_t::larg, fst));
  keys.push_back("addr");
  context->add_node(keys, lac--);
  return adr;
}

void Assembler::add_unresolved_sym(const key_tok_t ktt,   const full_symbol_t &fst, int oploc) {
  unresolved_symbol_t  notfound;
  if(fst.smodule[0]!= ':') notfound.name = current_context; // uri, use fst's full app:api name
  // if smodule=':' or mvar=':' uri resolve fst with ktt

  notfound.type = ktt;
  notfound.location = pc_load;
  notfound.operand_loc = oploc;
  switch(ktt) {
    case key_tok_t::app: 
      notfound.name.app = fst.app;
      break;
    case key_tok_t::api: 
      notfound.name.api = fst.api;
      break;
    case key_tok_t::smodule:
      notfound.name.smodule = fst.smodule;
      break;
    case key_tok_t::mvar:
      notfound.name.smodule = fst.smodule;
      notfound.name.mvar = fst.mvar;
      break;
    case key_tok_t::mfunction:
      // std::cout << "mfunction unresolved sym!" << fst.smodule + fst.mfunction << " at " << pc_load << "\n";
      notfound.name.smodule = fst.smodule;
      notfound.name.mfunction = fst.mfunction;
      break;
    case key_tok_t::lvar:
      notfound.name.smodule = fst.smodule;
      notfound.name.mfunction = fst.mfunction;
      notfound.name.lvar = fst.lvar;
      break;
    case  key_tok_t::label:
      notfound.name.smodule = fst.smodule;
      notfound.name.mfunction = fst.mfunction;
      notfound.name.label = fst.label;
      break;
    default:
      break;
  }
  unresolved_syms.push_back(notfound);
  // std::cerr << "adding to not found symbols location: " << pc_load << " " << fst.smodule << ":" << fst.mfunction << "' to unresolved vector\n";

}

void Assembler::super_opfun_set_instruction(Opcode op, const full_symbol_t &fst) {
  s_int_t adr = -1;
  full_symbol_t lfst; 
  if(fst.smodule[0]!= ':') {// use fst's full app:api name :app.api.module.fun
    lfst = current_context;
    lfst.smodule = fst.smodule;
    lfst.mfunction  = fst.mfunction;
  }
  std::vector<std::string> keys = move(get_sym_key(key_tok_t::mfunction, lfst));
  keys.push_back("addr");
  std::shared_ptr<TreeNode> sym_node = context->get_node(keys);
  if(sym_node == nullptr) {
    if(warning_print) std::cerr << "function '" << fst.mfunction << "' not found\n";
    add_unresolved_sym(key_tok_t::mfunction, lfst);
  } else {
    adr = std::any_cast<s_int_t>(sym_node->get_data());
  }
  instr_t asm_instr = {op, adr,0,0};
  set_instruction(asm_instr); 
}
void Assembler::super_op_branch(const std::string &labelstr) {
  

}


// resolve all names aka unresolved symbols at end of
// file loading or parsing
void Assembler::resolve_names() {
  std::vector<std::string> keys;
  for(auto us  : unresolved_syms) {
    // if the location of the unresolved name 
    if(us.operand_loc > -1) { // is specified in operand_loc which is > -1
      code[us.location].operands[us.operand_loc ].adr
         = get_sym_addr(us.type, us.name);
      continue;
    }
    switch(us.type) {
    case key_tok_t::mvar:  
      code[us.location].operands[2].adr
        = get_sym_addr(key_tok_t::mvar, us.name);
      break;
    case key_tok_t::mfunction:  
      code[us.location].operands[0].adr
        = get_sym_addr(key_tok_t::mfunction, us.name);
      break;
    case key_tok_t::label:  
      code[us.location].operands[0].adr
        = get_sym_addr(key_tok_t::label, us.name);
      break;
    default: 
      std::cerr << "symbol not found: " << us.name.smodule << "\n";
      break;
    }
  }
}
full_symbol_t Assembler::lookup_current_function(VM& vm) {
  Frame calling_frame = vm.get_calling_frame();
  int func = calling_frame.func; // current function address
  full_symbol_t fst =  addr2sym_map[func];
  return fst;
}

std::vector<std::string> Assembler::get_sym_key(const key_tok_t ktt,  const full_symbol_t &fst) {
  std::vector<std::string> key;
  switch(ktt) {
    case  key_tok_t::smodule:
      key ={ fst.uni, fst.app, fst.api, "modules", fst.smodule};
      break;
    case  key_tok_t::mfunction:
      key ={ fst.uni, fst.app, fst.api, "modules", fst.smodule,  "functions", fst.mfunction};
      break;
    case  key_tok_t::mvar_total_count:
      key ={ fst.uni, fst.app, fst.api, "modules", "mvar_total_count"};
      break;
    case  key_tok_t::mvar:
      key ={ fst.uni, fst.app, fst.api, "modules", fst.smodule,  "mvars", fst.mvar};
      break;
    case  key_tok_t::lvar:
      //std::cout << "in getsymkey: "<<  fst.uni+ fst.app+ fst.api+ "modules"+ fst.smodule+  "functions"+ fst.mfunction+ "lvars"+ fst.lvar << "\n";
      key ={ fst.uni, fst.app, fst.api, "modules", fst.smodule,  "functions", fst.mfunction, "lvars", fst.lvar};
      break;
    case  key_tok_t::larg:
      // key ={ fst.uni, fst.app, fst.api, "modules", fst.smodule,  "functions", fst.mfunction, "largs", fst.larg};
      key ={ fst.uni, fst.app, fst.api, "modules", fst.smodule,  "functions", fst.mfunction, "lvars", fst.larg};
      break;
    case  key_tok_t::label:
      key ={ fst.uni, fst.app, fst.api, "modules", fst.smodule,  "functions", fst.mfunction, "labels", fst.label};
      break;
    default: 
      std::cerr << "get_sym_key(): key not found!\n";
     return {}; 
  }
  return key; 
}

s_int_t Assembler::get_sym_addr(const key_tok_t ktt,  const full_symbol_t &fst) {

  std::string error_str;
  auto key=move(get_sym_key(ktt, fst));
  key.push_back("addr"); 
  std::shared_ptr<TreeNode> sym_node = context->get_node({key});

  if(sym_node != nullptr) {
    return std::any_cast<s_int_t>(sym_node->get_data());
  } 
  switch(ktt) {
    case  key_tok_t::smodule:
      error_str = fst.smodule;
      break;
    case  key_tok_t::mvar:
      error_str = fst.smodule + ":" + fst.mvar;
      break;
    case  key_tok_t::mfunction:
      error_str = fst.smodule + ":" + fst.mfunction;
      break;
    case  key_tok_t::lvar:
      error_str = fst.smodule + ":" + fst.mfunction + "." + fst.lvar;
      break;
    case  key_tok_t::larg:
      error_str = fst.smodule + ":" + fst.mfunction + "." + fst.larg;
      break;
    case  key_tok_t::label:
      error_str = fst.smodule + ":" + fst.mfunction + "." + fst.label;
      break;
    default:
      error_str = "not sure";
      break;
  }
  std::cerr << "can't resolve symbol:'" << error_str << "' got nullptr!\n";
  return -1;
}


full_symbol_t Assembler::dotstr2modvar(const std::string& vs) {
  return dotstr2fst(key_tok_t::mvar, vs);
}
full_symbol_t Assembler::dotstr2modfun(const std::string& vs) {
  return dotstr2fst(key_tok_t::mfunction, vs);
}
full_symbol_t Assembler::dotstr2mod(const std::string& vs) { //  up2 mod, include or exclude mod
  return dotstr2fst(key_tok_t::smodule, vs);
}

// arg vector size: app:1 api:2, up to  smodule:3  
// mfunction:4, mvar:4,  larg:5, lvar:5, label:5
full_symbol_t Assembler::dotstr2fst(key_tok_t ktt, const std::string& vs) {
  full_symbol_t fst = {};
  std::vector<std::string> keys  = split_string(vs, ".");
  if(keys.size()<=0) { 
    fst.app = fst.api = fst.smodule = fst.mfunction =
    fst.mvar = fst.lvar = fst.larg = fst.label = "";
    std::cerr << "str2fst error string: " 
      << vs << "\n"; 
    return fst;
  }
  switch(keys.size()) {
  case 5:
    if(ktt == key_tok_t::larg) 
      fst.larg = keys[4];
    else if(ktt == key_tok_t::lvar) 
      fst.lvar = keys[4];
    else if(ktt == key_tok_t::label) 
      fst.label = keys[4];
    else 
      fst.larg = fst.lvar = fst.label = "";
  case 4:
    if(ktt == key_tok_t::mfunction) 
      fst.mfunction = keys[3];
    else if(ktt == key_tok_t::mvar) 
      fst.mvar = keys[3];
    else  
      fst.mfunction = fst.mvar = "";
  case 3:
    fst.smodule = keys[2];
  case 2:
    fst.api = keys[1];
  case 1:
    fst.app = keys[0];
    break;
  default:
    std::cerr << "str2fst error string: " << vs << "\n";
  }
  return fst;
}