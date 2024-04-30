  #include "svlm_lang.hh"

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

    ast_current_contexts.push
    ( ast_current_context
    );
  }

//--------------------------------------------------------------------
SvlmLangContext::SvlmLangContext() {
   current_context = {
    CONTEXT_UNIV, 
    "svlm_program_tree", 
    "symbols/1.0.0",
    "", // mod
    "", // mvar
    "", // mfun
    "", // larg
    "", // lvar
    "", // label
    };
}

void SvlmLangContext::add_module_name(const std::string &m) {
    std::cout << "in add module \n";
    current_context.smodule = m;
    full_symbol_t fst = current_context;  fst.smodule = m;
    std::vector<std::string> keys = move(get_sym_key(key_tok_t::smodule, fst));
    svl_lang->context_tree->add_node(keys, std::string("module name"));
    //std::cout << "context tree: " << svl_lang->context_tree << "\n";
}

void SvlmLangContext::add_mvar_name(const std::string &mv) { // int n, with offset for array
  current_context.mvar = mv;
  full_symbol_t fst = current_context; fst.mvar= mv;
  std::vector<std::string> keys = move(get_sym_key(key_tok_t::mvar, fst));
  svl_lang->context_tree->add_node(keys, std::string("value"));
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
  std::shared_ptr<TreeNode> sym_node = svl_lang->context_tree->get_node({key});

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

