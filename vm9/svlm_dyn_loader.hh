#include <dlfcn.h>
#include <gnu/lib-names.h> 
//#include "ast_map.hh"
#include "svlm_ast.hh"
//----------------------------------------------------------------------- SvlmBind
// if func doesn't exist in module
// look up symbols func. if it exists
// assign new 

//class SvlmBind : public AstExpr {
class SvlmBind : public SvlmAst {
public:
  SvlmBind(OperandType);
};

class SvlmKernel : public SvlmBind {
public:
  //Operand evaluate(astnode_u_ptr &) override;
  Operand to_str() const override;
  Operand get_type() const override ;
  OperandType _get_type() const override;
  void print() const override;
};

class SvlmDynLoader {
private:
  void *handle;
  string library_name;
  unordered_map<string, void*> functions;
public:
  SvlmDynLoader(const string& l);
  ~SvlmDynLoader();

  template <typename Func> 
  Func* load_function(const std::string& functionName);

  template <typename Func> 
  Func* get_function(const string& function_name);
};


class SvlmLibLoader {
private:
  unordered_map<string, unique_ptr<SvlmDynLoader>> libs;
public:
  SvlmLibLoader(){};
  ~SvlmLibLoader(){};
  bool load_lib(const string& l);
  bool load_func(const string& l, const string& f);

  template <typename Func> 
  Func* get_function(const string& l, const string& f);

};

class ModuleRegistry {
private:
  SvlmDynLoader& loader;
  unordered_map<string, void*> functions;
  string module_name;
public:
  ModuleRegistry(SvlmDynLoader&, const string &);

  template <typename Func>
  void register_function(const string& function_name, astnode_u_ptr protol_list);

  template <typename Func>
  Func* get_function(const string& function_name);
};

class MathModuleBind : public ModuleRegistry {
  void dispatch(const string &func_name);

};