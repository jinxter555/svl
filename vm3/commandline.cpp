#include "commandline.hh"

struct option Commandline::long_options[] = {
  {"inputfile", required_argument, NULL, 'f'},
  {NULL, 0, NULL, 0}
};

Commandline::Commandline(int argc, char* argv[]) {
  int opt;
  while( (opt = getopt_long(argc, argv, "rhif:o:", long_options, NULL)) != -1) {
    switch(opt) {
      case 'i': interactive = true; break;
      case 'r': run = true; break;
      case 'f': infile_name  = optarg; break;
      case 'h': outerr(argv); exit(0); break;
    }
  }
}

void Commandline::outerr(char *argv[]) {
  std::cerr 
    << "Usage: " 
    << argv[0] 
    << " [-r ] [-i interactive] [-f inputfile] [--inputfile=inputfile] [-o outputfile] [--outputfile=outputfile]\n"
    << " -r run program after load\n"
    ;


}

void Commandline::printout() {
  /*
  for (auto const& pair : options)
    std::cout 
      << pair.first 
      << ": " 
      << pair.second 
      << std::endl;
  */
  std::cout << "\n";
  for (auto const& str : arguments)
    std::cout << str << " ";
    std::cout << "\n";

  std::cout << "infile:" << infile_name << "\n";


  if(interactive)
    std::cout << "interactive: true" << " ";
  else
    std::cout << "interactive: false" << " ";

  std::cout << "\n";
};
