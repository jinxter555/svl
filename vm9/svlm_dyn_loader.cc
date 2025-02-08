#include "svlm_dyn_loader.hh"


SvlmBind::SvlmBind(OperandType t) :AstExpr(t) {
}

SvlmDynLoader::SvlmDynLoader(const string library_name) 
: SvlmBind(OperandType::svlm_dyn_load_t)
, handle(nullptr) {
  handle = dlopen(library_name.c_str(), RTLD_LAZY);
  if (!handle) {
    cerr << "Cannot open library: " << dlerror() << '\n';
  }
}

SvlmDynLoader::~SvlmDynLoader() {
  if(handle) dlclose(handle);
}

template <typename Func>
Func SvlmDynLoader::loadFunction(const std::string& functionName) {
  dlerror(); // Clear any existing error

  Func function = (Func)dlsym(handle, functionName.c_str());
  const char* dlsym_error = dlerror();
  if (dlsym_error) {
    std::cerr << "Cannot load symbol '" << functionName << "': " << dlsym_error << '\n';
  }

  return function;
}
