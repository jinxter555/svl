#include "prompt.hh"
#include <cstring>


void LangPrompt::save_history() {
  std::ofstream outfile(history_filename);
 if(outfile.is_open()) {
    for(const std::string& command : history) {
      outfile << command << std::endl;
    }
    outfile.close();
  } else {
    std::cerr 
      << "Error saving history to file: " 
      << history_filename << std::endl;
  }
}

void LangPrompt::load_history() {
  std::ifstream infile(history_filename);
  if(infile.is_open()) {
    std::string line;
    while(getline(infile, line)) {
      history.push_back(line);
      add_history(line.c_str());
    }
  } else {
    std::cerr 
      << "Error loading history from file: " 
      << history_filename << std::endl;
  }
}


// ready for user readline input
PromptSwitch LangPrompt::ready() {
  char *input;
  std::string input_str;
  // history.clear();


  while( (input = readline(prompt_string.c_str())) != nullptr) {
    if(strcmp(input, "")==0)  continue; 
    add_history(input);
    history.push_back(input);
    input_str = input; 
    free(input);
    if(input_str == "exit") return PromptSwitch::exit;
    if(input_str == "!asm") return PromptSwitch::vasm;
    if(input_str == "!svlm") return PromptSwitch::svlm;
    accept_prompt(input_str);
  }
  return PromptSwitch::exit;
}