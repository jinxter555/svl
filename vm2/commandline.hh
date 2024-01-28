#include <getopt.h>
#include <iostream>
#include <map>
#include <string>
#include <vector>

using namespace std;

class Commandline {
public:
  map<string, string> options;
  string infile_name;
  vector<string> arguments;

  static struct option long_options[];
  bool interactive=false;
  Commandline(int argc, char* argv[]);
  void outerr(char *argv[]);
  void printout();

};
