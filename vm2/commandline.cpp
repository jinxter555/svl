#include "commandline.hh"

struct option Commandline::long_options[] = {
  {"inputfile", required_argument, NULL, 'f'},
  {NULL, 0, NULL, 0}
};

Commandline::Commandline(int argc, char* argv[]) {
  int opt;

  while( (opt = getopt_long(argc, argv, "if:o:", long_options, NULL)) != -1) {
    switch(opt) {
      case 'i': interactive = true; break;
      case 'f': infile_name  = optarg; break;
    }
  }
}
void Commandline::outerr(char *argv[]) {
  std::cerr 
    << "Usage: " 
    << argv[0] 
    << " [-i interactive] [-f inputfile] [--inputfile=inputfile] [-o outputfile] [--outputfile=outputfile]\n";
}

void Commandline::printout() {
  for (auto const& pair : options)
    std::cout 
      << pair.first 
      << ": " 
      << pair.second 
      << std::endl;

  cout << "\n";
  for (auto const& str : arguments)
    cout << str << " ";
    cout << "\n";

  cout << "infile:" << infile_name << "\n";


  if(interactive)
    cout << "interactive: true" << " ";
  else
    cout << "interactive: false" << " ";

  cout << "\n";
};


