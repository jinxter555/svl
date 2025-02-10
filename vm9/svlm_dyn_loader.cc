#ifndef SVLM_DYN_LOADER_CC
#define SVLM_DYN_LOADER_CC


#include "svlm_dyn_loader.hh"



SvlmBind::SvlmBind(OperandType t) :AstExpr(t) {
}
//----------------------------------------------------------------------- Svml Dynamic Loader

SvlmDynLoader::SvlmDynLoader(const string library_name) 
: SvlmBind(OperandType::svlm_dyn_load_t)
, handle(nullptr) {
  handle = dlopen(library_name.c_str(), RTLD_LAZY);
  if (!handle) {
    throw std::runtime_error
    ( "Cannot open library: "
    + std::string("cannot open library: "
    + std::string(dlerror()))
    );
  }
}

SvlmDynLoader::~SvlmDynLoader() {
  if(handle) dlclose(handle);
}

template <typename Func>
Func* SvlmDynLoader::loadFunction(const std::string& function_name) {
  dlerror(); // Clear any existing error

  Func* function_ptr = (Func*)dlsym(handle, function_name.c_str());
  const char* dlsym_error = dlerror();
  if (dlsym_error) {
    std::cerr << "Cannot load symbol '" << function_name << "': " << dlsym_error << '\n';
  }

  return function_ptr;
}


//----------------------------------------------------------------------- Svml Function Register
FunctionRegistry::FunctionRegistry(SvlmDynLoader &l) : loader(l) {}

template<typename Func>
void FunctionRegistry::register_function(const string &function_name){
  functions[function_name] = (void *)loader.loadFunction<Func>(function_name);
}

template<typename Func>
Func* FunctionRegistry::get_function(const string &function_name){
  auto it = functions.find(function_name);
  if(it == functions.end()) {
    throw std::runtime_error("Function " + function_name + " not found.");
  }
  return (Func*) it->second;
}


#endif