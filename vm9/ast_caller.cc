#include "lang.hh"
#include "ast.hh"

#include "svlm_lang.hh"
#include "my_helpers.hh"
#include "operand_vars.hh"
#include "svlm_interactive.hh"
#include <algorithm>
#include <numeric>

#define SLOG_DEBUG_TRACE_FUNC
#include "scope_logger.hh"

//----------------------------------------------------------------------- AstCaller
AstCaller::AstCaller(const Operand& callee, astnode_u_ptr arg_list) 
: AstExpr(OperandType::ast_caller_t)
{
  MYLOGGER(trace_function , "AstCaller::AstCaller()" , __func__, SLOG_FUNC_INFO);
  MYLOGGER_MSG(trace_function, string("arg_list: ") + arg_list->to_str()._to_str(), SLOG_FUNC_INFO+1)

  auto modfunc = split_string(callee._to_str(), ".");
  int s=modfunc.size();
  //cout << "modfunc size" << modfunc.size() << "\n";
  if(modfunc.size() > 1) {
    node["callee_func"]=modfunc[s-1];
    modfunc.pop_back();
    node["callee_mod"]= concat_vector_string(modfunc, ".");
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
  return frames->remove();
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

  auto keys_module = svlm_lang_ptr->get_module_keys(module_name);

 // cout << "keys_module: " << keys_module << "\n";
/*
  vector<string> keys_func = {CONTEXT_UNIV, MOD, module_name,  "function", callee_func._to_str()};
  vector<string> keys_code = {CONTEXT_UNIV, MOD, module_name,  "function", callee_func._to_str(), "code"};
  vector<string> keys_proto = {CONTEXT_UNIV, MOD, module_name,  "function", callee_func._to_str(), "proto_list"};
  vector<string> keys_proto_by_syms = {CONTEXT_UNIV, MOD, module_name,  "symfunc", callee_func._to_str(), "proto_list"};
  vector<string> keys_code_by_syms = {CONTEXT_UNIV, MOD, module_name,  "symfunc", callee_func._to_str(), "code"};
*/

  vec_str_t keys_func=keys_module;

  keys_func.insert(keys_func.end(), {"function", callee_func._to_str().c_str()});

  vector<string> keys_code = keys_func; 
  keys_code.push_back("code");

  vector<string> keys_proto = keys_func;
  keys_proto.push_back("proto_list");

  vector<string> keys_symfunc=keys_module;
  keys_symfunc.insert(keys_symfunc.end(), {"symfunc", callee_func._to_str().c_str()});

  vector<string> keys_proto_by_syms = keys_symfunc;
  keys_proto_by_syms.push_back("proto_list");

  vector<string> keys_code_by_syms =  keys_symfunc;
  keys_code_by_syms.push_back("code");

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
    auto result = code_by_syms.evaluate(ctxt);
    remove_frame(ctxt);

    return result;

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
  remove_frame(ctxt);


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

//----------------------------------------------------------------------- AstCallerLvar
AstCallerLvar::AstCallerLvar(const Operand&callee, astnode_u_ptr arg_list) : AstExpr(OperandType::ast_caller_lvar_t) {
  auto objfunc = split_string(callee._to_str(), ".");
  node["obj_var_name"] = objfunc[0];
  node["obj_var_func"] = objfunc[1];
  node["arg_list"] = move(arg_list);
  node["object"] = nil;
}

Operand AstCallerLvar::to_str() const {
  return "Object member: " + node["obj_var_name"]._to_str() + node["obj_var_func"]._to_str();

}
Operand AstCallerLvar::get_type() const {
  return OperandType::ast_caller_lvar_t;
}

OperandType AstCallerLvar::_get_type() const {
  return OperandType::ast_caller_lvar_t;
}

void AstCallerLvar::print() const {
  cout << to_str();
}
string AstCallerLvar::obj_var_name() const {
  return node["obj_var_name"]._to_str();
}
string AstCallerLvar::obj_var_func() const {
  return node["obj_var_func"]._to_str();
}

Operand AstCallerLvar::evaluate(astnode_u_ptr &ctxt) {
  auto svlm_lang_ptr = (*ctxt)[SVLM_LANG].get_svlm_ptr();
  if(svlm_lang_ptr==nullptr) {
    cerr << "In AstMvar::Assign svlmlang is null!\n";
    return Operand();
  }
  auto &frame = svlm_lang_ptr->get_current_frame(ctxt);
  auto &lvars =  frame["lvars"];
  auto var_name = obj_var_name();
  auto var_func = obj_var_func();
  auto &object = lvars[var_name];
  if(object.is_nil()) {
    cerr << "variable : " << var_name << " does not exist!\n";
    return nil;
  }
  auto &class_ptr = object["class_ptr"];

/*
  cout << "var_name: " << var_name<< "\n";
  cout << "var_func: " << var_func<< "\n";
  cout << "variable: " << variable << "\n";
*/
//  cout << "class_ptr[members]: " << class_ptr["members"] << "\n";
 // vec_str_t code_keys = {"members", var_func, "code"};
 // auto &code = class_ptr[code_keys];

  auto &members = class_ptr["members"];
  auto &func = members[var_func];
  auto &code = func["code"];
  node["proto_list"] = func["proto_list"].get_raw_ptr();
  //node["proto_list"] = func["proto_list"].clone();

  if(code.is_nil()) { cerr << "class.code is nil!\n"; }
  add_frame(ctxt, object);
  auto result = code.evaluate(ctxt);
  remove_frame(ctxt);
  return result;
}

//Operand& AstCallerObject::add_frame(astnode_u_ptr& ctxt) { }
Operand& AstCallerLvar::add_frame(astnode_u_ptr &ctxt, Operand &object) { 
  MYLOGGER(trace_function , "AstCallerLvar::add_frame(astnode_u_ptr& ctxt)" , __func__, SLOG_FUNC_INFO);
  MYLOGGER_MSG(trace_function, string("ctxt: ") + AstPtr2Str(ctxt), SLOG_FUNC_INFO+1)

  // use current module if call


  //auto svlm_lang = ctxt->root["svlm_lang"]; //auto svlm_lang_ptr = ctxt->root["svlm_lang"].get_svlm_ptr();

  auto svlm_lang_ptr = (*ctxt)[SVLM_LANG].get_svlm_ptr();
  auto &frames = svlm_lang_ptr->get_frames(ctxt);
  auto &current_frame = svlm_lang_ptr->get_current_frame(ctxt);

  auto new_frame = make_unique<AstMap>(); // nm, new frame here
  auto lvars = make_unique<AstMap>();
  new_frame->add("current_function", node["obj_var_func"], true);
  new_frame->add(CURRENT_MODULE,   current_frame[CURRENT_MODULE], true);
  new_frame->add("ovars", object["ovars"], true);

  auto &arg_list = node["arg_list"];

  // proto list needs to be implemented
  auto &proto_list = node["proto_list"];

  cout << "AstCallerLvar add_frames(), node: " <<  node<< "\n"; //cout << "proto_list: " <<  proto_list << "\n\n";
  cout << "AstCallerLvar add_frames(), proto_list: " <<  proto_list << "\n"; //cout << "proto_list: " <<  proto_list << "\n\n";
  cout << "AstCallerLvar add_frames(), arg_list: " <<  arg_list << "\n"; //cout << "proto_list: " <<  proto_list << "\n\n";

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

Operand& AstCallerLvar::remove_frame(astnode_u_ptr &ctxt) { 
  auto &svlm_lang = (*ctxt)[SVLM_LANG];
  auto ptr = svlm_lang.get_svlm_ptr();
  auto &frames = ptr->get_frames(ctxt);
  return frames->remove();
}


//----------------------------------------------------------------------- AstCallerMvar
AstCallerMvar::AstCallerMvar(const Operand&callee, astnode_u_ptr arg_list) : AstExpr(OperandType::ast_caller_mvar_t) {
  auto objfunc = split_string(callee._to_str(), ".");
  node["obj_var_name"] = objfunc[0];
  node["obj_var_func"] = objfunc[1];
  node["arg_list"] = move(arg_list);
}

Operand AstCallerMvar::to_str() const {
  return "Object member: " + node["obj_var_name"]._to_str() + node["obj_var_func"]._to_str();

}
Operand AstCallerMvar::get_type() const {
  return OperandType::ast_caller_mvar_t;
}

OperandType AstCallerMvar::_get_type() const {
  return OperandType::ast_caller_mvar_t;
}

void AstCallerMvar::print() const {
  cout << to_str();
}
string AstCallerMvar::obj_var_name() const {
  return node["obj_var_name"]._to_str();
}
string AstCallerMvar::obj_var_func() const {
  return node["obj_var_func"]._to_str();
}

Operand AstCallerMvar::evaluate(astnode_u_ptr &ctxt) {
  auto svlm_lang_ptr = (*ctxt)[SVLM_LANG].get_svlm_ptr();
  if(svlm_lang_ptr==nullptr) {
    cerr << "In AstMvar::Assign svlmlang is null!\n";
    return Operand();
  }
  auto &frame = svlm_lang_ptr->get_current_frame(ctxt);

  Operand mod_name_operand;

  auto &mod_name = (*this)["mod_name"];
  mod_name_operand = mod_name.to_str();

  if(mod_name == nil_operand)  {
    mod_name_operand  = svlm_lang_ptr->get_current_module(ctxt);
    add(string("mod_name"), mod_name_operand);
  }

  auto var_name = obj_var_name();
  auto var_func = obj_var_func();
  auto &sub_node = svlm_lang_ptr->get_module_subnode(mod_name_operand,  OperandType::ast_mvar_t);

  auto &object = sub_node[var_name];
  if(object.is_nil()) {
    cerr << "variable : " << var_name << " does not exist!\n";
    return nil;
  }
  auto &class_ptr = object["class_ptr"];

/*
  cout << "var_name: " << var_name<< "\n";
  cout << "var_func: " << var_func<< "\n";
  cout << "variable: " << variable << "\n";
*/
//  cout << "class_ptr[members]: " << class_ptr["members"] << "\n";
 // vec_str_t code_keys = {"members", var_func, "code"};
 // auto &code = class_ptr[code_keys];

  auto &members = class_ptr["members"];
  auto &func = members[var_func];
  auto &code = func["code"];
  node["proto_list"] = func["proto_list"].get_raw_ptr();
  if(code.is_nil()) { cerr << "class.code is nil!\n"; }
  add_frame(ctxt, object);
  auto result = code.evaluate(ctxt);
  remove_frame(ctxt);
  return result;
}

//Operand& AstCallerObject::add_frame(astnode_u_ptr& ctxt) { }
Operand& AstCallerMvar::add_frame(astnode_u_ptr &ctxt, Operand &object) { 
  MYLOGGER(trace_function , "AstCallerLvar::add_frame(astnode_u_ptr& ctxt)" , __func__, SLOG_FUNC_INFO);
  MYLOGGER_MSG(trace_function, string("ctxt: ") + AstPtr2Str(ctxt), SLOG_FUNC_INFO+1)

  // use current module if call


  //auto svlm_lang = ctxt->root["svlm_lang"]; //auto svlm_lang_ptr = ctxt->root["svlm_lang"].get_svlm_ptr();

  auto svlm_lang_ptr = (*ctxt)[SVLM_LANG].get_svlm_ptr();
  auto &frames = svlm_lang_ptr->get_frames(ctxt);
  auto &current_frame = svlm_lang_ptr->get_current_frame(ctxt);

  auto new_frame = make_unique<AstMap>(); // nm, new frame here
  auto lvars = make_unique<AstMap>();
  auto ovars = object["ovars"].to_shared();
  new_frame->add("current_function", node["obj_var_func"], true);
  new_frame->add(CURRENT_MODULE,   current_frame[CURRENT_MODULE], true);
  //new_frame->add("ovars", object["ovars"], true);
  new_frame->add(string("ovars"), ovars, true);

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


Operand& AstCallerMvar::remove_frame(astnode_u_ptr &ctxt) { 
  auto &svlm_lang = (*ctxt)[SVLM_LANG];
  auto ptr = svlm_lang.get_svlm_ptr();
  auto &frames = ptr->get_frames(ctxt);
  return frames->remove();
}

//----------------------------------------------------------------------- AstCallerOvar
AstCallerOvar::AstCallerOvar(const Operand&callee, astnode_u_ptr arg_list) : AstExpr(OperandType::ast_caller_ovar_t) {
  auto objfunc = split_string(callee._to_str(), ".");
  node["obj_var_name"] = objfunc[0];
  node["obj_var_func"] = objfunc[1];
  node["arg_list"] = move(arg_list);
  node["object"] = nil;
}

Operand AstCallerOvar::to_str() const {
  return "Object member: " + node["obj_var_name"]._to_str() + node["obj_var_func"]._to_str();

}
Operand AstCallerOvar::get_type() const {
  return OperandType::ast_caller_ovar_t;
}

OperandType AstCallerOvar::_get_type() const {
  return OperandType::ast_caller_ovar_t;
}

void AstCallerOvar::print() const {
  cout << to_str();
}
string AstCallerOvar::obj_var_name() const {
  return node["obj_var_name"]._to_str();
}
string AstCallerOvar::obj_var_func() const {
  return node["obj_var_func"]._to_str();
}

Operand AstCallerOvar::evaluate(astnode_u_ptr &ctxt) {
  auto svlm_lang_ptr = (*ctxt)[SVLM_LANG].get_svlm_ptr();
  if(svlm_lang_ptr==nullptr) {
    cerr << "In AstMvar::Assign svlmlang is null!\n";
    return Operand();
  }
  auto &frame = svlm_lang_ptr->get_current_frame(ctxt);
  auto &lvars =  frame["lvars"];
  auto &ovars =  frame["ovars"];
  auto var_name = obj_var_name();
  auto var_func = obj_var_func();
  auto &object = ovars[var_name];
  if(object.is_nil()) {
    cerr << "variable : " << var_name << " does not exist!\n";
    return nil;
  }
  auto &class_ptr = object["class_ptr"];

/*
  cout << "var_name: " << var_name<< "\n";
  cout << "var_func: " << var_func<< "\n";
  cout << "variable: " << variable << "\n";
*/
//  cout << "class_ptr[members]: " << class_ptr["members"] << "\n";
 // vec_str_t code_keys = {"members", var_func, "code"};
 // auto &code = class_ptr[code_keys];

  auto &members = class_ptr["members"];
  auto &func = members[var_func];
  auto &code = func["code"];
  node["proto_list"] = func["proto_list"].get_raw_ptr();
  //node["proto_list"] = func["proto_list"].clone();

  if(code.is_nil()) { cerr << "class.code is nil!\n"; }
  add_frame(ctxt, object);
  auto result = code.evaluate(ctxt);
  remove_frame(ctxt);
  return result;
}

//Operand& AstCallerObject::add_frame(astnode_u_ptr& ctxt) { }
Operand& AstCallerOvar::add_frame(astnode_u_ptr &ctxt, Operand &object) { 
  MYLOGGER(trace_function , "AstCallerLvar::add_frame(astnode_u_ptr& ctxt)" , __func__, SLOG_FUNC_INFO);
  MYLOGGER_MSG(trace_function, string("ctxt: ") + AstPtr2Str(ctxt), SLOG_FUNC_INFO+1)

  // use current module if call


  //auto svlm_lang = ctxt->root["svlm_lang"]; //auto svlm_lang_ptr = ctxt->root["svlm_lang"].get_svlm_ptr();

  auto svlm_lang_ptr = (*ctxt)[SVLM_LANG].get_svlm_ptr();
  auto &frames = svlm_lang_ptr->get_frames(ctxt);
  auto &current_frame = svlm_lang_ptr->get_current_frame(ctxt);

  auto new_frame = make_unique<AstMap>(); // nm, new frame here
  auto lvars = make_unique<AstMap>();
  new_frame->add("current_function", node["obj_var_func"], true);
  new_frame->add(CURRENT_MODULE,   current_frame[CURRENT_MODULE], true);
  new_frame->add("ovars", object["ovars"], true);

  auto &arg_list = node["arg_list"];

  // proto list needs to be implemented
  auto &proto_list = node["proto_list"];

  cout << "AstCallerLvar add_frames(), node: " <<  node<< "\n"; //cout << "proto_list: " <<  proto_list << "\n\n";
  cout << "AstCallerLvar add_frames(), proto_list: " <<  proto_list << "\n"; //cout << "proto_list: " <<  proto_list << "\n\n";
  cout << "AstCallerLvar add_frames(), arg_list: " <<  arg_list << "\n"; //cout << "proto_list: " <<  proto_list << "\n\n";

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

Operand& AstCallerOvar::remove_frame(astnode_u_ptr &ctxt) { 
  auto &svlm_lang = (*ctxt)[SVLM_LANG];
  auto ptr = svlm_lang.get_svlm_ptr();
  auto &frames = ptr->get_frames(ctxt);
  return frames->remove();
}