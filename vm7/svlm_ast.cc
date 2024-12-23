#include "svlm_ast.hh"
#include "svlm_interactive.hh"
#include "my_helpers.hh"

#define DEBUG_TRACE_FUNC
#include "scope_logger.hh"




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
  MYLOGGER(trace_function , string("SvlmAst::add_module(") + mod_name._to_str() + string(")") ,__func__)
  cout << "SvlmAst::add_module()\n";

  s_integer i, s=clist->size();

  get_module_subnode(mod_name, OperandType::ast_mod_t);

  for(i=0; i < s; i++) {
    auto &nan = clist->getv(i); 
  //  cout << "\nnan: " << nan << "\n";
  //  cout << "nan.get_type: " << nan.get_type() << "\n";
    if(nan._get_type() != OperandType::uptr_t) { continue; }

    auto &nan_vptr = nan.get_u_ptr_nc();

  //  cout << "nan_vptr.get_type: " << nan_vptr->get_type() << "\n";

    // sub_node could be FUNC, CLASS, VAR
    auto &sub_node = get_module_subnode(mod_name,  nan_vptr->_get_type());
    if(sub_node==nil_operand) { 
  //    cout << "sub_node == nil_operand\n";
      continue; 
    }

    auto sub_node_name = nan.getv("name")._to_str();
    sub_node.add(sub_node_name, move(nan_vptr), true);
  }
}


Operand& SvlmAst::get_module_subnode(const Operand& mod_name, const OperandType t) {
  MYLOGGER(trace_function , string("SvlmAst::get_module_subnode(") + mod_name._to_str() + string("): ") + Operand(t)._to_str()
   ,__func__)

  //cout << "SvlmAst::get_module_subnode\n";

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


  //cout << "msub_node=root.get_branch(keys): "; for(auto k: keys) { std::cout << k << ","; } std::cout << "\n";
  auto &msub_node = root.get_branch(keys);
  //cout << "msub_node: " << msub_node << "\n";

  if(msub_node==nil_operand) {
  //  cout << "msub_node is nil_operand: " << msub_node << "--add\n";
    root.add_branch(keys, make_unique<AstMap>(), true);
    auto &nd= root.get_branch(keys);
  //  cout << "new node : " << nd << "--added\n";
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
//----------------------------------------------------------------------- AstBinOp

AstBinOp::AstBinOp(astexpr_u_ptr l, astexpr_u_ptr r, AstOpCode op) 
 : type_(OperandType::ast_binop_t) 
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
  MYLOGGER(trace_function
  , "AstBinOp::evaluate(astexpr_u_ptr& ctxt)"
  , __func__);

  auto &l = (*this)["left"];
  auto &r = (*this)["right"];
  auto opcode_str = (*this)["op"]._to_str();
  auto opcode = (*this)["op"]._get_opcode();

  auto r_v = r.evaluate(ctxt);


  if(opcode == AstOpCode::assign) {
    AstAssign* variable =(AstAssign*) l.get_raw_ptr();
    //cout << "r_vptr get_type: " <<  r_vptr->get_type() << "\n";

    // to use shared pointer for list and map and maybe others
    if(r_v._get_type() == OperandType::list_t ||
      r_v._get_type() == OperandType::map_t 
      ) {
      //cout << "assigning list_t || map_t || tuple_t !\n ";
      Operand rv = r_v.clone();
      variable->assign(ctxt, rv); 
    } else {
      cout << "assigning regular var!\n";
      cout << "var:" << r_v << "\n";
      cout << "type:" << r_v.get_type() << "\n\n";
      //variable->assign(ctxt, r_vptr->clone());
      variable->assign(ctxt, r_v);
    }

    return r_v;
  }

  auto l_v = l.evaluate(ctxt);

  auto result = l_v.opfunc(r_v, opcode);
  return result;

}


//----------------------------------------------------------------------- AstFunc
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

//----------------------------------------------------------------------- AstPrint
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
  return Operand("").evaluate(ctxt);
}
//----------------------------------------------------------------------- AstCaller
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
    s_integer s = arg_list_result.size();
    for(s_integer i =0; i< s; i++) {
      //lvars->add(proto_list[i], arg_list_result[i]);
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
  auto &idx_key =  getv(string("idx_key"));
  if(idx_key == nil_operand) {
      return -1;
  }
  auto result = idx_key.evaluate(ctxt);

  if(result._get_type()==OperandType::str_t) {
    return -1;
  }

  return result._get_int();
}
string AstAssign::get_index_s(astexpr_u_ptr &ctxt) {
  auto &idx_key =  getv(string("idx_key"));
  if(idx_key == nil_operand) {
    return "";
  }
  auto result = idx_key.evaluate(ctxt);
  if(result._get_type()==OperandType::num_t) {
    return "";
  }
  return result.to_str()._to_str();
}

//----------------------------------------------------------------------- AstMvar
AstMvar::AstMvar(const string &v) : AstAssign(OperandType::ast_mvar_t) { 
  MYLOGGER(trace_function
  , "AstMvar::AstMvar(const string &v)"
  , __func__
  )
  MYLOGGER_MSG(trace_function, string("var_name: ") + v)

  scale_ = OperandType::scalar_t;
  auto mod_var = split_string(v, ".");
  if(mod_var.size() > 1) {
    add(string("mod_name"), Operand(mod_var[0]));
    add(string("var_name"), Operand(mod_var[1]));
    return;
  }
  add(string("var_name"), Operand(v));
}

astexpr_u_ptr AstMvar::clone() const {
  auto &var_name= (*this)["var_name"];
  auto &mod_name= (*this)["mod_name"];
  //return make_unique<AstMvar>(mod_name + var_name);
  return nullptr;
}

AstMvar::AstMvar(const string &v, astexpr_u_ptr idx_key) : AstAssign(OperandType::ast_mvar_t) { 
  scale_ = OperandType::array_t;
  auto mod_var = split_string(v, ".");
  add(string("idx_key"), move(idx_key));
  if(mod_var.size() > 1)  {
    add(string("mod_name"), Operand(mod_var[0]));
    add(string("var_name"), Operand(mod_var[1]));
    return;
  }
  add(string("var_name"), Operand(v));
}

const Operand& AstMvar::getv() const {
  cout << "AstMvar::getv()\n";
  //return clone();
  return nil_operand;
}
string AstMvar::name() { 
  return AstMap::getv(string("var_name"))._to_str();
}
string AstMvar::get_module() { 
  return AstMap::getv(string("mod_name"))._to_str();
}


Operand AstMvar::get_type() const { 
  cout << "AstMvar::get_type()\n";
  return OperandType::ast_mvar_t;
}
OperandType AstMvar::_get_type() const { return OperandType::ast_mvar_t;}
Operand AstMvar::to_str() const {
  //auto &var_name= map_.at(string("var_name"));
  //auto &mod_name= map_.at(string("mod_name"));

  auto &var_name= (*this)["var_name"];
  auto &mod_name= (*this)["mod_name"];

  if(mod_name==nil_operand) {
    return Operand("$") +  var_name.to_str();
  }

  return mod_name.to_str() + string(".") + var_name.to_str();
}
void AstMvar::print() const {
  cout << to_str();
}

// to get value from tree: module 'mname' mvar 'vname'
Operand AstMvar::evaluate(astexpr_u_ptr& ctxt) {
  MYLOGGER(trace_function
  , "AstMvar::evaluate(astexpr_u_ptr& ctxt)"
  , __func__
  )
  MYLOGGER_MSG(trace_function, string("var_name: ") + name())
  
  //cout << "AstMvar::evalaute\n\n";

  Operand mod_name_operand;
  auto svlm_lang_ptr = ctxt->get_branch({"svlm_lang"}).get_svlm_ptr();

  if(svlm_lang_ptr==nullptr) {
    cerr << "In AstMvar::Assign svlmlang is null!\n";
    return Operand();
  }

  auto &mod_name = (*this)["mod_name"];
  mod_name_operand = mod_name.to_str();

  if(mod_name == nil_operand)  {
    mod_name_operand  = svlm_lang_ptr->get_current_module();
    add(string("mod_name"), mod_name_operand);
  }

  auto var_name = name();

  auto &sub_node = svlm_lang_ptr->get_module_subnode(mod_name_operand,  OperandType::ast_mvar_t);
  auto &result_var = sub_node.getv(var_name);


  if(scale_ == OperandType::array_t){
    auto index_i = get_index_i(ctxt);
    if(index_i >= 0) {
      //return result_var[index_i].clone_val();
      cout << "index i: " << index_i << "\n";
      cout <<  result_var[index_i] << "\n";
      return result_var[index_i].clone();
    }

    auto index_s = get_index_s(ctxt);
    if(index_s != "" ) {
      //return result_var[index_s].clone_val();
      return result_var[index_s].clone();
    }
    return Operand();
  }
  /*
  cout << "var gettype: " << get_type() << "\n";
  cout << "eval result_var: " << result_var << "\n";
  cout << "eval result_var gettype: " << result_var.get_type() << "\n";
  if(result_var._get_type() == OperandType::uptr_t) {
    cout << "mvar eval return u_ptr\n";
    return result_var.get_u_ptr_nc();
  }
  */
  //return result_var.clone_val();
  if(result_var._get_type() == OperandType::uptr_t) {
    //cout << "evalute returning clone_usu()\n";
    return result_var.clone_usu();
  }
  //cout << "evalute returning just clone()\n";
  //return result_var.clone();
  return result_var._get_value();
}


// to assign value to tree: module 'mname' mvar 'vname'
bool AstMvar::assign(astexpr_u_ptr& ctxt, Operand &v) {
  MYLOGGER(trace_function
  , "AstMvar::assign(astexpr_u_ptr& ctxt, const Operand& v)" 
  , __func__);
  MYLOGGER_MSG(trace_function, name() + string(" = ") + v.to_str()._to_str());

  Operand mod_name_operand;

  auto svlm_lang_ptr = ctxt->get_branch({"svlm_lang"}).get_svlm_ptr();
  if(svlm_lang_ptr==nullptr) {
    cerr << "In AstMvar::Assign svlmlang is null!\n";
    return false;
  }

  auto &mod_name = (*this)["mod_name"];
  mod_name_operand = mod_name.to_str();


  if(mod_name == nil_operand)  {
     mod_name_operand = svlm_lang_ptr->get_current_module();
    add(string("mod_name"), mod_name_operand);
  }


  auto var_name = name();

  auto &sub_node = svlm_lang_ptr->get_module_subnode(mod_name_operand,  OperandType::ast_mvar_t);


  //cout << "mvar assign\n";
  //cout << "vptr (): " << vptr << "\n";
  //cout << "vptr get_type(): " << vptr->get_type() << "\n";
  //cout << "v.getv().get_type():" << v.getv().get_type() << "\n";


  if(scale_ == OperandType::array_t){
    auto &result = sub_node.getv(var_name);

    auto index_i = get_index_i(ctxt);
    if(index_i >= 0) {
      cout << "assign mvar[i] settting value!\n";
      result.set(index_i, v);
      cout << "result: " << result << "\n";
      cout << "result gettype: " << result.get_type() << "\n";
      return true;
    }
    auto index_s = get_index_s(ctxt);
    if(index_s != "" ) {
      cout << "assign mvar[s] settting value!\n";
        result.add(index_s, v, true);
      return true;
    }
  }
  MYLOGGER_MSG(trace_function, "sub_node.add() before");

  sub_node.add(var_name, v, true);

  MYLOGGER_MSG(trace_function, "sub_node.add() after");
  return true;

}


//----------------------------------------------------------------------- AstLvar
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
  return lvars.getv(var_name).clone();
}

bool AstLvar::assign(astexpr_u_ptr& ctxt, Operand& v) {
  auto svlm_lang_ptr = ctxt->get_branch({"svlm_lang"}).get_svlm_ptr();
  auto &frame = svlm_lang_ptr->get_current_frame();
  auto &lvars =  frame["lvars"];
  lvars.add(name(), v);

  return true;
}
//----------------------------------------------------------------------- Tuple
AstTuple::AstTuple(astexpr_u_ptr u_tuple) : AstAssign(OperandType::ast_tuple_t){ 
  //cout << "AstTuple::AstTuple()\n";
  AstMap::add(string("u_tuple"), move(u_tuple));
}
string AstTuple::name() {return "tuple name";}

Operand AstTuple::to_str() const {
  auto tuple_ = (*this)["u_tuple"].get_raw_ptr();

  s_integer i, s = tuple_->size();
  Operand outstr("{");
  if(s==0) {return Operand("{}");}

  for(i=0; i<s-1; i++) {
    outstr = outstr + tuple_->getv(i).to_str() + ",";
  }
  outstr = outstr + tuple_->getv(i).to_str() + "}";
  return outstr;
}


Operand AstTuple::get_type() const {
  return OperandType::ast_tuple_t;
}
OperandType AstTuple::_get_type() const {
  return OperandType::ast_tuple_t;

}
Operand AstTuple::evaluate(astexpr_u_ptr& ctxt) {
  cout << "AstTuple::eval\n";

  auto &u_tuple = (*this)["u_tuple"];
  //cout << "u_tuple " << u_tuple << "\n";

  auto e_tuple  = u_tuple.evaluate(ctxt);
  add(string("e_tuple"), make_unique<AstTuple>(e_tuple.clone()));
  //cout << "e_tuple " << e_tuple << "\n\n";

  return e_tuple;
}
astexpr_u_ptr AstTuple::clone() const {
  cout << "AstTuple::clone()\n";
  auto &u_tuple= (*this)["u_tuple"];
  return  make_unique<AstTuple>(u_tuple.clone());
}
astexpr_u_ptr AstTuple::clone_usu() {
  cout << "AstTuple::clone_usu()\n";
  auto &u_tuple= (*this)["u_tuple"];
  cout << "elist: "  << u_tuple<< "\n";
  return  make_unique<AstTuple>(u_tuple.clone_usu());
}


astexpr_u_ptr AstTuple::elemptr(const Operand& v) {

  return nullptr;

}


bool AstTuple::assign(astexpr_u_ptr& ctxt, Operand& v) {
  cout << "AstTuple::assign()\n";
  auto &u_tuple = (*this)["u_tuple"];
  auto e_tuple = evaluate(ctxt);

  if(u_tuple.size() != v.size()) return false;

  for(s_integer i=0; i < u_tuple.size(); i++) {

    if( u_tuple[i].get_u_ptr()->_get_type() == OperandType::ast_lvar_t || 
        u_tuple[i].get_u_ptr()->_get_type() == OperandType::ast_mvar_t)  {
        cout << "found var!\n";
        continue;
    }

    if(e_tuple.getv(i).getv() != v.getv(i).getv()) {
      cout << e_tuple << " != " << v << "\n";
      return false;
    }
  }
  cout << "\n\n";
  for(s_integer i=0; i < u_tuple.size(); i++) {
    if( u_tuple[i].get_u_ptr()->_get_type() == OperandType::ast_lvar_t || 
        u_tuple[i].get_u_ptr()->_get_type() == OperandType::ast_mvar_t)  {
      auto r_var =(AstAssign*) u_tuple[i].get_raw_ptr();
      Operand rv = v.getv(i).clone();
      //r_var->assign(ctxt, v.getv(i).clone());
      r_var->assign(ctxt, rv);
    }
  }
  //cout << e_tuple << "= " << vptr << "\n";
  return true;
}
void AstTuple::print() const {
  cout << "ast_tuple: " << to_str();
}

