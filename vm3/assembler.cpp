#include <iostream>
#include "assembler.hh"
#include <any>

Assembler::Assembler() {
  context = new Tree();
  current_context = {
    CONTEXT_UNIV, 
    "myprog", 
    "myapi",
    "", // mod
    "", // mfun
    "", // var
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
  Assembly::run(vm);
}

// call module:function from user command prompt 
void Assembler::run_call(VM& vm, const std::string &m, const std::string &f) {
  std::shared_ptr<TreeNode> sym_node = context->get_node({
    current_context.uni, 
    current_context.app,
    current_context.api, 
    "modules", m,
    "functions", f,
    "addr"});
  if(sym_node == nullptr) {
    std::cout << "can't find module: " << m << " function: " << f << "\n";
    return;
  }
  s_int_t old_pc =  pc_load;
  s_int_t fun_pc =  std::any_cast<s_int_t>(sym_node->get_data());
  if(fun_pc < 0) {std::cerr << "Can't find function:'" << m+":"+ f << "'\n"; return;}
  set_instruction({Opcode(Opcode::CALL), fun_pc, 0, 0});  
  insert_instruction();
  set_instruction({Opcode(Opcode::EXIT), 0, 0, 0});  
  insert_instruction();
  Assembly::run_call(vm, old_pc);
  pc_load = old_pc;
}

void Assembler::run_single_instruction(VM& vm) {
  Assembly::run_single_instruction(vm);
}

void Assembler::set_instruction(const instr_t &t) {
  Assembly::instruction = t;
}

void Assembler::insert_instruction() {
  Assembly::insert_instruction();
}
void Assembler::print_program() {
  for(int i=0; i<pc_load; i++) {
    std::cout 
      << "code[" <<i<< "]" 
      <<  int(code[i].opcode) << " "  
      << "operands: "  
      <<  code[i].operands[0].i << ","  
      <<  code[i].operands[1].i << ","  
      <<  code[i].operands[2].i << "\n";
  }
}
void Assembler::print_program_f() {
  for(int i=0; i<pc_load; i++) {
    std::cout 
      << "code[" <<i<< "]" 
      <<  int(code[i].opcode) << " "  
      << "operands: "  
      <<  code[i].operands[0].f << ","  
      <<  code[i].operands[1].f << ","  
      <<  code[i].operands[2].f << "\n";
  }
}
void Assembler::add_app_name(const std::string &app) {
  std::cout << "in add app to context: "  << app << "\n";
  current_context.app = app;
  context->add_node({
    current_context.uni, 
    current_context.app,
    "addr"}, pc_load);
}
void Assembler::add_api_name(const std::string &api) {
  std::cout << "in add api to context: "  << api << "\n";
  current_context.api = api;
  context->add_node({
    current_context.uni, 
    current_context.app,
    current_context.api, 
    "addr"}, pc_load);
}
/* void Assembler::add_module_name(const std::string &m) {
  std::cout << "in add module to context: "  << m << "\n";
  current_context.smodule = m;
  context->add_node({
    current_context.uni, 
    current_context.app,
    current_context.api, 
    "modules",
    current_context.smodule,
    "addr"}, pc_load);
}
*/

void Assembler::add_module_name(const std::string &m) {
  // std::cout << "in add module to context: '"  << m << "'\n";
  current_context.smodule = m; // update current context where are we
  full_symbol_t fst = current_context; fst.smodule = m;
  std::vector<std::string> keys = move(get_sym_key(key_tok_t::smodule, fst));
  keys.push_back("addr");
  context->add_node(keys, pc_load);
}


/*
void Assembler::add_function_name(const std::string &f) {
  std::cout << "in add function to context: "  << f << "\n";
  current_context.mfunction = f; 
  // current_var = ""; // clear out var so, %call fun1 won't return variable
  lvc = 0; // init lvc local variable counter, it should be similar to vp variable pointer
  context->add_node({
    current_context.uni, 
    current_context.app,
    current_context.api, 
    "modules",
    current_context.smodule,
    "functions",
    current_context.mfunction,
    "addr"}, pc_load);
}*/
void Assembler::add_function_name(const std::string &f) {
  std::cout << "in add function to context: "  << f << "\n";
  current_context.mfunction = f; 
  lvc = 0; // reset local var count to zero addr for every function
  full_symbol_t fst = current_context; fst.mfunction = f;
  std::vector<std::string> keys = move(get_sym_key(key_tok_t::mfunction, fst));
  keys.push_back("addr");
  context->add_node(keys, pc_load);
}

/*
void Assembler::add_label_name(const std::string &l) {
  context->add_node({
    current_context.uni, 
    current_context.app,
    current_context.api, 
    "modules",
    current_context.smodule,
    "functions",
    current_context.mfunction,
    "labels",
    l, "addr"}, pc_load);
}*/
void Assembler::add_label_name(const std::string &l) {
  current_context.label = l; 
  full_symbol_t fst = current_context; fst.label = l;
  std::vector<std::string> keys = move(get_sym_key(key_tok_t::label, fst));
  keys.push_back("addr");
  context->add_node(keys, pc_load);
}


/*
// the address location will be point to the stack realtive from fp,fp+vp
void Assembler::add_lvar_name(const std::string &v) {
  current_context.lvar = v;
  context->add_node({
  current_context.uni, 
  current_context.app,
  current_context.api, 
  "modules",
  current_context.smodule,
  "functions",
  current_context.mfuntion,
  "lvars",
  current_context.lvar, 
  "addr"}, lvc++);
}*/
void Assembler::add_lvar_name(const std::string &v) {
  current_context.lvar = v;
  full_symbol_t fst = current_context; fst.lvar= v;
  std::vector<std::string> keys = move(get_sym_key(key_tok_t::lvar, fst));
  keys.push_back("addr");
  context->add_node(keys, lvc++);
}


void Assembler::add_unresolved_function(const full_symbol_t &fst) {
  unresolved_symbol_t  notfound;
  notfound.name = current_context;
  notfound.name.smodule = fst.smodule;
  notfound.name.mfunction = fst.mfunction;
  notfound.type = key_tok_t::mfunction ;
  notfound.location.adr = pc_load;
  unresolved_syms.push_back(notfound);
  std::cerr << "adding to not found: '" << fst.smodule << ":" << fst.mfunction << "' to unresolved vector\n";
}
void Assembler::add_unresolved_sym(const key_tok_t ktt,   const full_symbol_t &fst) {
  unresolved_symbol_t  notfound;
  notfound.name = current_context;
  notfound.type = ktt;
  notfound.location.adr = pc_load;
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
  std::cerr << "adding to not found symbols location: " << pc_load << " " << fst.smodule << ":" << fst.mfunction << "' to unresolved vector\n";

}

/*
void Assembler::super_opfun_set_instruction(Opcode op, const full_symbol_t &fst) {
  s_int_t adr = -1;
  std::shared_ptr<TreeNode> sym_node = context->get_node({
    current_context.uni, 
    current_context.app,
    current_context.api, 
    "modules",
    fst.smodule, 
    "functions",
    fst.mfunction, 
    "addr"});

  if(sym_node == nullptr) {
    std::cout << "function '" << fst.mfunction << "' not found\n";
    //add_unresolved_function(fst);
    add_unresolved_sym(key_tok_t::mfunction, fst);
  } else {
    adr = std::any_cast<s_int_t>(sym_node->get_data());
  }
  instr_t asm_instr = {op, adr,0,0};
  set_instruction(asm_instr); 
}*/

void Assembler::super_opfun_set_instruction(Opcode op, const full_symbol_t &fst) {
  s_int_t adr= -1;
  std::vector<std::string> keys = move(get_sym_key(key_tok_t::mfunction, fst));
  keys.push_back("addr");
  std::shared_ptr<TreeNode> sym_node = context->get_node(keys);
  if(sym_node == nullptr) {
    std::cout << "function '" << fst.mfunction << "' not found\n";
    add_unresolved_sym(key_tok_t::mfunction, fst);
  } else {
    adr = std::any_cast<s_int_t>(sym_node->get_data());
  }
  instr_t asm_instr = {op, adr,0,0};
  set_instruction(asm_instr); 
}


/*
#define __funckeys__ {us.name.uni, us.name.app, us.name.api, "modules", us.name.smodule, "functions", us.name.mfunction, "addr"}
void Assembler::resolve_names() {
  // gothru all vector unresolvednames
  std::vector<std::string> keys;
  std::shared_ptr<TreeNode> sym_node;
  // std::cout << "trying unresolved symbols\n";

  for(auto us  : unresolved_syms) {
    // std::cout << "unresolved sym:'" << us.name.sfunction << "'\n";
    switch(us.type) {
    case key_tok_t::mvar:  break;
    case key_tok_t::mfunction:  
      sym_node = context->get_node(__funckeys__);
      if(sym_node != nullptr) {
        std::cout << "resolving function: '" << us.name.mfunction << "'\n";
        code[us.location.adr].operands[0].adr
          = std::any_cast<s_int_t>(sym_node->get_data());
      } else { 
        std::cerr << "can't resolve symbol: nullptr\n"; 
      }
      break;
    case key_tok_t::lvar:  break;
    default: break;
    }
  }
}
*/
void Assembler::resolve_names() {
  std::vector<std::string> keys;
  for(auto us  : unresolved_syms) {
    switch(us.type) {
    case key_tok_t::mvar:  break;
    case key_tok_t::mfunction:  
      code[us.location.adr].operands[0].adr
        = get_sym_addr(key_tok_t::mfunction, us.name);
    default: break;
    }
  }
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
    case  key_tok_t::mvar:
      key ={ fst.uni, fst.app, fst.api, "modules", fst.smodule,  "mvars", fst.mvar};
      break;
    case  key_tok_t::lvar:
      key ={ fst.uni, fst.app, fst.api, "modules", fst.smodule,  "functions", fst.mfunction, "lvars", fst.lvar};
      break;
    case  key_tok_t::label:
      key ={ fst.uni, fst.app, fst.api, "modules", fst.smodule,  "functions", fst.mfunction, "labels", fst.label};
      break;
    default : return {}; break;
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
    case  key_tok_t::label:
      error_str = fst.smodule + ":" + fst.mfunction + "." + fst.label;
      break;
    default:
      error_str = "not sure";
      break;
  }
  std::cerr << "can't resolve symbol:'" << error_str << "' got nullptr\n!";
  return -1;
}