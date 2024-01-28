#include "assembler.hh"
#include "my_helpers.hh"

Assembler::Assembler() {
  Assembly::context = new Tree();
};

void Assembler::load(const string &filename) {
  ifstream infile(filename);
  string line; 
  elevel_t parse_status;

  if(infile.is_open()) {
    while(getline(infile, line)) {
      if(! (parse_status=parse(line))) {
        cerr << "error parsing!\n"; continue;
        continue; } 
      if(parse_status ==2) continue; // comment
      if(!decode())  cerr << "error decoding in load!\n"; }
  } else {
    cerr << "Error from assembly file: " << filename << endl;
  }
  infile.close();
  resolve_names();
}

bool Assembler::parse(const string &line) {
  clear_line();  // clear opcode str and operands strs
  if(line[0]=='#') return 2;
  if(line[0] == '%') {
    return parse_directive(line);
  } 
  return parse_instruction_string(line);
}

bool Assembler::parse_instruction_string(const string &line) {
  string tok; int i=0,j=0;
  string tokens_s[4] = {"", "", "", ""};


  istringstream sline1(line);
  while(getline(sline1, tok, ' ')) {
    tokens_s[i++] = tok;
  }
  opcode_str = tokens_s[0];

  istringstream sline2(tokens_s[1] + tokens_s[2] + tokens_s[3]);
  while(getline(sline2, tok, ',')) {
    operands_str[j++] = tok;
  }
  // cout << "parse instruction string" << "\n";
  cout << "opcode operands: " << opcode_str << " " << operands_str[0] << " " << operands_str[1] << " " << operands_str[2] << "\n";

  return true;
}

/*
void handle_resolved(){
  if(opcode_str == "call") {
    unresolved_t ut={pc_load, tokens_s[1]};
    unresolved_names.push_back(ut);
  }
};
*/

bool Assembler::parse_directive(const string &line) {
  vector<string> tokens_s = move(split_string(line, " "));
  opcode_str="%"; // to prevent decode for decoding directive
  if(tokens_s[0] == "%module")  {
    current_module =  tokens_s[1];
    context->add_node({current_module, "addr"}, pc_load);
    cout << "module: " << tokens_s[1] << "\n";
    return true;
  }
  if(tokens_s[0] == "%function")  {
    current_function =  tokens_s[1];
    context->add_node({current_module, current_function, "addr"}, pc_load);
    cout << "in function direcive: module:" << current_module << "\n";
    cout << "function: " << tokens_s[1] << " addr: " << pc_load  << "\n";
    return true;
  }
  return false;
}

bool Assembler::is_float(const string &s) {
  std::istringstream iss(s);
  float f;
  iss >> noskipws >> f; 
  return iss.eof() && !iss.fail(); 
}
bool Assembler::is_integer(const string& s) {
    std::string::const_iterator it = s.begin();
    while (it != s.end() && std::isdigit(*it)) ++it;
    return !s.empty() && it == s.end();
}

bool Assembler::operands2bin(const string& s, reg_t &operand) {
  string str = s;
  if(str[0] == 'r') {         // if operand is register, then get register number
    str.erase(0,1);
    if(is_integer(str)) {
      operand.i = stol(str);
      return 0;
    } else { return 1; }
  }
  if(is_integer(str)) {       // if operand is constant int
    operand.i = stol(str);
    return 0;
  }
  if(is_float(str)) {         // if operand is constant float
    operand.f = stold(str);
    return 0;
  }
  return 1;
}

bool Assembler::opcode2bin() {
  auto it = asm_str_lookup.find(opcode_str);
  if (it != asm_str_lookup.end()) {
    instruction.opcode = asm_str_lookup[opcode_str];
    return 0;
  } else {
    return 1; // opcode str not found
  }
}

void Assembler::clear_line() {
  opcode_str = "";
  operands_str[0] = "";
  operands_str[1] = "";
  operands_str[2] = "";
  instruction = {0,0,0,0};
}


// convert string instruction to bin instruction
bool Assembler::decode(bool from_prompt) {   
  if(opcode_str[0] == '%') { return true;}
  if(opcode2bin() != 0) {
    cerr << "error opcode2bin unknown opcode: " << opcode_str << "\n";
    return false;
  }
  if(opcode_str == "call") {  // resolve symbol for function call name
    if(!decode_call()) // store function  name addrs in insutrctions.operands[0]
      cerr << "can't decode call: " << operands_str[0]<< "\n";

  }else {      // all other operands 
    for(byte_code_t i=0; i<3; i++) {
      if(operands_str[i] == "") break;
      if(operands2bin(operands_str[i], instruction.operands[i]) !=0) {
        cerr << "error in operands2bin unknown operand: " << operands_str[i] << "\n";
        return false;
      }
    }
  }
  if(!from_prompt) code[pc_load++] = instruction;
  //else { cout << "calling from prompt: " << opcode_str << ":" << operands_str[0] << "\n"; }
  
  return true;
}

//asm: call function
//asm: call Module.function
bool Assembler::decode_call() {
  shared_ptr<TreeNode> sym_node;
  vector<string> tokens_s = move(split_string(operands_str[0], "."));
  string call_module_name = current_module;
  string call_function_name = tokens_s[0];
  string tvar = "";

  //cout << "in call opcode operands: " << opcode_str << " " << operands_str[0] << " " << operands_str[1] << " " << operands_str[2] << "\n";
  switch(tokens_s.size()) {
  case 1: 
    sym_node = context->get_node({call_module_name, tokens_s[0], "addr"}); 
    break;
  case 2: 
    call_module_name = tokens_s[0];
    call_function_name = tokens_s[1];
    sym_node = context->get_node({tokens_s[0], tokens_s[1], "addr"});  
    break;
  }
  if(sym_node == nullptr) {
    // cerr << "symbol not found: -"<< call_module_name << "-" << call_function_name << "\n";
    add_unresolved_name(call_module_name, call_function_name, tvar);
    return false;
  }
  instruction.operands[0].adr = any_cast<us_int_t>(sym_node->get_data());
  return true;

}

void Assembler::add_unresolved_name(const string &m, const string &f, const string &v) {
  unresolved_t  notfound_name;
  cerr << "adding to not found to unresolved vector\n";
  notfound_name.location.adr = pc_load;
  notfound_name.smodule=m; //tokens_s[1], ""};
  notfound_name.sfunction=f; //tokens_s[1], ""};
  notfound_name.svar=v; //tokens_s[1], ""};
  unresolved_names.push_back(notfound_name);
}
void Assembler::resolve_names() {
  // gothru all vector unresolvednmaes
  // cout << "in resolve names\n";
  shared_ptr<TreeNode> sym_node;
  for(auto s  : unresolved_names) {
    //cout << s.location.adr << ":" <<  s.smodule << s.sfunction << "\n";
    sym_node = context->get_node({s.smodule, s.sfunction, "addr"});  
    if(sym_node != nullptr) {
      code[s.location.adr].operands[0].adr = any_cast<us_int_t>(sym_node->get_data());
    }
  }
  //cout << "\n";
}