#include "svlm_lang.hh"
#include "ast_list.hh"
#include "operand_vars.hh"
#include "math.h"

//----------------------------------------------------------------------- Svml Bind
//----------------------------------------------------------------------- Module Registery
ModuleRegistry::ModuleRegistry(SvlmLang &sl)  
: AstExpr(OperandType::ast_bind_t)
, svlm_lang(sl) {}

/*
template<typename Func>
void ModuleRegistry::register_function(const string &function_name, astnode_u_ptr proto_list){
  functions[function_name] = (void *)loader.load_function<Func>(function_name);
  //loader.add_symfunc(module_name, function_name, move(proto_list));
}

template<typename Func>
Func* ModuleRegistry::get_function(const string &function_name){
  auto it = functions.find(function_name);
  if(it == functions.end()) {
    throw std::runtime_error("Function " + function_name + " not found.");
  }
  return (Func*) it->second;
}
*/

//----------------------------------------------------------------------- Kernel  Module 
KernelModule::KernelModule(SvlmLang&sl) : ModuleRegistry(sl) {
  module_name="Kernel";
  setup();
}
void KernelModule::setup() {
  svlm_lang.add_symfunc("Kernel", "eval", make_unique<AstList>(vec_str_t{"exp"}), sthis);
}
string KernelModule::mod_name() const {
  return module_name;
}

Operand  KernelModule::to_str() const {
  return "KernelModule";
}
Operand KernelModule::get_type() const {
  return OperandType::ast_bind_t;
}
OperandType KernelModule::_get_type() const {
  return OperandType::ast_bind_t;

}
void KernelModule::print() const {
  cout << to_str();
}
Operand KernelModule::evaluate(astnode_u_ptr &ctxt) {
  auto svlm_lang_ptr = (*ctxt)[SVLM_LANG].get_svlm_ptr();
  auto &frame = svlm_lang_ptr->get_current_frame(ctxt);

  //auto &current_function = node["current_function"];
  auto &current_function = frame["current_function"];
  cout << "current_function: " << current_function << "\n";

  if(current_function=="eval") {
    return eval(ctxt);
  }

  return nil;
}
void KernelModule::bind_sthis(shared_ptr<KernelModule> sptr) {
  sthis=shared_ptr<KernelModule>(sptr);
}
Operand KernelModule::eval(astnode_u_ptr &ctxt) {
  auto svlm_lang_ptr = (*ctxt)[SVLM_LANG].get_svlm_ptr();
  svlm_lang_ptr->eval(ctxt);
  return svlm_lang_ptr->evaluate_prompt_line(ctxt);
}

//----------------------------------------------------------------------- Math Module 


//----------------------------------------------------------------------- Math Module 
MathModule::MathModule(SvlmLang &sl) : ModuleRegistry(sl) {
  module_name="Math";
  setup();
}

string MathModule::mod_name() const {
  return module_name;
}

void MathModule::setup() {
  //if(svlm_lang_ptr==nullptr) svlm_lang_ptr = sl_ptr;
  //sthis = shared_from_this();
  svlm_lang.add_symfunc("Math", "sin", make_unique<AstList>(vec_str_t{"value"}), sthis);
  svlm_lang.add_symfunc("Math", "cos", make_unique<AstList>(vec_str_t{"value"}), sthis);
}
Operand  MathModule::to_str() const {
  return "MathModule";
}
Operand MathModule::get_type() const {
  return OperandType::ast_bind_t;
}
OperandType MathModule::_get_type() const {
  return OperandType::ast_bind_t;

}
void MathModule::print() const {
  cout << to_str();
}
void MathModule::bind_sthis(shared_ptr<MathModule> sptr) {
  sthis=shared_ptr<MathModule>(sptr);
}
//--------------------
Operand MathModule::evaluate(astnode_u_ptr &ctxt) {
  auto svlm_lang_ptr = (*ctxt)[SVLM_LANG].get_svlm_ptr();
  auto &frame = svlm_lang_ptr->get_current_frame(ctxt);

  //auto &current_function = node["current_function"];
  auto &current_function = frame["current_function"];
  cout << "current_function: " << current_function << "\n";

  if(current_function=="sin") {
    return sin_b(ctxt);
  }

  return nil;
}


Operand MathModule::sin_b(astnode_u_ptr&ctxt) {
  cout << "I am in sin_b!\n";
  auto svlm_lang_ptr = (*ctxt)[SVLM_LANG].get_svlm_ptr();
  auto &frame = svlm_lang_ptr->get_current_frame(ctxt);
  auto &lvars =  frame["lvars"];
  auto &value = lvars["value"];
  cout << "value: " << value << "\n";
  cout << "sin " << sin(value._get_float()) << "\n";
  return sin(value._get_float());


}
//----------------------------------------------------------------------- Math Module 
