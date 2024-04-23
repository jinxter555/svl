#pragma once
#include <sstream>
#include <map>
#include <string>
#include <functional>

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
  SvlmInteractive(const std::string&hf, const std::string&ps, std::shared_ptr<Tree> tp);//  : LangPrompt(hf, ps) {};
  void accept_prompt(const std::string&l) override; // readyline prompt
  void parse(const std::string &line); // parse readline line
  void parse_prompt(const std::string &line); // parse readline line
  void interact(const std::string &line); // parse readline line
  void load(const std::string &filename); // load files from command line
  void run_program(const std::string &l="");


  // command completion
  std::map<std::string, std::function<void(const std::string&)>> command_functions;
  void init_command_functions();

  static std::vector<std::string> cui_keys;

  std::vector<std::string> get_ui_commands(const std::vector<std::string> &ptk={});                                                 
  void set_ui_commands();

  static char** command_completion(const char *text, int start, int end);
  static char* command_generator(const char *text, int state);
  static void convert_buff_to_keys();


  // using CommandFunctionPtr = std::function<void(const std::string &)>;
  void print_tree(const std::string& line);
  void printHello(const std::string& message);
  void printGoodbye(const std::string& message);
  void print_ast(const std::string& line);

};