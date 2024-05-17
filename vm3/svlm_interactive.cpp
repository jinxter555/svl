#include <iostream>
#include "svlm_interactive.hh"
#include "my_helpers.hh"

#include "vm_type.hh"
#include "lang.hh"


std::ostream& operator << (std::ostream& out, std::any& a) ;

extern SvlmInteractive svlm_it;

SvlmInteractive::SvlmInteractive
( const std::string&hf
, const std::string&ps
, std::shared_ptr<Tree> tp
) : LangPrompt(hf, ps), svlm_lang(tp) {
  init_command_functions();
};

void SvlmInteractive::print_tree(const std::string& line) {
  std::vector<std::string> vstr = split_string(line, " ");
  auto children = svlm_lang.context_tree->get_children(vstr);
  for(auto c : children) { std::cout << "child: " << c << "\n"; }

  auto node = svlm_lang.context_tree->get_node(vstr);

  for(int i=0; node!=nullptr && i<node->get_member_size(); i++) {
    auto node_mem = node->get_member(i);
    if(node_mem == nullptr) break;
    std::cout << i << ": "; node_mem->print_data(); std::cout << "\n"; 
  }

  if(node) {std::cout << "value: "; node->print_data(); std::cout << "\n";}
}

void SvlmInteractive::print_ast(const std::string& line) {
  std::vector<std::string> vstr = split_string(line, " ");
  std::shared_ptr<TreeNode> cc  = 
    svlm_lang.context_tree->get_node({SVLM_AST_TREE});
  std::shared_ptr<ListExprAst> program = 
    std::dynamic_pointer_cast<ListExprAst>(cc->get_child("code"));
  program->print();
}


void SvlmInteractive::print_stack(const std::string& message) {
  int i=0;
  std::cout << "stack: " <<  message << std::endl;
  for ( std::vector<std::any>::iterator it = svlm_lang.svlm_stack.begin() ; 
    it != svlm_lang.svlm_stack.end(); ++it) {
    std::cout << i++ << ": " << (*it) << "\n";
  }
  std::cout << '\n';

}

void SvlmInteractive::printGoodbye(const std::string& message) {
  std::cout << "goodbye: " << message << std::endl;
}

void SvlmInteractive::init_command_functions() {
  command_functions =  {
    {"!print_tree", std::bind(&SvlmInteractive::print_tree, this,  std::placeholders::_1)},
    {"!print_stack", std::bind(&SvlmInteractive::print_stack, this,  std::placeholders::_1)},
    {"!print_goodbye", std::bind(&SvlmInteractive::printGoodbye, this,  std::placeholders::_1)},
    {"!print_ast", std::bind(&SvlmInteractive::print_ast, this,  std::placeholders::_1)},
    {"!run_program", std::bind(&SvlmInteractive::run_program, this,  std::placeholders::_1)},
  };
}

std::vector<std::string> SvlmInteractive::cui_keys = {                                                                         
};

void SvlmInteractive::accept_prompt(const std::string &line) {
  parse_prompt(line);
}

void SvlmInteractive::parse_prompt(const std::string &line) {
    if(line[0] == '!') 
      interact(line);
    else {
      slc.interactive = true;
      parse(line);
    }
}

void SvlmInteractive::parse(const std::string &line) {
  std::istringstream input_buffer(line+"\n");
  svlm_scanner.switch_streams(&input_buffer, &std::cerr);
  svlm_parser.parse();
  evaluate_line();

  // evaluate ast_current_context pop back members
}
void SvlmInteractive::evaluate_line() {
  std::any output = slc.evaluate_last_line();
  std::cout << output << "\n";
}

void SvlmInteractive::load(const std::string &cfn) {
  std::vector<std::string> filenames = split_string(cfn, " ");

  for(auto filename : filenames) {
    std::ifstream infile(filename);
    if(infile.is_open()) {
      svlm_scanner.switch_streams(&infile, &std::cerr);
      svlm_parser.parse();
    } else {
      std::cerr << "Error opening vslm file: " <<  filename << "\n";
    }
    infile.close();
  }
}

void SvlmInteractive::run_program(const std::string &l) {
  std::cout << "run program\n";
  slc.run_evaluate();

}

void SvlmInteractive::interact(const std::string &cline) {
  std::string line = move(reduce(cline));
  std::vector<std::string> tokens= move(split_string(line, " "));
  std::string command = tokens.front();
  if(command_functions[command] != nullptr) {
    std::string args =  move(trim(match(line, command)));
    (command_functions[command])(args);
  } else 
    std::cerr << command << " not found!\n";
}

std::vector<std::string> SvlmInteractive::get_ui_commands(const std::vector<std::string> &ptk) {
  std::vector<std::string> keys;
  std::vector<std::string> children;
  keys = {rlsvlm_current_context_key};
  keys.insert(keys.end(), ptk.begin(), ptk.end());
  
  // std::cout << "keys: "; for(auto k: keys) { std::cout << k << ","; } std::cout << "\n";

  children = svlm_lang.context_tree->get_children(keys);
  children.push_back("");
  return children;
}


void SvlmInteractive::set_ui_commands() {
  std::string command; int list_index=0;
  std::vector<std::string> keys;

  for(auto const&[command, fun] : SvlmInteractive::command_functions) {
    if(command =="") continue;
    keys = {rlsvlm_current_context_key, command};
    svlm_lang.context_tree->add_node({keys}, 1);
  }

  std::shared_ptr<TreeNode> ptree_node 
    = svlm_lang.context_tree->get_node({rlsvlm_current_context_key, "!print_tree"});

  if(ptree_node!=nullptr) {
    std::shared_ptr<TreeNode> uni_node = svlm_lang.context_tree->get_node({CONTEXT_UNIV});
    ptree_node->add_child({CONTEXT_UNIV}, uni_node);
  } else
    std::cerr << "Can't add the universe to !print_tree\n";
}

                                                                                                            
void SvlmInteractive::convert_buff_to_keys() {
  std::string rlbuff=trim(rl_line_buffer);
  cui_keys.clear();
  if(rl_line_buffer!=NULL)
    cui_keys = split_string(rlbuff, " ");
}


char* SvlmInteractive::command_generator(const char *text, int state) {
  std::vector<std::string> commands = std::move(svlm_it.get_ui_commands(cui_keys));
  std::string textstr(text), command;
  static int list_index, len; 

  if(!state) {
    list_index = 0;
    len = strlen(text);
  }  
  
  while((command = commands[list_index++]) != "") {
    if( command.compare(0, len, textstr) == 0) {
      return strdup(command.c_str());
    }
  }
  return nullptr;
}

char** SvlmInteractive::command_completion(const char *text, int start, int end) {
  char **matches, *match;
  std::string matchstr, rematch;
  rl_attempted_completion_over = 1;

  if(std::string(rl_line_buffer)  == "") cui_keys.clear();
  if(rl_line_buffer[strlen(rl_line_buffer)-1] == ' ') {convert_buff_to_keys(); }

  matches = rl_completion_matches(text, command_generator);

  if(matches == nullptr && strlen(text) > 0) {     // if stuck from previous command didn't complete properly
    convert_buff_to_keys(); 
    if(!cui_keys.empty()) 
      rematch = cui_keys.back();
    cui_keys.pop_back();
    matches = rl_completion_matches(rematch.c_str(), command_generator);
  }

  return  matches;
}
