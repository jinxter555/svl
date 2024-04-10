#pragma once
#include <readline/readline.h>
#include <readline/history.h>
#include <vector>
#include <iostream>
#include <fstream>


enum class PromptSwitch {
  exit,
  begin,
  vasm,
  svlm,
};

class Prompt {
  friend class PromptInteractive;
private:
  std::string history_filename, prompt_string;
  std::vector<std::string> history;
public:
  Prompt(const std::string &fn, const std::string &ps) 
    : history_filename(fn), prompt_string(ps) {}
  virtual void accept_prompt(const std::string &) = 0;
};

class LangPrompt : public Prompt {
public:
  // virtual void accept_prompt(const std::string &) = 0;
  LangPrompt(const std::string&hf, const std::string&ps)
    : Prompt(hf, ps) {};
  virtual void parse(const std::string &line) = 0; // parse readline line
  virtual void interact(const std::string &line) = 0; // parse readline line
  virtual void load(const std::string &filename) = 0; // load files from command line
  virtual void run_program() = 0; // load files from command line
};

class PromptInteractive {
public:
  static void save_history(Prompt&);
  static void load_history(Prompt&);
  static PromptSwitch ready(Prompt&); // ready for user readline input

};