#pragma once
#include <sstream>
#include "prompt.hh"
#include "svlm_scanner.hh"
#include "svlm_lang.hh"
#include "svlm_parser.hh"

#define CONTEXT_UNIV "svlvm"
#define rlsvlm_current_context_key  CONTEXT_UNIV, "readline",  "commands", "svlm"

class SvlmInteractive : public LangPrompt {
private:
  SvlmLang svlm_lang; // static or not static to be determined
  vslast::SvlmScanner svlm_scanner { std::cin, std::cerr };
  vslast::SvlmParser svlm_parser { &svlm_scanner , &svlm_lang };
public:
  SvlmInteractive(const std::string&hf, const std::string&ps)
    : LangPrompt(hf, ps) {};
  void accept_prompt(const std::string&l) override; // readyline prompt
  void parse(const std::string &line); // parse readline line
  void interact(const std::string &line); // parse readline line
  void load(const std::string &filename); // load files from command line


  // command completion
  static std::vector<std::string> commands;
  static std::vector<std::string> cui_keys;

  std::vector<std::string> get_ui_commands(const std::vector<std::string> &ptk={});                                                 
  void set_ui_commands();

  static void convert_buff_to_keys();
  static char** command_completion(const char *text, int start, int end);
  static char* command_generator(const char *text, int state);
};