#pragma once
#include <readline/readline.h>
#include <readline/history.h>
#include <vector>
#include <iostream>
#include <fstream>

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


class PromptInteractive {
public:
  void save_history(Prompt&);
  void load_history(Prompt&);
  void ready(Prompt&); // ready for user readline input
};