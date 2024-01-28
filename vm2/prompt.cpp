#include "prompt.hh"
#include "assembly.hh"
#include <cstring>

using namespace std;

void PromptInteractive::save(Prompt& p) {
  ofstream outfile(p.history_filename);
  if(outfile.is_open()) {
    for(const string& command : p.history) {
      outfile << command << endl;
    }
    outfile.close();
  } else {
    cerr << "Error saving history to file: " << p.history_filename << endl;
  }
}

void PromptInteractive::load(Prompt& p) {
  ifstream infile(p.history_filename);
  if(infile.is_open()) {
    string line;
    while(getline(infile, line)) {
      p.history.push_back(line);
      add_history(line.c_str());
    }
  } else {
    cerr << "Error loading history from file: " << p.history_filename << endl;
  }
}

void PromptInteractive::run(Prompt& p) {
  char *input;
  string input_str;
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
