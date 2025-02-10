#include <dlfcn.h>
#include <gnu/lib-names.h> 
#include "ast_map.hh"
//----------------------------------------------------------------------- SvlmBind
// if func doesn't exist in module
// look up symbols func. if it exists
// assign new 

class SvlmBind : public AstExpr {
public:
  SvlmBind(OperandType);
};

class SvlmKernel : SvlmBind {
public:
  Operand evaluate(astnode_u_ptr &) override;
  Operand to_str() const override;
  Operand get_type() const override ;
  OperandType _get_type() const override;
  void print() const override;
};

class SvlmDynLoader: SvlmBind {
private:
  void *handle;
public:
  SvlmDynLoader(const string library_name);
  ~SvlmDynLoader();

  template <typename Func>
  Func* loadFunction(const std::string& functionName);

};

class FunctionRegistry {
private:
  SvlmDynLoader& loader;
  unordered_map<string, void*> functions;
public:
  FunctionRegistry(SvlmDynLoader&);

  template <typename Func>
  void register_function(const string& function_name);

  template <typename Func>
  Func* get_function(const string& function_name);
};