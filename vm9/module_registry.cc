
#include "svlm_lang.hh"

//----------------------------------------------------------------------- Svml Function Register
ModuleRegistry::ModuleRegistry(SvlmDynLoader &l, const string &mn) : loader(l), module_name(mn) {}

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

//----------------------------------------------------------------------- Svml Bind
SvlmBind::SvlmBind(OperandType t) :SvlmLang(t) {
}
