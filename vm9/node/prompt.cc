#include "prompt.hh"
#include <cstring>

PromptInteractive myprompt;
LangPrompt *lang_it;

void PromptInteractive::save_history(Prompt& prompt) {
  std::ofstream outfile(prompt.history_filename);
 if(outfile.is_open()) {
    for(const std::string& command : prompt.history) {
      outfile << command << std::endl;
    }
    outfile.close();
  } else {
    std::cerr 
      << "Error saving history to file: " 
      << prompt.history_filename << std::endl;
  }
}

void PromptInteractive::load_history(Prompt& prompt) {
  std::ifstream infile(prompt.history_filename);
  if(infile.is_open()) {
    std::string line;
    while(getline(infile, line)) {
      prompt.history.push_back(line);
      add_history(line.c_str());
    }
  } else {
    std::cerr 
      << "Error loading history from file: " 
      << prompt.history_filename << std::endl;
  }
}


// ready for user readline input
PromptSwitch PromptInteractive::ready(Prompt& prompt) {
  char *input;
  std::string input_str;
  // history.clear();


  while( (input = readline(prompt.prompt_string.c_str())) != nullptr) {
    if(strcmp(input, "")==0)  continue; 
    add_history(input);
    prompt.history.push_back(input);
    input_str = input; 
    free(input);
    if(input_str == "exit") return PromptSwitch::exit;
    if(input_str == "!asm") return PromptSwitch::vasm;
    if(input_str == "!svlm") return PromptSwitch::svlm;
    prompt.accept_prompt(input_str);
  }
  return PromptSwitch::exit;
}