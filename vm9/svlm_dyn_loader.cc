#ifndef SVLM_DYN_LOADER_CC
#define SVLM_DYN_LOADER_CC



#ifndef SVLM_DYN_LOADER_HH
#include "svlm_dyn_loader.hh"
#endif

#include <dlfcn.h>
#include <gnu/lib-names.h> 
#include <iostream>



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
SvlmLibLoader::SvlmLibLoader() {}

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



#endif