#pragma once
#include <sstream>
#include <map>
#include <string>
#include <functional>

#include "prompt.hh"
#include "commandline.hh"
#include "lisp_expr.hh"



class Interactive : public LangPrompt {
private:
  LispExpr lang; // static or not static to be determined
public:
  Interactive(const std::string&hf, const std::string&ps);//  : LangPrompt(hf, ps) {};
  void accept_prompt(const std::string&l) override; // readyline prompt
  void parse(const std::string &line) override; // parse readline line
  void parse_prompt(const std::string &line); // parse readline line
  void interact(Commandline &cmdline) ; // parse readline line
  Node::OpStatus load(const std::string &filename) override; // load files from command line
  void reload(const string &filename); // reload file

  Node::OpStatus build_program(const string& input); // create module structure 
  void run_program(const std::string &l="") override;


  PromptSwitch ready(); // ready for user readline input




  // command completion
  std::map<std::string, std::function<void(const std::string&)>> command_functions;

  static std::vector<std::string> cui_keys;

  std::vector<std::string> get_ui_commands(const std::vector<std::string> &ptk={});                                                 

  void print();


};
//extern SvlmInteractive svlm_it;
extern Interactive *svlm_it_ptr;