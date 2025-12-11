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
  bool opt_interactive=false;
  bool opt_run=false;
  bool opt_file=false;
  bool assembly_lang=false;
  bool lisp_lang=false;
  bool svlm_lang=false;

  Commandline(int argc, char* argv[]);
  void outerr(char *argv[]);
  void printout();
  void run(Interactive*);

};
