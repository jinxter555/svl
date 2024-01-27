#include <iostream>
#include <fstream>
#include "commandline.hh"
#include <readline/readline.h>
#include <readline/history.h>
#include "readinputline.hh"
#include "expr.hh"
#include "parser.hh"
#include "interpreter.hh"


using namespace std;

int main(int argc, char *argv[]) {
  char *input;
  Interpreter itp;
  ReadInputLine t;

  Parser p;
  ifstream infile;
  string input_str, text;

  CommandLine cml(argc, argv);

  for(auto const& infile_name : cml.arguments) {
    infile.open(infile_name);
    while (getline(infile, input_str)) {
      if (input_str == "EOF") break;
      text=t.readyline(input_str);
      if(text!=""){        // return "" if more text is quoted and multiline 
        t.tokenize(text);
        t.print_tokens();
        t.clear_token();
      }
    }
    cout << "\n";
    infile.close();
  }

  if(cml.interactive) {
    while ((input = readline("> ")) != nullptr) {
      add_history(input);
      input_str=input;
      free(input);          
      if (input_str == "exit") break;          
      if(input_str[0]=='\\') {
        itp.cml_action(input_str);
        continue;
      }
      if (input_str == "clear"){
        t.clear_token();
        continue;
      }
      if (input_str == "print_token"){
        t.print_tokens(); 
        // interpreter vmsvl print code
        continue;
      }
      text=t.readyline(input_str);
      if(text!=""){        // return "" if more text is quoted and multiline 
        t.tokenize(text);

        // p.run(t);
        cout << "Result: " ;
        cout <<  "\n";
        Expr e(t);
        itp.add_expr(e);
        itp.run();
        //e.print();
        //e.Evaluate().print(); 
//        t.print_tokens();
//        t.clear_token();
      }
    }
  }

  //cml.printout();
  return 0;
}

