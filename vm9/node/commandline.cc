#include <string>
#include "interactive.hh"
#include "commandline.hh"
#include "my_helpers.hh"

struct option Commandline::long_options[] = {
  {"inputfile", required_argument, NULL, 'f'},
  {"lang", required_argument, NULL, 'l'},
  {NULL, 0, NULL, 0}
};

Commandline::Commandline(int argc, char* argv[]) {
  int opt;
  while( (opt = getopt_long(argc, argv, "prhil:f:o:", long_options, NULL)) != -1) {
    switch(opt) {
      case 'i': { opt_interactive = true; break; }
      case 'r': { opt_run= true; break;}
      case 'p': { opt_print= true; break;}
      case 'l': {
        if(optarg == string("lisp")) lisp_lang = true;
        if(optarg == string("svlm")) svlm_lang = true;
        if(optarg == string("asm")) assembly_lang = true;
        break;
      }
      case 'f': infile_name  = optarg; opt_file=true; break;
      case 'h': outerr(argv); exit(0); break;
    }
  }
  for(; optind < argc; optind++){      
    infile_name += std::string(" ") + std::string(argv[optind]);  
    opt_file=true;
  } 

}

void Commandline::outerr(char *argv[]) {
  std::cerr 
    << "Usage: " 
    << argv[0] 
    << " [-r ] [-i interactive] [-f inputfile] [--inputfile=inputfile] [-o outputfile] [--outputfile=outputfile]\n"
    << " -r run program after load\n"
    ;


};


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
  for(auto const& str : arguments) 
    std::cout << str << " ";
  std::cout << "\ninfile:" << infile_name << "\n";

  if(opt_interactive)
    std::cout << "interactive: true" << " ";
  else
    std::cout << "interactive: false" << " ";

  std::cout << "\n";
}

void Commandline::run(Interactive* interactive) {

  if(opt_file){
    load_files(interactive, infile_name);
  }
  if(opt_run) {
    interactive->run_program();
  }
  // tree structure print after build and run to show frames
  if(opt_print) interactive->print();
}

// build with mulitple source lisp files
void Commandline::load_files(Interactive *interactive, const string& file_str) {
  auto files = split_string(file_str, " ");
  for(auto file : files) {
    auto load_status = interactive->load(file);
    if(!load_status.first) { 
      cerr << "load file error: status error:" << load_status << "\n";
      exit(1); 
    }

    //Node::print_value_recursive(*load_status.second); cout << "\n";

    auto source_status = (*load_status.second)["source_str"];
    if(!source_status.first) {
      cerr << "map source[] status error" << source_status << "\n";
      return;
    }
    //cout << "getstr:" << source_status.second->_get_str() << "\n";
    auto build_status  = interactive->build_program( source_status.second._get_str());
    if(!build_status.first) {
      cerr << "build error status error: " << build_status << "\n";
      return;
    }

    //interactive->print();

  }
}