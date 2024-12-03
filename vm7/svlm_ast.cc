#include "svlm_ast.hh"
#include "svlm_interactive.hh"
#include "my_helpers.hh"




#define MOD "module"
#define FRAMES "frames"
SvlmAst::SvlmAst(const OperandType&t) : Tree(t) {
  auto vptr = make_unique<AstList>();
  if(! root.add_branch({CONTEXT_UNIV, FRAMES}, move(vptr))) {
    cerr << "can't create  {" << CONTEXT_UNIV << " " << FRAMES << "}\n";
    exit(1);
  }
}
Operand SvlmAst::to_str() const {
  return string("SvlmAst PTR");
}

astexpr_u_ptr& SvlmAst::get_context() {
  auto &c= root.get_branch({CONTEXT_UNIV});
  return c.get_u_ptr_nc();
}
astexpr_u_ptr& SvlmAst::get_frames() {
  auto &c= root.get_branch({CONTEXT_UNIV, FRAMES});
  //if(c==nil_operand) {
  if(c._get_type()==OperandType::nil_t) {
    cerr << "SvlmAst::get_frames is nil_operand!\n";
    return root.AstMap::nil_ast_ptr;
  }
  return c.get_u_ptr_nc();
}
Operand& SvlmAst::get_current_frame() {
  auto &frames = get_frames();
  if(frames == root.AstMap::nil_ast_ptr) {
    return nil_operand;
  }
  return frames->back();
}

string SvlmAst::get_current_module() {
  auto& f = get_frames()->back();
  //auto &m = f[string("current_module")];
  auto &m = f["current_module"];
  //cout << "in SvlmAst::get_current_module: " << m << "\n";
  return m._to_str();
}

void SvlmAst::add_module(const Operand& mod_name, astexpr_u_ptr clist) {
  s_integer i, s=clist->size();

  get_module_subnode(mod_name, OperandType::ast_mod_t);

  for(i=0; i < s; i++) {
    auto &nan = clist->getv(i); 
    if(nan._get_type() != OperandType::uptr_t) { continue; }

    auto &nan_vptr = nan.get_u_ptr_nc();

    // sub_node could be FUNC, CLASS, VAR
    auto &sub_node = get_module_subnode(mod_name,  nan_vptr->_get_type());
    if(sub_node==nil_operand) { continue; }

    auto sub_node_name = nan.getv("name")._to_str();
    sub_node.add(sub_node_name, move(nan_vptr), true);
  }
}


Operand& SvlmAst::get_module_subnode(const Operand& mod_name, const OperandType t) {
  vector<string> keys = {CONTEXT_UNIV, MOD, mod_name._to_str()};
  switch(t) {
  case OperandType::ast_mod_t:
    //cout << "ast_mod_t!\n";
    //root.add_branch(keys, nil_operand);
    //return nil_operand;
    break;
  case OperandType::ast_func_t:
    keys.push_back("function");
    break;
  case OperandType::ast_mvar_t:
    keys.push_back("mvar");
    break;
  case OperandType::ast_class_t:
    keys.push_back("class");
    break;
  default:
    cerr << "unknown module subtype: " << Operand(t) << "! \n";
    return nil_operand;
  }

  auto &msub_node = root.get_branch(keys);
  if(msub_node==nil_operand) {
    root.add_branch(keys, make_unique<AstMap>(), true);
    auto &nd= root.get_branch(keys);
    return nd;
  }
  return msub_node;
}

void SvlmAst::add_code(const Operand&n, unique_ptr<AstExpr> c ) {
  //cout << "add code:" << MOD << " " << n << "\n";
  auto &msub_node = get_module_subnode(n, OperandType::ast_mod_t);
  auto nm = make_unique<AstMap>();
  nm->add(string("code"), move(c));
  msub_node.add(string("last"), move(nm), true);

  auto& l = root.get_branch({CONTEXT_UNIV, MOD, n._to_str()});
  //l.print(); cout << "\n";
}


Operand SvlmAst::evaluate_last_line() {
  auto& l = root.get_branch({CONTEXT_UNIV, MOD, "Prompt", "last", "code"});
  //l.print(); cout << "\n";
  auto &ctxt = get_context();
  return l.evaluate(ctxt);
  //return nullptr;
}


void SvlmAst::run_evaluate() {
  //cout << "Run eval Main::main \n";
  auto& l = root.get_branch({CONTEXT_UNIV, MOD, "Main", "function", "main", "code"});
  root.add_branch({CONTEXT_UNIV, "svlm_lang"}, Operand(this));
  //auto &c = l.get_u_ptr_nc();
  auto &ctxt = get_context();
  auto &frames = get_frames();

  auto nm = make_unique<AstMap>();
  nm->add(string("lvars"), make_unique<AstMap>());
  nm->add(string("current_module"), Operand("Main"));
  frames->add(move(nm));

  l.evaluate(ctxt);

/*
  for(s_integer i=0; i<l.size();  i++){
    auto &c = l[i];
    c.evaluate(c.get_u_ptr_nc());
  }
*/

}
//-----------------------------------------------------------------------

AstBinOp::AstBinOp(std::unique_ptr<AstExpr> l, std::unique_ptr<AstExpr> r, AstOpCode op) 
 // : AstExpr(OperandType::ast_binop_t) 
  {
  add(string("left"), move(l));
  add(string("right"), move(r));
  add(string("op"), Operand(op));
}
void AstBinOp::print() {
  //cout << "AstBinOp:\n";
  cout << to_str();
}
Operand AstBinOp::to_str() const { 
  auto &l = (*this)["left"];
  auto &r = (*this)["right"];
  auto &o = (*this)["op"];
  return  l.to_str() + o.to_str() +  r.to_str();
}
Operand AstBinOp::evaluate(astexpr_u_ptr& ctxt) {
  //cout << "in astbinop eval!\n";
  auto &l = (*this)["left"];
  auto &r = (*this)["right"];
  auto opcode = (*this)["op"]._get_opcode();

  auto rv = r.evaluate(ctxt);

  if(opcode == AstOpCode::assign) {
    AstAssign* variable =(AstAssign*) l.get_raw_ptr();
    variable->assign(ctxt, rv);
    return rv;
  }

  auto lv = l.evaluate(ctxt);

  auto result = lv.opfunc(rv, opcode);
  return result;

}


//-----------------------------------------------------------------------
AstFunc::AstFunc(const Operand &n, astexpr_u_ptr pl,  astexpr_u_ptr code_ptr) {
  name = n._to_str();
  type_ = OperandType::ast_func_t;
  add(string("name"), n);
  add(string("code"), move(code_ptr));
  add(string("proto_list"), move(pl));
}

Operand AstFunc::evaluate(astexpr_u_ptr& ctxt) {
  auto &l = map_["code"];
  cout << "in func eval!\n";
  return l.evaluate(ctxt);
}
Operand AstFunc::to_str() const {
  return string("func: ") + name;
}
Operand AstFunc::get_type() const { return OperandType::ast_func_t;}
OperandType AstFunc::_get_type() const { return OperandType::ast_func_t;}
void AstFunc::print() const { 
  cout << to_str();
  const Operand &l = map_.at("code");
  for(s_integer i=0; i<l.size(); i++) {
    cout << l[i] << "\n";
  }
}

//-----------------------------------------------------------------------
AstPrint::AstPrint(astexpr_u_ptr ptr) {
  type_= OperandType::ast_print_t;
  add(string("exp"), move(ptr));
}
Operand AstPrint::get_type() const { return OperandType::ast_print_t;}
OperandType AstPrint::_get_type() const { return OperandType::ast_print_t;}
Operand AstPrint::to_str() const {
  auto &exp = map_.at(string("exp"));
  return Operand("print ") + exp.to_str();
}
void AstPrint::print() const {
  cout << to_str();
}
Operand AstPrint::evaluate(astexpr_u_ptr& ctxt) {
  auto &exp = map_.at(string("exp"));
  cout << exp.evaluate(ctxt);
  return Operand("");
}
//-----------------------------------------------------------------------
AstCaller::AstCaller(const Operand& callee, astexpr_u_ptr arg_list) {
  type_= OperandType::ast_caller_t;
  auto modfunc = split_string(callee._to_str(), ".");
  //cout << "modfunc size" << modfunc.size() << "\n";
  if(modfunc.size() > 1) {
    add(string("callee_mod"), Operand(modfunc[0]));
    add(string("callee_func"),Operand(modfunc[1]));
  } else {
    add(string("callee_mod"), nil_operand);
    add(string("callee_func"),Operand(modfunc[0]));
  }
  add(string("arg_list"), move(arg_list));
}

Operand& AstCaller::add_frame(astexpr_u_ptr &ctxt) { 
  // use current module if call



  auto svlm_lang_ptr = ctxt->get_branch({"svlm_lang"}).get_svlm_ptr();
  auto &frames = svlm_lang_ptr->get_frames();

  auto nm = make_unique<AstMap>();
  auto lvars = make_unique<AstMap>();
  nm->add(string("current_function"), map_.at(string("callee_func")));
  nm->add(string("current_module"), map_.at(string("callee_mod")));


  auto &arg_list = map_.at(string("arg_list"));
  auto &proto_list = map_.at(string("proto_list"));
  //cout << "arg_list: " <<  arg_list << "\n";
  //cout << "proto_list: " <<  proto_list << "\n\n";
  if(arg_list.size() != proto_list.size()) {
    cerr << "Arguments do not match prototype!\n";
    return nil_operand;
  }

  if(arg_list.size() > 0 ) {
    auto arg_list_result = arg_list.evaluate(ctxt);
    for(s_integer i =0; i< arg_list_result.size(); i++) {
      lvars->add(proto_list[i], arg_list_result[i]);
    }
    // get from tree protolist and add to lvars
  }

  nm->add(string("lvars"), move(lvars));
  frames->add(move(nm));


  return frames->back();
}
Operand& AstCaller::remove_frame(astexpr_u_ptr &ctxt) { 
  auto &svlm_lang = ctxt->get_branch({"svlm_lang"});
  auto ptr = svlm_lang.get_svlm_ptr();
  auto &frames = ptr->get_frames();
  auto &f = frames->back();
  //frames->pop
  return nil_operand;
}

Operand AstCaller::get_type() const { return OperandType::ast_caller_t;}
OperandType AstCaller::_get_type() const { return OperandType::ast_caller_t;}
Operand AstCaller::to_str() const {
  auto &exp = map_.at(string("callee_func"));
  return Operand(" ") + exp.to_str();
}
void AstCaller::print() const {
  cout << "AstCaller Print: " << to_str();
}
Operand AstCaller::evaluate(astexpr_u_ptr& ctxt) {
  string module_name;
  auto svlm_lang_ptr = ctxt->get_branch({"svlm_lang"}).get_svlm_ptr();
  auto &callee_mod = map_.at(string("callee_mod"));
  auto &callee_func = map_.at(string("callee_func"));


  if(callee_mod._get_type() == OperandType::nil_t)  {
    module_name = svlm_lang_ptr->get_current_module();
  } else {
    module_name = callee_mod._to_str();
  }
  //cout << "module_name: " << module_name << "\n";

  vector<string> keys_code = {MOD, module_name,  "function", callee_func._to_str(), "code"};
  vector<string> keys_proto = {MOD, module_name,  "function", callee_func._to_str(), "proto_list"};
  //cout << "keys_code: " ; for(auto k : keys_code) { cout << k << ", "; } cout << "\n";
  auto &code = ctxt->get_branch(keys_code);
  auto &proto_list = ctxt->get_branch(keys_proto);
  AstMap::add(string("callee_mod"), Operand(module_name), true);
  AstMap::add(string("proto_list"), proto_list, true);

  add_frame(ctxt);
  auto result  = code.evaluate(ctxt);
  return result;
}


/*
string AstCaller::get_current_module(astexpr_u_ptr& ctxt) {
  auto svlm_lang_ptr = ctxt->get_branch({"svlm_lang"}).get_svlm_ptr();
  auto &frame = svlm_lang_ptr->get_current_frame();
  auto &m = frame[string("current_module")];
  //cout << "current module: " << m._to_str() << "\n";
  return m._to_str();
}
*/

s_integer AstAssign::get_index_i(astexpr_u_ptr &ctxt) {
  cout << "AstAssign::get_index_i\n";
  auto &idx_key =  getv(string("idx_key"));
  if(idx_key == nil_operand) {
      return -1;
  }
  auto result = idx_key.evaluate(ctxt);
  return result._get_int();
}

//----------------------------------------------------------------------- AstMvar
AstMvar::AstMvar(const string &v) : AstAssign(OperandType::ast_mvar_t) { 
  scale_ = OperandType::list_t;
  auto mod_var = split_string(v, ".");
  if(mod_var.size() > 1) {
    add(string("mod_name"), Operand(mod_var[0]));
    add(string("var_name"), Operand(mod_var[1]));
    return;
  }
  add(string("var_name"), Operand(v));
}
AstMvar::AstMvar(const string &v, astexpr_u_ptr idx_key) : AstAssign(OperandType::ast_mvar_t) { 
  scale_ = OperandType::list_t;
  auto mod_var = split_string(v, ".");
  add(string("idx_key"), move(idx_key));
  if(mod_var.size() > 1)  {
    add(string("mod_name"), Operand(mod_var[0]));
    add(string("var_name"), Operand(mod_var[1]));
    return;
  }
  add(string("var_name"), Operand(v));
}


string AstMvar::name() { 
  return getv(string("var_name"))._to_str();
}
string AstMvar::get_module() { 

  return getv(string("mod_name"))._to_str();
}


Operand AstMvar::get_type() const { return OperandType::ast_mvar_t;}
OperandType AstMvar::_get_type() const { return OperandType::ast_mvar_t;}
Operand AstMvar::to_str() const {
  auto &var_name= map_.at(string("var_name"));
  auto &mod_name= map_.at(string("mod_name"));
  return mod_name.to_str() + string(".") + var_name.to_str();
}
void AstMvar::print() const {
  cout << to_str();
}

// to get value from tree: module 'mname' mvar 'vname'
Operand AstMvar::evaluate(astexpr_u_ptr& ctxt) {
  //cout << "AstMvar::evalaute\n\n";

  Operand mod_name_operand;
  auto svlm_lang_ptr = ctxt->get_branch({"svlm_lang"}).get_svlm_ptr();

  if(svlm_lang_ptr==nullptr) {
    cerr << "In AstMvar::Assign svlmlang is null!\n";
    return Operand();
  }

  auto &mod_name = (*this)["mod_name"];
  auto &index_exp = (*this)["mod_name"];
  mod_name_operand = mod_name.to_str();

  if(mod_name == nil_operand)  {
    mod_name_operand  = svlm_lang_ptr->get_current_module();
    add(string("mod_name"), mod_name_operand);
  }

  auto var_name = name();

  auto &sub_node = svlm_lang_ptr->get_module_subnode(mod_name_operand,  OperandType::ast_mvar_t);
  //auto result = sub_node.getv(var_name).clone_val();
  auto &result = sub_node.getv(var_name);
  if(scale_ == OperandType::list_t){
     auto index_i = get_index_i(ctxt);
    
    if(index_i >= 0) {
      cout << "index!\n";
      return result[index_i].clone_val();
    }
  }
  return result.clone_val();
}


// to assign value to tree: module 'mname' mvar 'vname'
void AstMvar::assign(astexpr_u_ptr& ctxt, const Operand& v) {

  Operand mod_name_operand;

  auto svlm_lang_ptr = ctxt->get_branch({"svlm_lang"}).get_svlm_ptr();
  if(svlm_lang_ptr==nullptr) {
    cerr << "In AstMvar::Assign svlmlang is null!\n";
    return;
  }

  //auto &mod_name = map_.at(string("mod_name"));
  auto &mod_name = (*this)["mod_name"];
  mod_name_operand = mod_name.to_str();


  //if(mod_name == nil_operand)  {
  if(mod_name._get_type() == OperandType::nil_t)  {
     mod_name_operand = svlm_lang_ptr->get_current_module();
    add(string("mod_name"), mod_name_operand);
  }

  auto var_name = name();

  auto &sub_node = svlm_lang_ptr->get_module_subnode(mod_name_operand,  OperandType::ast_mvar_t);
  sub_node.add(var_name, v, true);

}


//-----------------------------------------------------------------------
AstLvar::AstLvar(const string &name) : AstAssign(OperandType::ast_lvar_t) { 
  add(string("var_name"), Operand(name));
}
string AstLvar::name() { return getv(string("var_name"))._to_str(); }
Operand AstLvar::get_type() const { return OperandType::ast_lvar_t;}
OperandType AstLvar::_get_type() const { return OperandType::ast_lvar_t;}
Operand AstLvar::to_str() const {
  auto &name= map_.at(string("var_name"));
  return name.to_str();
}
void AstLvar::print() const {
  cout << to_str();
}


Operand AstLvar::evaluate(astexpr_u_ptr& ctxt) {
  //cout << "AstLvar::evalaute\n";
  auto svlm_lang_ptr = ctxt->get_branch({"svlm_lang"}).get_svlm_ptr();
  if(svlm_lang_ptr==nullptr) {
    cerr << "In AstMvar::Assign svlmlang is null!\n";
    return Operand();
  }
  auto &frame = svlm_lang_ptr->get_current_frame();
  auto &lvars =  frame["lvars"];
  auto var_name = name();
  return lvars.getv(var_name).clone_val();
}

void AstLvar::assign(astexpr_u_ptr& ctxt, const Operand& v) {
  auto svlm_lang_ptr = ctxt->get_branch({"svlm_lang"}).get_svlm_ptr();
  auto &frame = svlm_lang_ptr->get_current_frame();
  auto &lvars =  frame["lvars"];
  lvars.add(name(), v);
}
//-----------------------------------------------------------------------