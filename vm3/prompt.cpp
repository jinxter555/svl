#include "prompt.hh"
#include <cstring>

void PromptInteractive::save_history(Prompt& p) {
  std::ofstream outfile(p.history_filename);
 if(outfile.is_open()) {
    for(const std::string& command : p.history) {
      outfile << command << std::endl;
    }
    outfile.close();
  } else {
    std::cerr 
      << "Error saving history to file: " 
      << p.history_filename << std::endl;
  }
}

void PromptInteractive::load_history(Prompt& p) {
  std::ifstream infile(p.history_filename);
  if(infile.is_open()) {
    std::string line;
    while(getline(infile, line)) {
      p.history.push_back(line);
      add_history(line.c_str());
    }
  } else {
    std::cerr 
      << "Error loading history from file: " 
      << p.history_filename << std::endl;
  }
}

// ready for user readline input
void PromptInteractive::ready(Prompt& p) {
  char *input;
  std::string input_str;
  // history.clear();
  while( (input = readline(p.prompt_string.c_str())) != nullptr) {
    if(strcmp(input, "")==0)  continue; 
    add_history(input);
    p.history.push_back(input);
    input_str = input; 
    free(input);
    if(input_str == "exit") break;
    p.accept_prompt(input_str);
  }
}