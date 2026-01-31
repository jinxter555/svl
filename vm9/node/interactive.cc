#include <iostream>
#include "interactive.hh"
#include "my_helpers.hh"

#include "kernel.hh"

#define SLOG_DEBUG_TRACE_FUNC
#include "scope_logger.hh"

// Interactive svlm_it(".svlm_history", "svlm> ");
// histoery_file , prompt string
Interactive::Interactive(const std::string& hf , const std::string&ps) 
: LangPrompt(hf, ps) 
{
  MYLOGGER(trace_function , string("LispExprInteractive::LispExprInteractive()") , __func__, SLOG_FUNC_INFO);
  lang.set_interface(this);

//  init_command_functions();
  
};


void Interactive::accept_prompt(const std::string &line) {
  MYLOGGER(trace_function, "Interactive::accept_prompt(const string& line)", __func__, SLOG_FUNC_INFO);
  cout << " in interactive:: accept prompt!\n";
  cout << "you have entered: " << line <<"\n";
//  parse_prompt(line);
}

PromptSwitch Interactive::ready() { 
  return LangPrompt::ready();
}
string Interactive::read() { 
  return LangPrompt::read();
}

void Interactive::parse_prompt(const std::string &line) {
//    svlm_lang.interactive = true;
    if(line[0] == '!' && line[1] == '!') 
      //interact(line);
      parse(line);
    else {
      parse(line);
    }
}

void Interactive::parse(const std::string &line) {
  std::istringstream input_buffer(line+"\n");
}


void Interactive::interact(Commandline &cmdline) {
  cmdline.run(this);
}


Node::OpStatus Interactive::load(const std::string &filename) {
  MYLOGGER(trace_function , "Interactive::load(string cfn)" , __func__, SLOG_FUNC_INFO);
  MYLOGGER_MSG(trace_function, string("filename: ") + filename, SLOG_FUNC_INFO);

  std::ifstream infile(filename);
  if(! infile.is_open()) {
    return {false, Node::create_error(Error::Type::System, "Can't open file: " + filename)};
  }

  string line, source_str; 
  Node::List source; Node::Map map;

  while(getline(infile, line) ) {
    source_str = source_str + line + "\n" ;
    source.push_back(Node::create(line));
  }
  infile.close();

  map["source"] = Node::create(move(source));
  map["source_str"] = Node::create(move(source_str));

  return {true, Node::create(move(map))};


}
void Interactive::reload(const std::string &cfn) {
  MYLOGGER(trace_function , string("Interactive::reload(") + cfn + string(")") , __func__, SLOG_FUNC_INFO);
  load(cfn);
}

void Interactive::run_program(const std::string &l) {
  MYLOGGER(trace_function , "Interactive::run_program()" , __func__, SLOG_FUNC_INFO);
  //MYLOGGER(trace_function , __PRETTY_FUNCTION__ , __func__, SLOG_FUNC_INFO);
  //std::cout << "run program\n";
  //svlm_lang.run_evaluate();
  lang.run_program();

}
Node::OpStatus Interactive::build_program(const std::string &source) {
  MYLOGGER(trace_function , "Interactive::build_program()" , __func__, SLOG_FUNC_INFO);
  return lang.build_program(source);
}
void Interactive::print() {
  MYLOGGER(trace_function , "Interactive::print()" ,  __CLASS_NAME__ + "::" +  __func__, SLOG_FUNC_INFO);
  lang.print();
}
