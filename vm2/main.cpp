#include <iostream>
#include <fstream>
#include <stack>
#include <vector>
#include <variant>
#include <readline/readline.h>
#include <readline/history.h>
#include "prompt.hh"
#include "commandline.hh"
#include "vm.hh"
#include  "assembler_interactive.hh"

using namespace std;

int main(int argc, char *argv[]) {

  PromptInteractive myprompt;
  Commandline cml(argc, argv);
  AssemblerInteractive ait(".vm_history.txt", "asm> ");
  // AssemblerInteractive ait;

  if(cml.infile_name != "") {
    ait.load(cml.infile_name);
  }

  // cml.printout();


  myprompt.load(ait);
  myprompt.run(ait);
  myprompt.save(ait);

  return 0;
}


