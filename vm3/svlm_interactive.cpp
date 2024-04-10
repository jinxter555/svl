#include "svlm_interactive.hh"
#include "my_helpers.hh"



// Define some example functions that take a string argument
void printTree(const std::string& message) {
  std::cout << message << std::endl;
}
void printHello(const std::string& message) {
  std::cout << message << std::endl;
}

void printGoodbye(const std::string& message) {
  std::cout << message << std::endl;
}

std::map<std::string, std::function<void(const std::string&)>> 
  SvlmInteractive::command_functions = {
  {"!print_tree",  printTree},
  {"!print_hello", printHello},
  {"!print_me", printHello},
  {"", nullptr}};

std::vector<std::string> SvlmInteractive::cui_keys = {                                                                         
};

void SvlmInteractive::accept_prompt(const std::string &line) {
  parse_prompt(line);
}

void SvlmInteractive::parse_prompt(const std::string &line) {
    std::istringstream input_buffer(line);
    if(line[0] == '!') 
      interact(line);
}
void SvlmInteractive::parse(const std::string &line) {
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

void SvlmInteractive::run_program() {}

void SvlmInteractive::interact(const std::string &cline) {
  std::string line = move(reduce(cline));
  std::vector<std::string> tokens= move(split_string(line, " "));
  std::string command = tokens.front();
  if(command_functions[command] != nullptr)
    std::cout << command << ": " << line << "\n";
  else 
    std::cerr << command << " not found!\n";
}

std::vector<std::string> SvlmInteractive::get_ui_commands(const std::vector<std::string> &ptk) {
  std::vector<std::string> keys;
  std::vector<std::string> children;
  keys = {rlsvlm_current_context_key};
  keys.insert(keys.end(), ptk.begin(), ptk.end());
  
  // std::cout << "keys: "; for(auto k: keys) { std::cout << k << ","; } std::cout << "\n";

  children = svlm_lang.context->get_children(keys);
  children.push_back("");
  return children;
}
void SvlmInteractive::set_ui_commands() {
  std::string command; int list_index=0;
  std::vector<std::string> keys;
  //std::cout << "set ui commandsize:" << commands.size() << "\n";

  for(auto const&[command, fun] : SvlmInteractive::command_functions) {
    if(command =="") continue;
    keys = {rlsvlm_current_context_key, command};
    svlm_lang.context->add_node({keys}, 1);
  }

  std::shared_ptr<TreeNode> ptree_node 
    = svlm_lang.context->get_node({rlsvlm_current_context_key, "!print_tree"});

  if(ptree_node!=nullptr) {
    std::shared_ptr<TreeNode> uni_node = svlm_lang.context->get_node({CONTEXT_UNIV});
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


extern SvlmInteractive svlm_it;
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
