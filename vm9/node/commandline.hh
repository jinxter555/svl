#pragma once

#include <getopt.h>
#include <iostream>
#include <map>
#include <string>
#include <vector>

class Interactive;
class Commandline {
  friend class Interactive;
public:
  //std::map<std::string, std::string> options;
  std::string infile_name="";
  std::vector<std::string> arguments;

  static struct option long_options[];
  bool opt_interactive=false,
  opt_run=false,
  opt_file=false,
  assembly_lang=false,
  lisp_lang=false,
  svlm_lang=false,
  opt_print=false;

  Commandline(int argc, char* argv[]);
  void outerr(char *argv[]);
  void printout();
  void run(Interactive*);
  void load_files(Interactive *i, const std::string& file_str);

};
