#pragma once

#include <getopt.h>
#include <iostream>
#include <map>
#include <string>
#include <vector>

class Commandline {
public:
  //std::map<std::string, std::string> options;
  std::string infile_name;
  std::vector<std::string> arguments;

  static struct option long_options[];
  bool interactive=false;
  bool assembly_lang=false;
  bool svlm_lang=true;
  bool run=false;

  Commandline(int argc, char* argv[]);
  void outerr(char *argv[]);
  void printout();
};
