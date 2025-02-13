#ifndef SVLM_DYN_LOADER_CC
#define SVLM_DYN_LOADER_CC


#include "svlm_dyn_loader.hh"



SvlmBind::SvlmBind(OperandType t) :SvlmAst(t) {
}
//----------------------------------------------------------------------- Svml Dynamic Loader

SvlmDynLoader::SvlmDynLoader(const string& l) : library_name(l), handle(nullptr) {
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
Func* SvlmDynLoader::load_function(const string& function_name) {
  dlerror(); // Clear any existing error

  Func* function_ptr = (Func*)dlsym(handle, function_name.c_str());
  const char* dlsym_error = dlerror();
  if (dlsym_error) {
    std::cerr << "Cannot load symbol '" << function_name << "': " << dlsym_error << '\n';
    return nullptr;
  }
  functions[function_name] =(void*) function_ptr;

  return function_ptr;
}

template <typename Func>
Func* SvlmDynLoader::get_function(const string& function_name) {
  auto function_ptr = functions[function_name];
  if(function_ptr) {
    return (Func*) function_ptr;
  }
  return load_function<Func>(function_name);
}

//----------------------------------------------------------------------- Svml Library Loader
bool SvlmLibLoader::load_lib(const string& l) {
  libs[l] = make_unique<SvlmDynLoader>(l);
  if(libs[l]) return true;
  return false;
}

bool SvlmLibLoader::load_func(const string& l, const string& f) {
  if(libs[l]) {
    libs[l]->load_function<void*>(f);
    return true;
  }
  if(load_lib(l)) {
    libs[l]->load_function<void*>(f);
    return true;
  }
  return false;
}
template <typename Func>
Func* SvlmLibLoader::get_function(const string &l, const string& f) {
  if(!libs[l]) return nullptr;
  auto &lib = libs[l];
  return lib->get_function<Func>(f);
}


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


#endif