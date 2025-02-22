#include "lang.hh"
#include "svlm_lang.hh"
#include "ast_node.hh"
#include "ast_list.hh"
#include "operand.hh"

#include "svlm_interactive.hh"
#include "my_helpers.hh"
#include "operand_vars.hh"

#define SLOG_DEBUG_TRACE_FUNC
#include "scope_logger.hh"


/*
 svlvm:
  //  pid:
  //  svlm_lang:
  //  frames:
  processes:
    0:
      pid:
      svlvm:
      frames:
      processes:
    1:
      pid:
      svlvm:
      frames:
      processes:
*/
SvlmLang::SvlmLang(const OperandType&t) : Tree(t) {
  MYLOGGER(trace_function , string("SvlmLang::SvlmLang()") , __func__, SLOG_FUNC_INFO);
  //cout << "SvlmLang::SvlmLang()\n";


  // set up kernel 0 processs 
  auto process  = make_unique<AstMap>();
  (*process)[PID] = 0l;
  (*process)[FRAMES] = unique_ptr<AstNode >(make_unique<AstList>());
  (*process)[CONTROL_FLOWS] = unique_ptr<AstNode >(make_unique<AstList>());
  (*process)[CFSTATE] = ControlFlow::run;
  (*process)[SVLM_LANG] = this;

  auto processes = make_unique<AstList>();


  processes->add(move(process)); // add 

  if(! root.add(vec_str_t{CONTEXT_UNIV, PROCESSES}, move(processes), true)) {
    cerr << "can't create  {" << CONTEXT_UNIV << " " << FRAMES << "}\n";
    exit(1);
  } 

  if(! root.add(vec_str_t{CONTEXT_UNIV, SVLM_LANG},  this, true)) {
    cerr << "can't add {" << CONTEXT_UNIV << " svlm_lang  }\n";
    exit(1);
  }

  add_symfunc("Main", "eval", make_unique<AstList>(vec_str_t{"exp"}) );

  //=== create module registers



}
Operand SvlmLang::to_str() const {
  return string("SvlmLang PTR");
}
AstMap& SvlmLang::get_root() {return root; }

astnode_u_ptr& SvlmLang::get_context() {
  MYLOGGER(trace_function , string("SvlmLang::get_context()") , __func__, SLOG_FUNC_INFO);
  auto &c= root[CONTEXT_UNIV];
  return c.get_u_ptr_nc();
}
astnode_u_ptr& SvlmLang::get_processes() {
  MYLOGGER(trace_function , string("SvlmLang::get_processes()") , __func__, SLOG_FUNC_INFO);
  //MYLOGGER_MSG(trace_function, string("processes: ") + c._to_str(), SLOG_FUNC_INFO);
  //cout << "SvlmLang::get_processes()\n";
  auto &c= root[vec_str_t{CONTEXT_UNIV, PROCESSES}];
  return c.get_u_ptr_nc();
}

astnode_u_ptr& SvlmLang::get_process(s_integer i) {
  MYLOGGER(trace_function , string("SvlmLang::get_process(") + Operand(i)._to_str() + string(")") , __func__, SLOG_FUNC_INFO);
  auto pl_ptr = get_processes()->get_list_ptr_nc();
  auto &p = (*pl_ptr)[i].get_u_ptr_nc();
  return p;
}

// ctxt is proc
astnode_u_ptr& SvlmLang::get_frames(astnode_u_ptr& ctxt) {
  MYLOGGER(trace_function , string("SvlmLang::get_frames(astnode_u_ptr &ctxt)") , __func__, SLOG_FUNC_INFO+9);
  auto &f= (*ctxt)[FRAMES];
  if(f.is_nil()) {
    cerr << "SvlmLang::get_frames is nil_operand!\n";
    return nil_ast_ptr_nc;
  }
  return f.get_u_ptr_nc();
}

Operand& SvlmLang::get_current_frame(astnode_u_ptr& ctxt) {
  MYLOGGER(trace_function , string("SvlmLang::get_current_frame()")  ,__func__, SLOG_FUNC_INFO + 9)
  auto &frames = get_frames(ctxt);
  if(frames == nil_operand_ptr_nc) {
    return nil_operand_nc;
  }
  return frames->back_nc();
}

string SvlmLang::get_current_module(astnode_u_ptr& ctxt) {
  auto& f = get_frames(ctxt)->back();
  auto &m = f[CURRENT_MODULE];
  //cout << "in SvlmLang::get_current_module: " << m << "\n";
  return m._to_str();
}

ControlFlow SvlmLang::pop_control_flow(astnode_u_ptr &ctxt) {
  auto cfl= (*ctxt)[CONTROL_FLOWS].get_list_ptr_nc();
  auto &v=cfl->remove();
  return v._get_cf();
}

void SvlmLang::push_control_flow(astnode_u_ptr &ctxt) {
  auto &cfs = (*ctxt)[CFSTATE];
  auto cfl= (*ctxt)[CONTROL_FLOWS].get_list_ptr_nc();
  cfl->add(cfs._get_variant());
}

void SvlmLang::add_module(const Operand& mod_name, list_u_ptr clist_ptr) {
  MYLOGGER(trace_function , string("SvlmLang::add_module()"),__func__, SLOG_FUNC_INFO)
  MYLOGGER_MSG(trace_function, mod_name._to_str(), SLOG_FUNC_INFO);
  MYLOGGER_MSG(trace_function, string("clist: ") + clist_ptr->to_str()._to_str(), SLOG_FUNC_INFO);

  auto &clist = clist_ptr->_get_list_nc();

  s_integer i, s=clist.size();

  get_module_subnode(mod_name, OperandType::ast_mod_t); // create|get module name first by calling this function

  for(i=0; i < s; i++) {
    auto &nan = clist[i]; 

    //cout << "\nnan: " << nan << "\n";
    //cout << "nan.get_type: " << nan.get_type() << "\n";

    if(nan._get_type() != OperandType::uptr_t) { continue; }

    //auto &nan_vptr = nan.get_u_ptr();
    auto &nan_vptr = nan.get_u_ptr_nc();

    //cout << "nan_vptr.get_type: " << nan_vptr->get_type() << "\n";
    //cout << "*nan_vptr: " << *nan_vptr << "\n";

    // sub_node could be FUNC, CLASS, VAR
    auto &sub_node = get_module_subnode(mod_name,  nan_vptr->_get_type());

    //cout << "msub_node: " << msub_node << "\n";

/*
    if(msub_node.is_nil()) { 
      cout << "msub_node is_nil: " <<  msub_node << ", skip and continue\n"; 
      continue; 
    }
*/

    auto sub_node_name = (*nan_vptr)["name"]._to_str();

    //cout << "subnodename: " <<  sub_node_name<< "\n";
    //sub_node.add(sub_node_name, move(nan_vptr), true);

    //msub_node.add(sub_node_name, nan_vptr->clone(), true);
    sub_node.add(sub_node_name, move(nan_vptr), true);
  }
  //cout << "\n\n";
}


Operand& SvlmLang::get_module_subnode(const Operand& mod_name, const OperandType t) {
  MYLOGGER(trace_function , string("SvlmLang::get_module_subnode()") ,__func__, SLOG_FUNC_INFO);
  MYLOGGER_MSG(trace_function, mod_name._to_str() + string(":") + Operand(t)._to_str(), SLOG_FUNC_INFO);

 // cout << "SvlmLang::get_module_subnode, type" <<  Operand(t) <<"\n";

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
  case OperandType::ast_symfunc_t:
    keys.push_back("symfunc");
    break;
  default:
    cerr << "unknown module subtype: " << Operand(t) << "! \n";
    return nil_operand_nc;
  }


  //cout << "msub_node=root[keys]: "; for(auto k: keys) { std::cout << k << ","; } std::cout << "\n";

  auto &msub_node = root[keys];

  // ex, if key mvar, create it if it's not found==nil, else return already
  // found. so that we won't overwrite the existing mvar varaibles in it.
  if(msub_node.is_nil()) {
    //cout << "'msub_node' is_nil: " << msub_node << ", adding\n";

    root.add(keys, make_unique<AstMap>(), true);

    auto &new_msub_node= root[keys];

    //cout << "now 'msub_node' is: " << new_msub_node << "--added\n\n";

    if(new_msub_node.is_nil()) {cout << "new msubnode is nil\n"; }
    return new_msub_node;
  }
  return msub_node;
}

void SvlmLang::add_code(const Operand& name, list_u_ptr clist) {
  MYLOGGER(trace_function , string("SvlmLang::add_code('") + name._to_str() + string("')") ,__func__, SLOG_FUNC_INFO+9)
  //cout << "add code:" << MOD << " " << n << "\n";
  auto &msub_node = get_module_subnode(name, OperandType::ast_mod_t);
  auto new_map=make_unique<AstMap>();
  new_map->add(string("code"), move(clist), true);
  msub_node.add(string("last"), move(new_map), true);

  //auto& l = root[vec_str_t{CONTEXT_UNIV, MOD, name._to_str()}];
  //l.print(); cout << "\n";
}

Operand SvlmLang::evaluate_prompt_line() {
  MYLOGGER(trace_function , "SvlmLang::evaluate_prompt_line()" , string("SvlmLang::")  + string(__func__), SLOG_FUNC_INFO);
  //cout <<"SvlmLang::evaluate_prompt_line()\n";
  auto& l = root[vec_str_t{CONTEXT_UNIV, MOD, "Prompt", "last", "code"}];
  auto Lptr = l.get_list_ptr_nc();
  //l.print(); cout << "\n";
  if(Lptr==nullptr) {
    cerr << "evaluate prompt line: prompt code is null!\n";
    return nil;
  }
  auto &ctxt = get_process(0l);
  if(ctxt==nullptr) {
    cerr << "ctxt: get_process(0l) is nullptr!\n";
    exit(1);
  }
  return Lptr->evaluate(ctxt);
}
Operand SvlmLang::evaluate_prompt_line(astnode_u_ptr &ctxt) {
  MYLOGGER(trace_function , "SvlmLang::evaluate_prompt_line(astnode_u_ptr &ctxt)" , string("SvlmLang::")  + string(__func__), SLOG_FUNC_INFO);
  //cout <<"SvlmLang::evaluate_prompt_line()\n";
  auto& l = root[vec_str_t{CONTEXT_UNIV, MOD, "Prompt", "last", "code"}];
  auto Lptr = l.get_list_ptr_nc();
  //l.print(); cout << "\n";
  if(Lptr==nullptr) {
    cerr << "evaluate prompt line: prompt code is null!\n";
    return nil;
  }
  if(ctxt==nullptr) {
    cerr << "ctxt: get_process(0l) is nullptr!\n";
    exit(1);
  }
  return Lptr->evaluate(ctxt);
}

Operand SvlmLang::eval(astnode_u_ptr &ctxt) {
  //svlm_scanner.switch_streams(&input_buffer, &std::cerr);
  //svlm_parser.parse();
  auto &frame = get_current_frame(ctxt);
  auto &lvars =  frame["lvars"];

  auto exp_str = lvars["exp"]._to_str();


  cout << "eval lvars: " <<  lvars << "\n";
  cout << "eval exp: " <<  exp_str << "\n";

  std::istringstream input_buffer(exp_str+"\n\n");
  svlm_scanner_ptr->switch_streams(&input_buffer, &std::cerr);
  svlm_parser_ptr->parse();

  return nil;
}

// got to get kernel 0 process to bootstrap everything
void SvlmLang::run_evaluate() {
  MYLOGGER(trace_function , "SvlmLang::run_evaluate()" , string("SvlmLang::")  + string(__func__), SLOG_FUNC_INFO);
  //cout << "Run eval Main::main \n";
  auto Lptr = root[vec_str_t{CONTEXT_UNIV, MOD, "Main", "function", "main", "code"}].get_list_ptr_nc();
  //root.add(vec_str_t{CONTEXT_UNIV, "svlm_lang"},  this, true);
  //auto &c = l.get_u_ptr_nc();
  auto &ctxt = get_process(0l);
  auto &frames = get_frames(ctxt);

  if(frames == nullptr) {
    cerr << "frames: ptr is nullptr!\n";
    exit(1);
  }

  auto new_frame=make_unique<AstMap>();

  new_frame->add(string("lvars"), make_unique<AstMap>(), true);
  new_frame->add(string(CURRENT_MODULE), Operand("Main"));
  frames->add(move(new_frame));
  if(Lptr == nullptr) {
    cerr << "SvlmLang::run_evaluate Lptr==nullptr\n";
    return;
  }
  Lptr->evaluate(ctxt);

/*
  for(s_integer i=0; i<l.size();  i++){
    auto &c = l[i];
    c.evaluate(c.get_u_ptr_nc());
  }
*/

}

bool SvlmLang::add_symfunc(const string& mod, const string& func_name , astnode_u_ptr pl) {
  MYLOGGER(trace_function , string("SvlmLang::add_symfunc(") + mod + string(":") + func_name + string(")"), __func__, SLOG_FUNC_INFO)
  auto &sub_node = get_module_subnode(mod, OperandType::ast_symfunc_t);

  auto new_map = make_unique<AstMap>();
  (*new_map)["proto_list"]= move(pl);

  sub_node.add(func_name, move(new_map), true);
  return true;
}

bool SvlmLang::add_symfunc(const string& mod, const string& func_name , astnode_u_ptr pl, shared_ptr<ModuleRegistry> mr ) {
  MYLOGGER(trace_function , string("SvlmLang::add_symfunc(") + mod + string(":") + func_name + string(")"), __func__, SLOG_FUNC_INFO)
  auto &sub_node = get_module_subnode(mod, OperandType::ast_symfunc_t);

  auto new_map = make_unique<AstMap>();
  (*new_map)["code"] =(astnode_s_ptr) mr;

  sub_node.add(func_name, move(new_map), true);
  return true;
}

bool SvlmLang::dyn_load(const string& l, const string& f) {
  return dl_libs.load_func(l, f);
}

template <typename Func> 
Func* SvlmLang::dyn_get_func(const string& l, const string& f) {
  return dl_libs.get_function<Func>(l, f);
}

//bool SvlmLang::bind_module(const string& mod, const string&f, ModuleRegistry *mr_ptr) {
bool SvlmLang::bind_module(shared_ptr<ModuleRegistry> mr_ptr) {
  mr_ptr->setup();
  return true;

}