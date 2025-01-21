#include "svlm_ast.hh"
#include "svlm_interactive.hh"
#include "my_helpers.hh"
#include "operand_vars.hh"

#define SLOG_DEBUG_TRACE_FUNC
#include "scope_logger.hh"

#define MOD "module"
#define FRAMES "frames"

SvlmAst::SvlmAst(const OperandType&t) : Tree(t) {
  MYLOGGER(trace_function , string("SvlmAst::SvlmAst()") , __func__, SLOG_FUNC_INFO);
  cout << "SvlmAst::SvlmAst()\n";

  Operand ov(list_t{});

  if(! root.add(vec_str_t{CONTEXT_UNIV, FRAMES}, ov.clone(), true)) {
    cerr << "can't create  {" << CONTEXT_UNIV << " " << FRAMES << "}\n";
    exit(1);
  }
  if(! root.add(vec_str_t{CONTEXT_UNIV, "svlm_lang"},  this, true)) {
    cerr << "can't add {" << CONTEXT_UNIV << " svlm_lang  }\n";
    exit(1);
  }

  //cout << "&root " << &root << "\n"; cout << "root " << root << "\n";
}
Operand SvlmAst::to_str() const {
  return string("SvlmAst PTR");
}

astnode_u_ptr& SvlmAst::get_context() {
  //auto &c= root[vec_str_t{CONTEXT_UNIV}];
  auto &c= root[CONTEXT_UNIV];
  return c.get_u_ptr_nc();
}
astnode_u_ptr& SvlmAst::get_frames() {
  MYLOGGER(trace_function , string("SvlmAst::get_frames()") , __func__, SLOG_FUNC_INFO+9);
  auto &c= root[vec_str_t{CONTEXT_UNIV, FRAMES}];
  //cout << "&root " << &root << "\n"; cout << "root " << root << "\n";
  //if(c==nil_operand) {
  if(c.is_nil()) {
    cerr << "SvlmAst::get_frames is nil_operand!\n";
    return nil_ast_ptr_nc;
  }
  cout << "frames c: " << c << "\n";
  return c.get_u_ptr_nc();
}

Operand& SvlmAst::get_current_frame() {
  MYLOGGER(trace_function , string("SvlmAst::get_current_frame()")  ,__func__, SLOG_FUNC_INFO + 9)
  auto &frames = get_frames();
  if(frames == nil_operand_ptr_nc) {
    return nil_operand_nc;
  }
  return frames->back_nc();
}

string SvlmAst::get_current_module() {
  auto& f = get_frames()->back();
  auto &m = f["current_module"];
  //cout << "in SvlmAst::get_current_module: " << m << "\n";
  return m._to_str();
}

void SvlmAst::add_module(const Operand& mod_name, list_u_ptr clist_ptr) {
  MYLOGGER(trace_function , string("SvlmAst::add_module()"),__func__, SLOG_FUNC_INFO)
  MYLOGGER_MSG(trace_function, mod_name._to_str(), SLOG_FUNC_INFO);
  MYLOGGER_MSG(trace_function, string("clist: ") + clist_ptr->to_str()._to_str(), SLOG_FUNC_INFO);

/*
  MYLOGGER_MSG(trace_function, "---good---", SLOG_FUNC_INFO);
  Operand code(clist_ptr->clone());
  MYLOGGER_MSG(trace_function, "---good---", SLOG_FUNC_INFO);
  cout << "clist: code: " << *clist_ptr<< "\n";
  MYLOGGER_MSG(trace_function, "---bad---", SLOG_FUNC_INFO);
  cout << "addmodule: code: " << code << "\n";
  MYLOGGER_MSG(trace_function, "--------", SLOG_FUNC_INFO);
*/


  auto &clist = clist_ptr->_get_list_nc();

  s_integer i, s=clist.size();

  get_module_subnode(mod_name, OperandType::ast_mod_t); // create|get module name first by calling this function

  for(i=0; i < s; i++) {
    auto &nan = clist[i]; 
    cout << "\nnan: " << nan << "\n";
    cout << "nan.get_type: " << nan.get_type() << "\n";
    if(nan._get_type() != OperandType::uptr_t) { continue; }

    auto &nan_vptr = nan.get_u_ptr();

    cout << "nan_vptr.get_type: " << nan_vptr->get_type() << "\n";
    cout << "*nan_vptr: " << *nan_vptr << "\n";

    // sub_node could be FUNC, CLASS, VAR
    auto &msub_node = get_module_subnode(mod_name,  nan_vptr->_get_type());
    cout << "msub_node: " << msub_node << "\n";

/*
    if(msub_node.is_nil()) { 
      cout << "msub_node is_nil: " <<  msub_node << ", skip and continue\n"; 
      continue; 
    }
*/

    auto sub_node_name = (*nan_vptr)["name"]._to_str();
    cout << "subnodename: " <<  sub_node_name<< "\n";
    //sub_node.add(sub_node_name, move(nan_vptr), true);
    msub_node.add(sub_node_name, nan_vptr->clone(), true);
  }
  //cout << "\n\n";
}


Operand& SvlmAst::get_module_subnode(const Operand& mod_name, const OperandType t) {
  MYLOGGER(trace_function , string("SvlmAst::get_module_subnode()") ,__func__, SLOG_FUNC_INFO);
  MYLOGGER_MSG(trace_function, mod_name._to_str() + string(":") + Operand(t)._to_str(), SLOG_FUNC_INFO);

 // cout << "SvlmAst::get_module_subnode, type" <<  Operand(t) <<"\n";

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
    return nil_operand_nc;
  }


  cout << "msub_node=root[keys]: "; for(auto k: keys) { std::cout << k << ","; } std::cout << "\n";
  auto &msub_node = root[keys];

  // ex, if key mvar, create it if it's not found==nil, else return already
  // found. so that we won't overwrite the existing mvar varaibles in it.
  if(msub_node.is_nil()) {
    cout << "'msub_node' is_nil: " << msub_node << ", adding\n";
    root.add(keys, make_unique<AstMap>(), true);

    auto &new_msub_node= root[keys];
    cout << "now 'msub_node' is: " << new_msub_node << "--added\n\n";
    if(new_msub_node.is_nil()) {cout << "new msubnode is nil\n"; }
    return new_msub_node;
  }
  return msub_node;
}

void SvlmAst::add_code(const Operand& name, list_u_ptr clist) {
  MYLOGGER(trace_function , string("SvlmAst::add_code('") + name._to_str() + string("')") ,__func__, SLOG_FUNC_INFO+9)
  //cout << "add code:" << MOD << " " << n << "\n";
  auto &msub_node = get_module_subnode(name, OperandType::ast_mod_t);
  auto new_map=make_unique<AstMap>();
  new_map->add(string("code"), move(clist), true);
  msub_node.add(string("last"), move(new_map), true);

  //auto& l = root[vec_str_t{CONTEXT_UNIV, MOD, name._to_str()}];
  //l.print(); cout << "\n";
}

Operand SvlmAst::evaluate_prompt_line() {
  MYLOGGER(trace_function , "SvlmAst::evaluate_prompt_line()" , string("SvlmAst::")  + string(__func__), SLOG_FUNC_INFO);
  cout <<"SvlmAst::evaluate_prompt_line()\n";
  auto& l = root[vec_str_t{CONTEXT_UNIV, MOD, "Prompt", "last", "code"}];
  auto Lptr = l.get_list_ptr_nc();
  //l.print(); cout << "\n";
  auto &ctxt = get_context();
  return Lptr->evaluate(ctxt);
}

void SvlmAst::run_evaluate() {
  MYLOGGER(trace_function , "SvlmAst::run_evaluate()" , string("SvlmAst::")  + string(__func__), SLOG_FUNC_INFO);
  //cout << "Run eval Main::main \n";
  auto Lptr = root[vec_str_t{CONTEXT_UNIV, MOD, "Main", "function", "main", "code"}].get_list_ptr_nc();
  //root.add(vec_str_t{CONTEXT_UNIV, "svlm_lang"},  this, true);
  //auto &c = l.get_u_ptr_nc();
  auto &ctxt = get_context();
  auto &frames = get_frames();

  if(frames == nullptr) {
    cerr << "frames: ptr is nullptr!\n";
    exit(1);
  }

  auto new_map=make_unique<AstMap>();

  new_map->add(string("lvars"), make_unique<AstMap>(), true);
  new_map->add(string("current_module"), Operand("Main"));
  frames->add(move(new_map));
  Lptr->evaluate(ctxt);

/*
  for(s_integer i=0; i<l.size();  i++){
    auto &c = l[i];
    c.evaluate(c.get_u_ptr_nc());
  }
*/

}
//----------------------------------------------------------------------- AstBinOp
AstBinOp::AstBinOp(astnode_u_ptr l, astnode_u_ptr r, AstOpCode op) 
 : AstExpr(OperandType::ast_binop_t) {
  node["left"]= move(l);
  node["right"]= move(r);
  node["op"]= op;
}

void AstBinOp::print() {
  //cout << "AstBinOp:\n";
  cout << to_str();
}
Operand AstBinOp::to_str() const { 
  MYLOGGER(trace_function , "AstBinOp::to_str()" , __func__, SLOG_FUNC_INFO);
  //cout << "AstBinOp::to_str()\n";

  auto &l = node["left"];
  auto &r = node["right"];
  auto &o = node["op"];
  return  l.to_str() + o.to_str() +  r.to_str();
}
Operand AstBinOp::evaluate(astnode_u_ptr& ctxt) {
  MYLOGGER(trace_function , "AstBinOp::evaluate(astnode_u_ptr& ctxt)" , __func__, SLOG_FUNC_INFO);


  //auto &l = (*this)["left"];
  auto &l = node["left"];
  auto &r = node["right"];
  auto opcode_str = node["op"]._to_str();
  auto &op = node["op"];
  auto opcode = node["op"]._get_opcode();

  MYLOGGER_MSG(trace_function, string("AstBinOp::") + string(__func__) + string(" ") +  l._to_str()  + opcode_str + r._to_str(), SLOG_FUNC_INFO);

  cout << "l: " << l << "\n";
  cout << "l.type: " << l.get_type() << "\n";
  cout << "op.gettype(): " << op.get_type()<< "\n";
  cout << "opcode_str: " << opcode_str << "\n";
  cout << "r.type: " << r.get_type() << "\n";
  cout << "r: " << r << "\n\n";

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

  //l_v.to_shared(); r_v.to_shared();

  auto result = l_v.opfunc(r_v, opcode);
  return result;

}


//----------------------------------------------------------------------- AstFunc
AstFunc::AstFunc(const Operand &n, astnode_u_ptr pl,  astnode_u_ptr code_ptr) 
: AstExpr(OperandType::ast_func_t) {
  MYLOGGER(trace_function , "AstFunc::AstFunc()" , __func__, SLOG_FUNC_INFO);
  MYLOGGER_MSG(trace_function, string("clist: ") + code_ptr->to_str()._to_str(), SLOG_FUNC_INFO);

  //cout << "AstFunc::AstFunc(" << n <<")\n";
  //name = n._to_str();
  type_ = OperandType::ast_func_t;

  //  cout << "code_ptr: "<< code_ptr<< "\n";
  //root["name"] = move(n.clone());
  node["name"] = n._to_str();
  node["code"] = move(code_ptr);
  node["proto_list"] = move(pl);
}

Operand AstFunc::evaluate(astnode_u_ptr& ctxt) {
  cout << "AstFunc::evaluate()\n";
  auto &l = node["code"];
  return l.evaluate(ctxt);
}

Operand AstFunc::to_str() const {
  //return string("func: ") + name;
  return string("func: ") + node["name"]._to_str() + node["code"]._to_str();
}
Operand AstFunc::get_type() const { return OperandType::ast_func_t;}
OperandType AstFunc::_get_type() const { return OperandType::ast_func_t;}
void AstFunc::print() const { 
  cout << to_str();
  const Operand &l = node["code"];
  for(s_integer i=0; i<l.size(); i++) {
    cout << l[i] << "\n";
  }
}

//----------------------------------------------------------------------- AstPrint
AstPrint::AstPrint(astnode_u_ptr ptr) : AstExpr(OperandType::ast_print_t) {
  node["exp"]=move(ptr);
}
Operand AstPrint::get_type() const { return OperandType::ast_print_t;}
OperandType AstPrint::_get_type() const { return OperandType::ast_print_t;}

Operand AstPrint::to_str() const {
  //auto &exp = map_.at(string("exp"));
  auto &exp = node["exp"];
  return Operand("print ") + exp.to_str();
}
void AstPrint::print() const {
  cout << to_str();
}
Operand AstPrint::evaluate(astnode_u_ptr& ctxt) {
  auto &exp = node["exp"];
  cout << exp.evaluate(ctxt);
  return Operand("").evaluate(ctxt);
}
//----------------------------------------------------------------------- AstCaller
AstCaller::AstCaller(const Operand& callee, astnode_u_ptr arg_list) 
: AstExpr(OperandType::ast_caller_t)
{
  auto modfunc = split_string(callee._to_str(), ".");
  //cout << "modfunc size" << modfunc.size() << "\n";
  if(modfunc.size() > 1) {
    node["callee_mod"]= modfunc[0];
    node["callee_func"]=modfunc[1];
  } else {
    node["callee_mod"] = Operand();
    node["callee_func"] = modfunc[0];
  }
  node["arg_list"]= move(arg_list);
}

Operand& AstCaller::add_frame(astnode_u_ptr &ctxt) { 
  MYLOGGER(trace_function , "AstCaller::add_frame()" , __func__, SLOG_FUNC_INFO);
  // use current module if call


  //auto svlm_lang = ctxt->root["svlm_lang"];
  //auto svlm_lang_ptr = ctxt->root["svlm_lang"].get_svlm_ptr();

  auto svlm_lang_ptr = (*ctxt)["svlm_lang"].get_svlm_ptr();
  auto &frames = svlm_lang_ptr->get_frames();

  auto nm = make_unique<AstMap>();
  auto lvars = make_unique<AstMap>();
  nm->add("current_function", node["callee_func"], true);
  nm->add("current_module",   node["callee_mod"], true);


  auto &arg_list = node["arg_list"];
  auto &proto_list = node["proto_list"];

  //cout << "arg_list: " <<  arg_list << "\n";
  //cout << "proto_list: " <<  proto_list << "\n\n";
  if(arg_list.size() != proto_list.size()) {
    cerr << "Arguments do not match prototype!\n";
    return nil_operand_nc;
  }

  if(arg_list.size() > 0 ) {
    auto arg_list_result = arg_list.evaluate(ctxt);
    s_integer s = arg_list_result.size();
    for(s_integer i =0; i< s; i++) {
      //lvars->add(proto_list[i], arg_list_result[i]);
      lvars->add(proto_list[i]._to_str(), arg_list_result[i], true);
    }
    // get from tree protolist and add to lvars
  }

  nm->add(string("lvars"), move(lvars), true);
  frames->add(move(nm));



  return frames->back_nc();
}
Operand& AstCaller::remove_frame(astnode_u_ptr &ctxt) { 
  auto &svlm_lang = (*ctxt)["svlm_lang"];
  auto ptr = svlm_lang.get_svlm_ptr();
  auto &frames = ptr->get_frames();
  auto &f = frames->back();
  //frames->pop
  return nil_operand_nc;
}

Operand AstCaller::get_type() const { return OperandType::ast_caller_t;}
OperandType AstCaller::_get_type() const { return OperandType::ast_caller_t;}
Operand AstCaller::to_str() const {
  auto &exp = node["callee_func"];
  return Operand(" ") + exp.to_str();
}
void AstCaller::print() const {
  cout << "AstCaller Print: " << to_str();
}
Operand AstCaller::evaluate(astnode_u_ptr& ctxt) {
  string module_name;
  auto svlm_lang_ptr = (*ctxt)["svlm_lang"].get_svlm_ptr();
  auto &callee_mod = node["callee_mod"];
  auto &callee_func = node["callee_func"];


  if(callee_mod._get_type() == OperandType::nil_t)  {
    module_name = svlm_lang_ptr->get_current_module();
  } else {
    module_name = callee_mod._to_str();
  }
  //cout << "module_name: " << module_name << "\n";

  vector<string> keys_code = {MOD, module_name,  "function", callee_func._to_str(), "code"};
  vector<string> keys_proto = {MOD, module_name,  "function", callee_func._to_str(), "proto_list"};
  //cout << "keys_code: " ; for(auto k : keys_code) { cout << k << ", "; } cout << "\n";
  //auto &code = ctxt->get_branch(keys_code);
  auto &code = (*ctxt)[keys_code];
  auto &proto_list = (*ctxt)[keys_proto];
  node.add("callee_mod", Operand(module_name), true);
  node.add("proto_list", proto_list, true);

  add_frame(ctxt);
  auto result  = code.evaluate(ctxt);
  return result;
}


/*
string AstCaller::get_current_module(astnode_u_ptr& ctxt) {
  auto svlm_lang_ptr = ctxt->get_branch({"svlm_lang"}).get_svlm_ptr();
  auto &frame = svlm_lang_ptr->get_current_frame();
  auto &m = frame[string("current_module")];
  //cout << "current module: " << m._to_str() << "\n";
  return m._to_str();
}
*/

s_integer AstAssign::get_index_i(astnode_u_ptr &ctxt) {
  auto &idx_key =  node["idx_key"];
  if(idx_key.is_nil() ) {
      return -1;
  }
  auto result = idx_key.evaluate(ctxt);

  if(result._get_type()==OperandType::str_t) {
    return -1;
  }

  return result._get_int();
}
string AstAssign::get_index_s(astnode_u_ptr &ctxt) {
  auto &idx_key =  node["idx_key"];
  if(idx_key.is_nil()) {
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
  MYLOGGER(trace_function , "AstMvar::AstMvar(const string &v)" , __func__ , SLOG_FUNC_INFO)
  MYLOGGER_MSG(trace_function, string("var_name: ") + v, SLOG_FUNC_INFO)

  scale_ = OperandType::scalar_t;
  auto mod_var = split_string(v, ".");
  if(mod_var.size() > 1) {
    add(string("mod_name"), Operand(mod_var[0]));
    add(string("var_name"), Operand(mod_var[1]));
    return;
  }
  add(string("var_name"), Operand(v));
}

AstMvar::AstMvar(const string &v, astnode_u_ptr idx_key) : AstAssign(OperandType::ast_mvar_t) { 
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

string AstMvar::name() { 
  return node["var_name"]._to_str();
}
string AstMvar::get_module() { 
  return node["mod_name"]._to_str();
}
astnode_u_ptr AstMvar::clone() const {
  cout << "AstMvar::clone()\n";
  return AstMap::clone();
};


Operand AstMvar::get_type() const { 
  cout << "AstMvar::get_type()\n";
  return OperandType::ast_mvar_t;
}
OperandType AstMvar::_get_type() const { return OperandType::ast_mvar_t;}
Operand AstMvar::to_str() const {
  //auto &var_name= map_.at(string("var_name"));
  //auto &mod_name= map_.at(string("mod_name"));

  auto &var_name= node["var_name"];
  auto &mod_name= node["mod_name"];

  if(mod_name.is_nil()){
    return Operand("$") +  var_name.to_str();
  }

  return mod_name.to_str() + string(".") + var_name.to_str();
}
void AstMvar::print() const {
  cout << to_str();
}

// to get value from tree: module 'mname' mvar 'vname'
Operand AstMvar::evaluate(astnode_u_ptr& ctxt) {
  MYLOGGER(trace_function , "AstMvar::evaluate(astnode_u_ptr& ctxt)" , __func__,  SLOG_FUNC_INFO )
  MYLOGGER_MSG(trace_function, string("var_name: ") + name(), SLOG_FUNC_INFO)
  
  //cout << "AstMvar::evalaute\n\n";

  Operand mod_name_operand;
  auto svlm_lang_ptr = (*ctxt)["svlm_lang"].get_svlm_ptr();

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
  //auto &result_var = sub_node.getv(var_name);
  auto &result_var = sub_node[var_name];


  if(scale_ == OperandType::array_t){
    auto index_i = get_index_i(ctxt);
    if(index_i >= 0) {
      //return result_var[index_i].clone_val();
      cout << "index i: " << index_i << "\n";
      //cout <<  "result_var: " <<  result_var << "\n";
      //cout <<  "result_var.gettype(): " <<  result_var.get_type() << "\n";
      //cout <<  result_var[index_i] << "\n";
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
    //return result_var.clone_usu();
    return result_var.clone();
  }
  //cout << "evalute returning just clone()\n";
  //return result_var.clone();
  return result_var._get_variant();
  //return result_var.evaluate(ctxt);
}


// to assign value to tree: module 'mname' mvar 'vname'
bool AstMvar::assign(astnode_u_ptr& ctxt, Operand &v) {
  MYLOGGER(trace_function
  , "AstMvar::assign(astnode_u_ptr& ctxt, const Operand& v)" 
  , string("AstMvar::") + string(__func__), SLOG_FUNC_INFO);
  MYLOGGER_MSG(trace_function, name() + string(" = ") + v.to_str()._to_str(), SLOG_FUNC_INFO);

  Operand mod_name_operand;

  auto svlm_lang_ptr = (*ctxt)["svlm_lang"].get_svlm_ptr();
  if(svlm_lang_ptr==nullptr) {
    cerr << "In AstMvar::Assign svlmlang is null!\n";
    return false;
  }

  auto &mod_name = (*this)["mod_name"];
  mod_name_operand = mod_name.to_str();


  if(mod_name.is_nil() )  {
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
    //auto &result = sub_node.getv(var_name);
    auto &result = sub_node[var_name];

    auto index_i = get_index_i(ctxt);
    if(index_i >= 0) {
      cout << "assign mvar[i] settting value!\n";
      //result.set(index_i, v);
      result[index_i] = v.clone();
      cout << "result: " << result << "\n";
      cout << "result gettype: " << result.get_type() << "\n";
      return true;
    }
    auto index_s = get_index_s(ctxt);
    if(index_s != "" ) {
      cout << "assign mvar[s] settting value!\n";
      cout << "index_s: " <<  index_s << "\n";
      cout << "v: " << v << "\n";
      result.add(index_s, v, true);
      return true;
    }
  }
  MYLOGGER_MSG(trace_function, "sub_node.add() before", SLOG_FUNC_INFO);

  //cout << "sub_node: " << sub_node << "\n";
  //cout << "v.type(): " << v.get_type() << "\n";

  if(v._get_type() == OperandType::uptr_t) v.to_shared();

  //cout << "v.type(): " << v.get_type() << "\n";

  sub_node.add(var_name, v, true);

  MYLOGGER_MSG(trace_function, "sub_node.add() after", SLOG_FUNC_INFO);
  return true;

}


//----------------------------------------------------------------------- AstLvar
AstLvar::AstLvar(const string &name) : AstAssign(OperandType::ast_lvar_t) { 
  add(string("var_name"), Operand(name));
}
string AstLvar::name() { return node["var_name"]._to_str(); }

Operand AstLvar::get_type() const { return OperandType::ast_lvar_t;}

OperandType AstLvar::_get_type() const { return OperandType::ast_lvar_t;}

Operand AstLvar::to_str() const { return node["var_name"].to_str(); }

void AstLvar::print() const {
  cout << to_str();
}


Operand AstLvar::evaluate(astnode_u_ptr& ctxt) {
  //cout << "AstLvar::evalaute\n";
  auto svlm_lang_ptr = (*ctxt)["svlm_lang"].get_svlm_ptr();
  if(svlm_lang_ptr==nullptr) {
    cerr << "In AstMvar::Assign svlmlang is null!\n";
    return Operand();
  }
  auto &frame = svlm_lang_ptr->get_current_frame();
  auto &lvars =  frame["lvars"];
  auto var_name = name();
  return lvars[var_name].clone();
}

bool AstLvar::assign(astnode_u_ptr& ctxt, Operand& v) {
  auto svlm_lang_ptr = (*ctxt)["svlm_lang"].get_svlm_ptr();
  auto &frame = svlm_lang_ptr->get_current_frame();
  auto &lvars =  frame["lvars"];
  lvars.add(name(), v);

  return true;
}
//----------------------------------------------------------------------- Tuple
AstTuple::AstTuple(astnode_u_ptr u_tuple) : AstAssign(OperandType::ast_tuple_t){ 
  //cout << "AstTuple::AstTuple()\n";
  node["u_tuple"] = move(u_tuple);
}
string AstTuple::name() {return "tuple name";}

Operand AstTuple::to_str() const {
  auto tuple_ptr = node["u_tuple"].get_raw_ptr();

  s_integer i, s = tuple_ptr->size();
  Operand outstr("{");
  if(s==0) {return Operand("{}");}

  for(i=0; i<s-1; i++) {
    outstr = outstr + (*tuple_ptr)[i].to_str() + ",";
  }
  outstr = outstr + (*tuple_ptr)[i].to_str() + "}";
  return outstr;
}


Operand AstTuple::get_type() const {
  return OperandType::ast_tuple_t;
}
OperandType AstTuple::_get_type() const {
  return OperandType::ast_tuple_t;

}
Operand AstTuple::evaluate(astnode_u_ptr& ctxt) {
  cout << "AstTuple::eval\n";

  auto &u_tuple = (*this)["u_tuple"];
  //cout << "u_tuple " << u_tuple << "\n";

  auto e_tuple  = u_tuple.evaluate(ctxt);
  add(string("e_tuple"), make_unique<AstTuple>(e_tuple.clone()));
  //cout << "e_tuple " << e_tuple << "\n\n";

  return e_tuple;
}
astnode_u_ptr AstTuple::clone() const {
  cout << "AstTuple::clone()\n";
  auto &u_tuple= (*this)["u_tuple"];
  return  make_unique<AstTuple>(u_tuple.clone());
}


astnode_u_ptr AstTuple::elemptr(const Operand& v) {

  return nullptr;

}


bool AstTuple::assign(astnode_u_ptr& ctxt, Operand& v) {
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

    if(e_tuple[i] != v[i]) {
      cout << e_tuple << " != " << v << "\n";
      return false;
    }
  }
  cout << "\n\n";
  for(s_integer i=0; i < u_tuple.size(); i++) {
    if( u_tuple[i].get_u_ptr()->_get_type() == OperandType::ast_lvar_t || 
        u_tuple[i].get_u_ptr()->_get_type() == OperandType::ast_mvar_t)  {
      auto r_var =(AstAssign*) u_tuple[i].get_raw_ptr();
      Operand rv = v[i].clone();
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

