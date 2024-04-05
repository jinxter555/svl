#include "svlm_interactive.hh"
#include "my_helpers.hh"


void SvlmInteractive::accept_prompt(const std::string &line) {
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

void SvlmInteractive::parse(const std::string &line) {
    std::istringstream input_buffer(line);
    if(line[0] == '!') 
      interact(line);
}

void SvlmInteractive::interact(const std::string &line) {
    std::cout << line << "\n";
}

                                                                                                            
  std::vector<std::string> SvlmInteractive::commands = {                                                                         
  "!print_tree",                                                                                                                    
  "!print_hello",                                                                                                                    
  ""};