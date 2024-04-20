  #include "svlm_lang.hh"

  SvlmLang::SvlmLang(std::shared_ptr<Tree> tp) { 
    std::cout << "svlmlang init\n";
    context_tree = tp; 
    if(tp == nullptr) { std::cerr << "SvlmLang init: tree pointer is null!\n"; }

    tp->add_node({SVLM_AST_TREE}, std::string("program"));

    auto cc = tp->get_node({SVLM_AST_TREE});

    current_context = std::make_shared<ListExprAst>(std::string("ast code here"));
    if(current_context == nullptr) { std::cerr << "SvlmLang init: current_context is null!\n"; }
    cc->add_child("code", current_context);

    //auto cc2 = std::dynamic_pointer_cast<ListExprAst>(tp->get_node({SVLM_AST_TREE, "code"}));
    //std::cout << "current context pointer: "<< current_context << "\n";
    //std::cout << "cc2 pointer: "<< cc2 << "\n";

    current_contexts.push
    ( current_context
    );
  }