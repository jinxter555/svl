#include "lang.hh"
#include "ast.hh"

#include "svlm_lang.hh"
#include "my_helpers.hh"
#include "operand_vars.hh"
#include "svlm_interactive.hh"

#define SLOG_DEBUG_TRACE_FUNC
#include "scope_logger.hh"


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
astnode_u_ptr AstBinOp::clone() const {
    cout << "AstBinOp::clone()\n";
    return AstMap::clone();
};


Operand AstBinOp::evaluate(astnode_u_ptr& ctxt) {
  MYLOGGER(trace_function , "AstBinOp::evaluate(astnode_u_ptr& ctxt)" , __func__, SLOG_FUNC_INFO);
  //cout << "AstBinOp::evaluate(astnode_u_ptr&)\n";


  //auto &l = (*this)["left"];
  auto &l = node["left"];
  auto &r = node["right"];
  auto opcode_str = node["op"]._to_str();
  auto &op = node["op"];
  auto opcode = node["op"]._get_opcode();

  MYLOGGER_MSG(trace_function, string("AstBinOp::") + string(__func__) + string(" ") +  l._to_str()  + opcode_str + r._to_str(), SLOG_FUNC_INFO);

/*
  cout << "l: " << l << "\n";
  cout << "l.type: " << l.get_type() << "\n";
  cout << "op.gettype(): " << op.get_type()<< "\n";
  cout << "opcode_str: " << opcode_str << "\n";
  cout << "r.type: " << r.get_type() << "\n";
  cout << "r: " << r << "\n\n";
*/

  auto r_v = r.evaluate(ctxt);
  auto r_v_rptr = r_v._vrptr();



  if(opcode == AstOpCode::assign) {
    AstAssign* variable =(AstAssign*) l.get_raw_ptr();
    //cout << "r_vptr get_type: " <<  r_vptr->get_type() << "\n";

    switch(r_v_rptr->_get_type()) {
      case OperandType::list_t :
      case OperandType::tuple_t:
      case OperandType::map_t: {
        cout << "assigning list_t || map_t || tuple_t !\n ";
        if(r_v.be_shared()) { 
          variable->assign(ctxt, r_v); 
          return r_v; 
        }
        cerr << "can't convert r_v  be_shared()!\n"; 
        break;}

      case OperandType::ptr_t: 
      case OperandType::uptr_t: 
      case OperandType::sptr_t: { 
        cout << "assigning ptr!\n ";
        if(r_v.be_shared()) {
          variable->assign(ctxt, r_v);
          return r_v; }
        cout << "can't convert to be shared ptr!\n ";
        break;}

      default: {
        cout << "assigning regular var!\n";
        variable->assign(ctxt, r_v);
        return r_v; }
    }

  }

  auto l_v = l.evaluate(ctxt);

  //l_v.to_shared(); r_v.to_shared();

  auto result = l_v.opfunc(r_v, opcode);
  return result;

}


//----------------------------------------------------------------------- AstFunc
AstFunc::AstFunc(const Operand &n, astnode_u_ptr pl,  astnode_u_ptr code_ptr) 
: AstExpr(OperandType::ast_func_t) {
  MYLOGGER(trace_function , string("AstFunc::AstFunc(") + n._to_str()+ string(")") , __func__, SLOG_FUNC_INFO);
  MYLOGGER_MSG(trace_function, string("proto_list: ") + AstPtr2Str(pl), SLOG_FUNC_INFO);
  MYLOGGER_MSG(trace_function, string("clist: ") + AstPtr2Str(code_ptr), SLOG_FUNC_INFO);

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
  //return AstMap::to_str();
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
  MYLOGGER(trace_function , "AstCaller::AstCaller()" , __func__, SLOG_FUNC_INFO);
  MYLOGGER_MSG(trace_function, string("arg_list: ") + arg_list->to_str()._to_str(), SLOG_FUNC_INFO+1)

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
  MYLOGGER(trace_function , "AstCaller::add_frame(astnode_u_ptr& ctxt)" , __func__, SLOG_FUNC_INFO);
  MYLOGGER_MSG(trace_function, string("ctxt: ") + AstPtr2Str(ctxt), SLOG_FUNC_INFO+1)

  // use current module if call


  //auto svlm_lang = ctxt->root["svlm_lang"]; //auto svlm_lang_ptr = ctxt->root["svlm_lang"].get_svlm_ptr();

  auto svlm_lang_ptr = (*ctxt)[SVLM_LANG].get_svlm_ptr();
  auto &frames = svlm_lang_ptr->get_frames(ctxt);

  auto new_frame = make_unique<AstMap>(); // nm, new frame here
  auto lvars = make_unique<AstMap>();
  new_frame->add("current_function", node["callee_func"], true);
  new_frame->add(CURRENT_MODULE,   node["callee_mod"], true);
  //new_frame->add("current_flow", ControlFlow::run, true);

  auto &arg_list = node["arg_list"];
  auto &proto_list = node["proto_list"];

  //cout << "arg_list: " <<  arg_list << "\n"; //cout << "proto_list: " <<  proto_list << "\n\n";

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

  new_frame->add(string("lvars"), move(lvars), true);
  frames->add(move(new_frame));

  return frames->back_nc();
}
Operand& AstCaller::remove_frame(astnode_u_ptr &ctxt) { 
  auto &svlm_lang = (*ctxt)[SVLM_LANG];
  auto ptr = svlm_lang.get_svlm_ptr();
  auto &frames = ptr->get_frames(ctxt);
  auto &f = frames->back();
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
  MYLOGGER(trace_function , "AstCaller::evaluate(astnode_u_ptr& ctxt)" , __func__, SLOG_FUNC_INFO);
  MYLOGGER_MSG(trace_function, string("ctxt: ") + AstPtr2Str(ctxt), SLOG_FUNC_INFO+1)

  string module_name;
  auto svlm_lang_ptr = (*ctxt)[SVLM_LANG].get_svlm_ptr();

  if(svlm_lang_ptr==nullptr) { throw std::runtime_error("AstCaller::evaluate() svlm_lang_ptr is nullptr"); }

  auto &root = svlm_lang_ptr->get_root();
  auto &callee_mod = node["callee_mod"];
  auto &callee_func = node["callee_func"];


  // if(callee_mod._get_type() == OperandType::nil_t)  {
  if(callee_mod.is_nil()){
    module_name = svlm_lang_ptr->get_current_module(ctxt);
  } else {
    module_name = callee_mod._to_str();
  }


  MYLOGGER_MSG(trace_function, module_name + ":" + callee_func._to_str(), SLOG_FUNC_INFO+1);


  //vector<string> keys_func = {CONTEXT_UNIV, MOD, module_name,  "function", callee_func._to_str()};
  vector<string> keys_code = {CONTEXT_UNIV, MOD, module_name,  "function", callee_func._to_str(), "code"};
  vector<string> keys_proto = {CONTEXT_UNIV, MOD, module_name,  "function", callee_func._to_str(), "proto_list"};
  vector<string> keys_proto_by_syms = {CONTEXT_UNIV, MOD, module_name,  "symfunc", callee_func._to_str(), "proto_list"};
  vector<string> keys_code_by_syms = {CONTEXT_UNIV, MOD, module_name,  "symfunc", callee_func._to_str(), "code"};

  //cout << "keys_code: " ; for(auto k : keys_code) { cout << k << ", "; } cout << "\n";
  auto &code = root[keys_code];
  auto &proto_list = root[keys_proto];


  // might need to check the symbol table from here
  // look up mod:func in symbols
  if(code.is_nil()) {
    auto &code_by_syms = root[keys_code_by_syms];

    if(code_by_syms.is_nil()){
      cerr << "function " <<  callee_func << " not found and doesn't have code!\n";
      return nil;
    }
    // call symfunc using module registry function 
    auto &proto_list = root[keys_proto_by_syms];
    node.add("proto_list", proto_list, true); // this is for function ?
    add_frame(ctxt);
    return code_by_syms.evaluate(ctxt);

  } 

  
  //cout << "AstCaller::evaluate: proto_list: " <<  module_name + string(":") + callee_func._to_str() << ":  " <<  proto_list  << "\n";
  //cout << "AstCaller::evaluate:: code: " <<  code << "\n";

  node.add("proto_list", proto_list, true); // this is for function ?
  node.add("callee_mod", Operand(module_name), true);

  MYLOGGER_MSG(trace_function, string("proto_list: ") + proto_list._to_str(), SLOG_FUNC_INFO+1);

  svlm_lang_ptr->push_control_flow(ctxt);
  add_frame(ctxt);

  Operand result;
  result  = code.evaluate(ctxt);


  ControlFlow cfstate;
  cfstate = (*ctxt)[CFSTATE]._get_cf(); // current control flow state

  if(cfstate ==ControlFlow::ast_return_val) {
    auto &v = (*ctxt)[RET_VAL];
    cfstate =  svlm_lang_ptr->pop_control_flow(ctxt); // restore previous control flow state
    (*ctxt)[CFSTATE] = cfstate;
    return v._get_variant();
  }

  cfstate =  svlm_lang_ptr->pop_control_flow(ctxt); // restore previous control flow state
  (*ctxt)[CFSTATE] = cfstate;

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
//----------------------------------------------------------------------- AstMvar

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

//----------------------------------------------------------------------- 
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
  //cout << "AstMvar::clone()\n";
  return AstMap::clone();
};


Operand AstMvar::get_type() const { 
  //cout << "AstMvar::get_type()\n";
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
  auto svlm_lang_ptr = (*ctxt)[SVLM_LANG].get_svlm_ptr();

  if(svlm_lang_ptr==nullptr) {
    cerr << "In AstMvar::Assign svlmlang is null!\n";
    return Operand();
  }

  auto &mod_name = (*this)["mod_name"];
  mod_name_operand = mod_name.to_str();

  if(mod_name == nil_operand)  {
    mod_name_operand  = svlm_lang_ptr->get_current_module(ctxt);
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
      //cout << "index i: " << index_i << "\n";
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
    return nil;
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
  MYLOGGER_MSG(trace_function, name() + string(" = ") + v._to_str(), SLOG_FUNC_INFO);

  Operand mod_name_operand;

  auto svlm_lang_ptr = (*ctxt)[SVLM_LANG].get_svlm_ptr();
  if(svlm_lang_ptr==nullptr) {
    cerr << "In AstMvar::Assign svlmlang is null!\n";
    return false;
  }

  auto &mod_name = (*this)["mod_name"];
  mod_name_operand = mod_name.to_str();


  if(mod_name.is_nil() )  {
     mod_name_operand = svlm_lang_ptr->get_current_module(ctxt);
    add(string("mod_name"), mod_name_operand);
  }


  auto var_name = name();

  auto &sub_node = svlm_lang_ptr->get_module_subnode(mod_name_operand,  OperandType::ast_mvar_t);


  //cout << "mvar assign\n";
  //cout << "v.get_type():" << v.get_type() << "\n";


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

  //if(v._get_type() == OperandType::uptr_t) v.to_shared();

  //cout << "v.type(): " << v.get_type() << "\n";

  sub_node.add(var_name, v, true);
  //sub_node[var_name]= v.clone();

  MYLOGGER_MSG(trace_function, "sub_node.add() after", SLOG_FUNC_INFO);
  return true;

}


//----------------------------------------------------------------------- AstLvar
AstLvar::AstLvar(const string &name) : AstAssign(OperandType::ast_lvar_t) { 
  //add(string("var_name"), Operand(name));
  node["var_name"]= name;
  scale_ = OperandType::scalar_t;
}

string AstLvar::name() { return node["var_name"]._to_str(); }
Operand AstLvar::get_type() const { return OperandType::ast_lvar_t;}
OperandType AstLvar::_get_type() const { return OperandType::ast_lvar_t;}
Operand AstLvar::to_str() const { return node["var_name"].to_str(); }
void AstLvar::print() const { cout << to_str(); }

AstLvar::AstLvar(const string &name, astnode_u_ptr idx_key) : AstAssign(OperandType::ast_lvar_t) { 
  node["var_name"]= name;
  node["idx_key"]= move(idx_key);
  scale_ = OperandType::array_t;
}

Operand AstLvar::evaluate(astnode_u_ptr& ctxt) {
  //cout << "AstLvar::evalaute\n";
  auto svlm_lang_ptr = (*ctxt)[SVLM_LANG].get_svlm_ptr();
  if(svlm_lang_ptr==nullptr) {
    cerr << "In AstMvar::Assign svlmlang is null!\n";
    return Operand();
  }
  auto &frame = svlm_lang_ptr->get_current_frame(ctxt);
  auto &lvars =  frame["lvars"];
  auto var_name = name();
  auto &l_var = lvars[name()];
  if(scale_ == OperandType::array_t){
    //auto &result = sub_node.getv(var_name);
    auto index_i = get_index_i(ctxt);
    if(index_i >= 0) {
      return l_var[index_i]._get_variant();
    }
    auto index_s = get_index_s(ctxt);
    if(index_s != "" ) {
      return l_var[index_s]._get_variant();
    }
  } 
 return l_var._get_variant();
}

bool AstLvar::assign(astnode_u_ptr& ctxt, Operand& v) {
  MYLOGGER(trace_function
  , "AstLvar::assign(astnode_u_ptr& ctxt, const Operand& v)" 
  , string("AstLvar::") + string(__func__), SLOG_FUNC_INFO);
  MYLOGGER_MSG(trace_function, name() + string(" = ") + v._to_str(), SLOG_FUNC_INFO);

  auto svlm_lang_ptr = (*ctxt)[SVLM_LANG].get_svlm_ptr();
  auto &frame = svlm_lang_ptr->get_current_frame(ctxt);
  auto &lvars =  frame["lvars"];

  if(scale_ == OperandType::array_t){
    //auto &result = sub_node.getv(var_name);

    auto &l_var = lvars[name()];
    auto index_i = get_index_i(ctxt);
    if(index_i >= 0) {
      l_var[index_i] = v.clone();
      cout << "l_var: " << l_var<< "\n";
      return true;
    }
    auto index_s = get_index_s(ctxt);
    if(index_s != "" ) {
      l_var.add(index_s, v, true);
      cout << "l_var: " << l_var<< "\n";
      return true;
    }
  } else {
    lvars.add(name(), v, true);
  }
  return true;
}


//----------------------------------------------------------------------- Tuple
AstTuple::AstTuple() : AstAssign(OperandType::ast_tuple_t) {
  MYLOGGER(trace_function , "AstTuple::AstTuple()" , __func__, SLOG_FUNC_INFO); 
  node["u_tuple"] = nil;
}

AstTuple::AstTuple(astnode_u_ptr u_tuple) : AstAssign(OperandType::ast_tuple_t){ 
  MYLOGGER(trace_function , "AstTuple::AstTuple(astnode_u_ptr)" , __func__, SLOG_FUNC_INFO);
  MYLOGGER_MSG(trace_function, string("Tuple: ") + AstPtr2Str(u_tuple), SLOG_FUNC_INFO);
  //cout << "AstTuple::AstTuple()\n";
  node["u_tuple"] = move(u_tuple);
}


string AstTuple::name() {return "tuple name";}

Operand AstTuple::to_str() const {
  auto &tuple_v = node["u_tuple"];
  int i, s = tuple_v .size();

  string outstr("{");
  if(s==0) {return Operand("{}");}

  for(i=0; i<s-1; i++) {
    outstr = outstr + tuple_v[i]._to_str() + ", ";
  }
  outstr = outstr + tuple_v[i]._to_str() + "}";
  return outstr;
}


Operand AstTuple::get_type() const {
  return OperandType::ast_tuple_t;
}
OperandType AstTuple::_get_type() const {
  return OperandType::ast_tuple_t;
}

Operand AstTuple::evaluate(astnode_u_ptr& ctxt) {
  MYLOGGER(trace_function , "AstTuple::evaluate(astnode_u_ptr &ctxt)" , __func__, SLOG_FUNC_INFO);
  //cout << "AstTuple::eval\n";

  auto tuple_vptr = node["u_tuple"]._vrptr();         //cout <<"u_tuple:" <<  *tuple_vptr << "\n";
  if(tuple_vptr==nullptr) { throw std::runtime_error("AstTuple::evaluate() u_tuple is nullptr"); }

  return tuple_vptr->evaluate(ctxt); // tuple_t aka base::list_t to evaluate

}


astnode_u_ptr AstTuple::clone() const {
  MYLOGGER(trace_function , "AstTuple::clone()" , __func__, SLOG_FUNC_INFO);
  cout << "AstTuple::clone()\n";
  auto &tuple_v = node["u_tuple"];

  int i, s = tuple_v.size();
  auto new_tuple = make_unique<AstTuple>();
  for(i=0; i<s; i++)  {
    auto &e = tuple_v[i];
    new_tuple->add(e.clone()); 
  }
  return new_tuple;
}


astnode_u_ptr AstTuple::elemptr(const Operand& v) {
  return nullptr;
}


bool AstTuple::assign(astnode_u_ptr& ctxt, Operand& v) {
  MYLOGGER(trace_function , "AstTuple::assign(astnode_u_ptr &ctxt, Operand& v)" , __func__, SLOG_FUNC_INFO);
  MYLOGGER_MSG(trace_function, to_str()._to_str() +  string(" = v: ") + v._to_str(), SLOG_FUNC_INFO);

  //cout << "AstTuple::assign()\n";
  //auto &u_tuple = (*this)["u_tuple"];
  auto &u_tuple = node["u_tuple"];


  s_integer s = u_tuple.size();

  if(s != v.size()) return false;

  //for(s_integer i=0; i < u_tuple.size(); i++) {
  for(s_integer i=0; i < s; i++) {
    auto u_e_vrptr = u_tuple[i]._vrptr(); // tuple unassigned element

    if(u_e_vrptr==nullptr) throw std::runtime_error("AstTuple::assign() u_e_vrptr is nullptr");

    auto u_e_type = u_e_vrptr->_get_type();
    //cout << "v[" << i << "]: " <<  v[i] << "\n";
    //cout << "u_tuple[" << i << "]: " <<  *u_e_vrptr << "\n";
    //cout << "u_tuple[" << i << "].get_type(): " <<  u_e_vrptr->get_type() << "\n";

    if( u_e_type == OperandType::ast_lvar_t || u_e_type == OperandType::ast_mvar_t)  {
      cout << "found a var- " <<  u_e_vrptr->to_str() <<" -skipping!\n";
      continue;
    }

    if(u_tuple[i].evaluate(ctxt) != v[i].evaluate(ctxt)) {
      cerr << "tuple assign: " << u_tuple[i] << " != " << v[i] << " error\n";
      return false;
    }
  }

  //for(s_integer i=0; i < u_tuple.size(); i++) {
  for(s_integer i=0; i < s; i++) {
    auto u_e_vrptr = u_tuple[i]._vrptr(); // tuple unassigned element

    if(u_e_vrptr==nullptr) throw std::runtime_error("AstTuple::assign() u_e_vrptr is nullptr");

    auto u_e_type = u_e_vrptr->_get_type();

    if( u_e_type == OperandType::ast_lvar_t || u_e_type == OperandType::ast_mvar_t)  {
      auto r_var =(AstAssign*) u_e_vrptr;
      //cout << "r_var: " ; r_var->print(); cout << "\n";
      //Operand rv = v[i].clone();
      //r_var->assign(ctxt, v.getv(i).clone());
      //r_var->assign(ctxt, rv);
      r_var->assign(ctxt, v[i]);
    }
  }
  //cout << e_tuple << "= " << vptr << "\n";
  return true;
}
void AstTuple::print() const {
  cout << "ast_tuple: " << to_str();
}


//----------------------------------------------------------------------- Control Flow
AstFlow::AstFlow(ControlFlow cf) : AstExpr(OperandType::control_flow_t) {
  MYLOGGER(trace_function , "AstFlow::AstFlow(ControlFlow)" , __func__, SLOG_FUNC_INFO);
  node["control_flow"] = cf;
}
AstFlow::AstFlow(ControlFlow cf, astnode_u_ptr exp) : AstExpr(OperandType::control_flow_t) {
  node["control_flow"] = cf;
  node["exp"] = move(exp);
}



Operand AstFlow::to_str() const {
  auto &cf  = node["control_flow"];
  auto &exp = node["exp"] ;
  string outstr="noop";
  switch(cf._get_cf()) {
  case ControlFlow::run:
    outstr="run"; break;
  case ControlFlow::ast_break:
    outstr="run"; break;
  }
  return outstr;
}

Operand AstFlow::get_type() const { return OperandType::control_flow_t; }
OperandType AstFlow::_get_type() const { return OperandType::control_flow_t; }

void AstFlow::print() const {
  cout << "ast_tuple: " << to_str();
}

Operand AstFlow::evaluate(astnode_u_ptr &ctxt) {
  MYLOGGER(trace_function , "AstFlow::evaluate(astnode_u_ptr &ctxt)" , __func__, SLOG_FUNC_INFO);

  auto &cf = node["control_flow"];
  auto cfstate  = cf._get_cf();

  MYLOGGER_MSG(trace_function, cf._to_str(), SLOG_FUNC_INFO);

  (*ctxt)[CFSTATE] = cfstate; // set the process control flow state
  if(cfstate==ControlFlow::ast_return_val){
    auto &exp = node["exp"];
    (*ctxt)[RET_VAL] = exp.evaluate(ctxt);
    
  }
  return cfstate;
}