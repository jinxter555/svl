#include <gnu/lib-names.h>

#include "svlm_lang.hh"
#include "ast_list.hh"
#include "operand_vars.hh"
#include "math.h"
#include "svlm_dyn_loader.cc"
#include <functional>




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
  svlm_lang.add_symfunc("Math", "pow", make_unique<AstList>(vec_str_t{"base", "exponent"}), sthis);

  if(!svlm_lang.dl_libs.load_func(LIBM_SO, "sin")) {
    cerr << "can't load: " << LIBM_SO << ":sin()\n";
  } else {
    func_name_lookup["sin"] =  bind(&MathModule::sin_b, this,  std::placeholders::_1);
  }

  if(!svlm_lang.dl_libs.load_func(LIBM_SO, "cos")) {
    cerr << "can't load: " << LIBM_SO << ":cos()\n";
  } else{
    func_name_lookup["cos"] =  bind(&MathModule::cos_b, this,  std::placeholders::_1);
  }

  if(!svlm_lang.dl_libs.load_func(LIBM_SO, "pow")) {
    cerr << "can't load: " << LIBM_SO << ":pow()\n";
  } else {
    func_name_lookup["pow"] =  bind(&MathModule::pow_b, this,  std::placeholders::_1);
  }
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
  auto current_function = frame["current_function"]._to_str();
  cout << "current_function: " << current_function << "\n";

  return func_name_lookup[current_function](ctxt);

/*
  if(current_function=="sin") {
    return sin_b(ctxt);
  }
  if(current_function=="cos") {
    return cos_b(ctxt);
  }
  if(current_function=="pow") {
    return pow_b(ctxt);
  }
*/

}


Operand MathModule::sin_b(astnode_u_ptr&ctxt) {
  auto svlm_lang_ptr = (*ctxt)[SVLM_LANG].get_svlm_ptr();
  auto &frame = svlm_lang_ptr->get_current_frame(ctxt);
  auto &lvars =  frame["lvars"];
  auto &value = lvars["value"];
  //return sin(value._get_float());

  auto sin_function = svlm_lang.dl_libs.get_function<double(double)>(LIBM_SO, "sin");
  if(sin_function==nullptr) {
    cerr << "sin_function is nullptr!\n";
    return nil;
  }
  return sin_function(value._get_float());
}
Operand MathModule::cos_b(astnode_u_ptr&ctxt) {
  auto svlm_lang_ptr = (*ctxt)[SVLM_LANG].get_svlm_ptr();
  auto &frame = svlm_lang_ptr->get_current_frame(ctxt);
  auto &lvars =  frame["lvars"];
  auto &value = lvars["value"];
  //return sin(value._get_float());

  auto cos_function = svlm_lang.dl_libs.get_function<double(double)>(LIBM_SO, "cos");
  if(cos_function==nullptr) {
    cerr << "cos_function is nullptr!\n";
    return nil;
  }
  return cos_function(value._get_float());
}
Operand MathModule::pow_b(astnode_u_ptr&ctxt) {
  auto svlm_lang_ptr = (*ctxt)[SVLM_LANG].get_svlm_ptr();
  auto &frame = svlm_lang_ptr->get_current_frame(ctxt);
  auto &lvars =  frame["lvars"];
  auto &base = lvars["base"];
  auto &exponent = lvars["exponent"];
  //return sin(value._get_float());

  auto pow_function = svlm_lang.dl_libs.get_function<double(double, double)>(LIBM_SO, "pow");
  if(pow_function==nullptr) {
    cerr << "pow_function is nullptr!\n";
    return nil;
  }
  return pow_function(base._get_float(), exponent._get_float());
}
//----------------------------------------------------------------------- Math Module 
//----------------------------------------------------------------------- Math Module 

//----------------------------------------------------------------------- Math Module 
