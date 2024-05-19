#include "svlm_lang.hh"

std::ostream& operator << (std::ostream& out, std::any& a) ;

SvlmLang::SvlmLang(std::shared_ptr<Tree> tp) { 
    context_tree = tp; 
    if(tp == nullptr) { std::cerr << "SvlmLang init: tree pointer is null!\n"; }

    tp->add_node({SVLM_AST_TREE}, std::string("program"));

    auto cc = tp->get_node({SVLM_AST_TREE});

    ast_current_context = std::make_shared<ListExprAst>(std::string("ast code here"));
    if(ast_current_context == nullptr) { std::cerr << "SvlmLang init: current_context is null!\n"; }
    cc->add_child("code", ast_current_context);
    cc->add_child("data", ast_current_context);
    cc->add_child("stack", ast_current_context);
    frame.sp=0;
    frame.fp=0;

}

void SvlmLang::fcall_args_setup(std::vector<std::any> args){
  frame.sp = svlm_stack.size(); // set current stack pointer
  svlm_frames.push_back(frame);
  //for(auto a :args) { svlm_stack.push_back(a); }
  frame.fp = svlm_stack.size();
}

//--------------------------------------------------------------------
SvlmLangContext::SvlmLangContext(SvlmLang *s) : svlm_lang(s) {
   current_context = {
    CONTEXT_UNIV, 
    "svlm_program_tree", 
    "symbols/1.0.0",
    "", // mod
    "", // mvar
    "", // mfun
    "", // fbody, function code body block
    "", // larg
    "", // lvar
    "", // label
    };
}

void SvlmLangContext::run_evaluate() {
  svlm_lang->ast_current_context->evaluate(this);
}
std::any SvlmLangContext::evaluate_last_line() {
  std::any output = svlm_lang->ast_current_context->evaluate_last_line(this);
  return output;
}

void SvlmLangContext::add_module_name(const std::string &m) {
    //std::cout << "in add module \n";
    current_context.smodule = m;
    full_symbol_t fst = current_context;  fst.smodule = m;
    std::vector<std::string> keys = move(get_sym_key(key_tok_t::smodule, fst));
    svlm_lang->context_tree->add_node(keys, std::string("module name"));
}

void SvlmLangContext::add_mvar_name(const std::string &mv) { // int n, with offset for array
  current_context.mvar = mv;
  full_symbol_t fst = current_context; fst.mvar= mv;
  std::vector<std::string> keys = move(get_sym_key(key_tok_t::mvar, fst));
  svlm_lang->context_tree->add_node(keys, std::string("value"));
}

void SvlmLangContext::add_function_name(const std::string &name) {
  full_symbol_t fst = current_context; fst.mfunction= name;
  std::vector<std::string> keys = move(get_sym_key(key_tok_t::mfunction, fst));
  svlm_lang->context_tree->add_node(keys, std::string("functions")); // name lookup addr
  current_context = fst;
}

void SvlmLangContext::add_function_params(std::vector<std::string> param_list) {
  full_symbol_t fst = current_context; 
  std::vector<std::string> keys, lvar_keys;

  for(int i=0; i< param_list.size(); i++) {
    fst.larg = param_list[i];
    keys = move(get_sym_key(key_tok_t::larg, fst)); // same as lva
    svlm_lang->context_tree->add_node(keys, i); // name lookup addr
    keys.clear();
  }
  lvar_keys = move(get_sym_key(key_tok_t::mfunction, fst));
  lvar_keys.push_back("lvars");
  auto lvar_node = svlm_lang->context_tree->get_node(lvar_keys); 
  for(int i=0; i< param_list.size(); i++) {
    fst.larg = param_list[i];
    auto larg_node =  std::make_shared<TreeNode>(param_list[i]); 
    lvar_node->add_member(larg_node);
  }
}
void SvlmLangContext::add_function_fbody(std::shared_ptr<ExprAst> code) {
  full_symbol_t fst = current_context; 
  std::vector<std::string> keys = move(get_sym_key(key_tok_t::mfunction, fst));
  keys.push_back("fbody");
  svlm_lang->context_tree->add_node(keys, code); // name lookup addr
}

void SvlmLangContext::add_function_lvars(const std::vector<std::string> lvars) {
  full_symbol_t fst = current_context; 
  std::vector<std::string> keys, lvar_keys;

  for(int i=0; i< lvars.size(); i++) {
    fst.larg = lvars[i];
    keys = move(get_sym_key(key_tok_t::larg, fst)); // same as lva
    svlm_lang->context_tree->add_node(keys, i); // name lookup addr
    keys.clear();
  }
}


std::vector<std::string> SvlmLangContext::get_sym_key(const key_tok_t ktt,  const full_symbol_t &fst) {
  std::vector<std::string> key;
  switch(ktt) {
    case  key_tok_t::smodule:
      key ={ fst.uni, fst.app, fst.api, "modules", fst.smodule};
      break;
    case  key_tok_t::mfunction:
      key ={ fst.uni, fst.app, fst.api, "modules", fst.smodule,  "functions", fst.mfunction};
      break;
    case  key_tok_t::mvar_total_count:
      key ={ fst.uni, fst.app, fst.api, "modules", "mvar_total_count"};
      break;
    case  key_tok_t::mvar:
      key ={ fst.uni, fst.app, fst.api, "modules", fst.smodule,  "mvars", fst.mvar};
      break;
    case  key_tok_t::lvar:
      //std::cout << "in getsymkey: "<<  fst.uni+ fst.app+ fst.api+ "modules"+ fst.smodule+  "functions"+ fst.mfunction+ "lvars"+ fst.lvar << "\n";
      key ={ fst.uni, fst.app, fst.api, "modules", fst.smodule,  "functions", fst.mfunction, "lvars", fst.lvar};
      break;
    case  key_tok_t::larg:
   // key ={ fst.uni, fst.app, fst.api, "modules", fst.smodule,  "functions", fst.mfunction, "largs", fst.larg};
      key ={ fst.uni, fst.app, fst.api, "modules", fst.smodule,  "functions", fst.mfunction, "lvars", fst.larg};
      break;
    case  key_tok_t::fbody:
      key ={ fst.uni, fst.app, fst.api, "modules", fst.smodule,  "functions", fst.mfunction, "fbody"};
      break;
    case  key_tok_t::label:
      key ={ fst.uni, fst.app, fst.api, "modules", fst.smodule,  "functions", fst.mfunction, "labels", fst.label};
      break;
    default: 
      std::cerr << "get_sym_key(): key not found!\n";
     return {}; 
  }
  return key; 
}

s_int_t SvlmLangContext::get_sym_addr(const key_tok_t ktt,  const full_symbol_t &fst) {

  std::string error_str;
  auto key=move(get_sym_key(ktt, fst));
  key.push_back("addr"); 
  std::shared_ptr<TreeNode> sym_node = svlm_lang->context_tree->get_node({key});

  if(sym_node != nullptr) {
    return std::any_cast<s_int_t>(sym_node->get_data());
  } 
  switch(ktt) {
    case  key_tok_t::smodule:
      error_str = fst.smodule;
      break;
    case  key_tok_t::mvar:
      error_str = fst.smodule + ":" + fst.mvar;
      break;
    case  key_tok_t::mfunction:
      error_str = fst.smodule + ":" + fst.mfunction;
      break;
    case  key_tok_t::lvar:
      error_str = fst.smodule + ":" + fst.mfunction + "." + fst.lvar;
      break;
    case  key_tok_t::larg:
      error_str = fst.smodule + ":" + fst.mfunction + "." + fst.larg;
      break;
    case  key_tok_t::label:
      error_str = fst.smodule + ":" + fst.mfunction + "." + fst.label;
      break;
    default:
      error_str = "not sure";
      break;
  }
  std::cerr << "can't resolve symbol:'" << error_str << "' got nullptr!\n";
  return -1;
}

