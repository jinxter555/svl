#include <getopt.h>
#include <iostream>
#include <map>
#include <string>
#include <vector>

using namespace std;
class CommandLine {
  private:
  public:
    map<string, string> options;
    string infile_name, outfile_name;
    vector<string> arguments;
    static struct option long_options[];

    void outerr(char *argv[]);
    bool repetition=false, interactive=false;

    CommandLine(int argc, char* argv[]);
    void printout();
};

