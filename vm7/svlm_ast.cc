#include "svlm_ast.hh"
#include "svlm_interactive.hh"

/*
#define rl_loc "readline", "commands"

void SvlmAst::add_readline_cmds(const string&cmd) {
  root.add_branch({rl_loc, cmd}, 1l);
}
vector<string> SvlmAst::get_readline_cmds(const string& cmd) {
  auto &v = root.get_branch({rl_loc});
}
*/

astexpr_u_ptr SvlmAst::evaluate_last_line() {
  return nullptr;
}



#define MOD "modules"
void SvlmAst::add_module(const Operand& mod_name, astexpr_u_ptr clist) {
  s_integer i, s=clist->size();

  get_module_subnode(mod_name, OperandType::ast_mod_t);

  for(i=0; i < s; i++) {
    auto &nan = clist->getv(i); 
    if(nan._get_type() != OperandType::uptr_t) { continue; }

    auto &nan_vptr = nan.get_u_ptr_nc();
    auto &sub_node = get_module_subnode(mod_name,  nan_vptr->_get_type());
    if(sub_node==nil_operand) { continue; }

    auto sub_node_name = nan.getv("name")._to_str();
    sub_node.add(sub_node_name, move(nan_vptr), true);

  }
}


Operand& SvlmAst::get_module_subnode(const Operand& mod_name, const OperandType t) {
  vector<string> func_keys = {CONTEXT_UNIV, MOD, mod_name._to_str()};
  switch(t) {
  case OperandType::ast_mod_t:
    cout << "ast_mod_t!\n";
    //root.add_branch(func_keys, nil_operand);
    //return nil_operand;
    break;
  case OperandType::ast_func_t:
    func_keys.push_back("function");
    break;
  case OperandType::ast_mvar_t:
    func_keys.push_back("mvar");
    break;
  case OperandType::ast_class_t:
    func_keys.push_back("class");
    break;
  default:
    cerr << "unknown module subtype: " << Operand(t) << "! \n";
    return nil_operand;
  }
  auto &msub_node = root.get_branch(func_keys);
  if(msub_node==nil_operand) {
    cout << "creating new func_node!\n";
    root.add_branch(func_keys, make_unique<AstMap>());
    auto &nd= root.get_branch(func_keys);
    return nd;
  }
  return msub_node;
}

void SvlmAst::add_code(const Operand&n, unique_ptr<AstExpr> c ) {
  cout << "adding mod!" << MOD << "\n";
  cout << "code: " << c << " type: " << c->get_type() << "\n";
  cout << "\n";
  auto nm = make_unique<AstMap>();
  nm->add(n, move(c));
  root.add_branch({CONTEXT_UNIV, MOD}, move(nm));

  auto& l = root.get_branch({CONTEXT_UNIV, MOD, "mname"});
  cout << "after adding mod!" << MOD << n << "\n";
  l.print();
  cout << "\n";
}

void SvlmAst::run_evaluate() {
  cout << "run eval!\n";
  auto& l = root.get_branch({CONTEXT_UNIV, MOD, "Main"});
  auto &c = l.get_u_ptr();
  
  l.print();
  cout << "code list type: " <<  l.get_type() << "\n";
  cout << "size: " <<  l.size() << "\n";

  for(s_integer i=0; i<l.size();  i++){
    auto &c = l[i];
    cout << "c: " << c << "\n";
    cout << "c::getype " << c.get_type() << "\n";
    cout << "c::evaluate " << c.evaluate(c.get_u_ptr_nc()) << "\n";
  }
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
  cout << "AstBinOp:\n";
  cout << to_str();
}
Operand AstBinOp::to_str() const { 
  auto &l = (*this)["left"];
  auto &r = (*this)["right"];
  auto &o = (*this)["op"];
  return  l.to_str() + o.to_str() +  r.to_str();
}
astexpr_u_ptr AstBinOp::evaluate(astexpr_u_ptr& ast_ctxt) {
  cout << "in astbinop eval!\n";
  auto &l = (*this)["left"];
  auto &r = (*this)["right"];
  auto &o = (*this)["op"];
  cout << "opcode" << o.get_opcode() << "\n";
  cout << "str: " << l.to_str() + o.to_str() +  r.to_str() << "\n";
  cout << "num: " << l._get_number() << " " <<   r._get_number() << "\n";

  return make_unique<Operand>(l.opfunc(r, o._get_opcode()));
}


AstFunc::AstFunc(const Operand &n, astexpr_u_ptr c) {
  name = n._to_str();
  type_ = OperandType::ast_func_t;
  add(string("name"), n);
  add(string("code"), move(c));
}

astexpr_u_ptr AstFunc::evaluate(astexpr_u_ptr& ast_ctxt) {
  auto &l = map_["code"];
  cout << "in func eval!\n";
  return l.evaluate(ast_ctxt);
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