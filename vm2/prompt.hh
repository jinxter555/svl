#pragma once
#include <iostream>
#include <readline/readline.h>
#include <readline/history.h>
#include <vector>
#include <fstream>

using namespace std;

class Prompt {
  friend class PromptInteractive;
public:
  Prompt(const string &fn, const string &ps) : history_filename(fn), prompt_string(ps) {}
  virtual void accept_prompt(const string &) = 0;
private:
  string history_filename, prompt_string;
  vector<string> history;
};

class PromptInteractive {
private:
  // vector<string> history;
  // string filename;
public:
  // PromptInteractive(const string& filename) : filename(filename) {}
  // PromptInteractive(const Prompt& ) : filename(filename) {}
  void save(Prompt&);
  void run(Prompt&);
  void load(Prompt&);
};