#include <getopt.h>
#include <iostream>
#include <map>
#include <string>
#include <vector>
#include "commandline.hh"

struct option CommandLine::long_options[] = {
 {"inputfile", required_argument, NULL, 'f'}, 
 {"outputfile", required_argument, NULL,'o' }, 
 {NULL, 0, NULL, 0}
};

CommandLine::CommandLine(int argc, char* argv[]) {
  int opt;
  while ((opt = getopt_long(argc, argv, "irf:o:", long_options, NULL)) != -1) {
    switch (opt) {
      case 'i':
        interactive = true;
        break;
      case 'r':
        repetition= true;
        break;
      case 'f':
        infile_name = optarg;
        break;
      case 'o':
        outfile_name = optarg;
        break;
     default:
       outerr(argv);
       exit(EXIT_FAILURE);
    }
  }
  for(int i=optind; i < argc; i++)
    arguments.push_back(argv[i]);
}
void CommandLine::outerr(char *argv[]) {
   std::cerr << "Usage: " << argv[0] << " [-i interactive] [-r repetition] [-f inputfile] [--inputfile=inputfile] [-o outputfile] [--outputfile=outputfile]\n";
}

void CommandLine::printout() {
      for (auto const& pair : options)
        std::cout << pair.first << ": " << pair.second << std::endl;

      cout << "\n";
      for (auto const& str : arguments)
        cout << str << " ";
      cout << "\n";

      if(repetition)
        cout << "repetition: true" << " ";
      else
        cout << "repetition: false" << " ";
      if(interactive)
        cout << "interactive: true" << " ";
      else
        cout << "interactive: false" << " ";

      cout << "\n";
    };



/*
int main(int argc, char *argv[]) {
  CommandLine cml(argc, argv);
  cml.printout();
  

  return 0;
}
*/
