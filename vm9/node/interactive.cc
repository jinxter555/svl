#include <iostream>
#include "interactive.hh"
#include "my_helpers.hh"

#include "kernel.hh"

#define SLOG_DEBUG_TRACE_FUNC
#include "scope_logger.hh"

//SvlmInteractive svlm_it(".svlm_history", "svlm> ");

Interactive::Interactive(const std::string& hf , const std::string&ps) 
: LangPrompt(hf, ps) 
{
  MYLOGGER(trace_function , string("LispExprInteractive::LispExprInteractive()") , __func__, SLOG_FUNC_INFO);

//  init_command_functions();
  
};


void Interactive::accept_prompt(const std::string &line) {
  parse_prompt(line);
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
  evaluate_line();
  // evaluate ast_current_context pop back members
}


void Interactive::evaluate_line() {
  MYLOGGER(trace_function , "SvlmInteractive::evaluate_line()" , string("SvlmInteractive::")  + string(__func__), SLOG_FUNC_INFO);
  //std::cout << "evaluate line" << "\n";

  /*
  if(result.size()>0 ) {
    auto &v = result.back();
    if(v.is_nil()) { // Operand_math != is notworking 
      //cout << "v==nil" << result << "\n";
      cout << "nil\n";
    } else  {
      //cout << "v.get_type(): " << v.get_type() << "--\n";
      cout << v << "\n";
    }
  } else {
    //cout << "result.type: " << result.get_type() << "\n";
    if(result.type_==OperandType::nil_t){
      cout << "nil\n";
      return;
    }
    cout << result[0] << "-\n";
  }
    */
}

void Interactive::interact(Commandline &cmdline) {
  //cout << "hello, world!\n";
  cmdline.run(this);

}

void Interactive::interact(const std::string &c) {
}
Node::OpStatus Interactive::load(const std::string &filename) {
  MYLOGGER(trace_function , "Interactive::load(string cfn)" , __func__, SLOG_FUNC_INFO);

  std::ifstream infile(filename);
  if(! infile.is_open()) {
    return {false, Node::create_error(Node::Error::Type::System, "Can't open file: " + filename)};
  }

  string line, source_str; 
  Node::List source; Node::Map map;

  while(getline(infile, line) ) {
    source_str += line;
    source.push_back(Node::create(line));
  }
  infile.close();

  map["source"] = Node::create(move(source));
  map["source_str"] = Node::create(move(source_str));

  return {true, Node::create(move(map))};
}
void Interactive::reload(const std::string &cfn) {
  MYLOGGER(trace_function , string("SvlmInteractive::reload(") + cfn + string(")") , string("SvlmInteractive::")  + string(__func__), SLOG_FUNC_INFO);
  load(cfn);
}

void Interactive::run_program(const std::string &l) {
  MYLOGGER(trace_function , "SvlmInteractive::run_program()" , string("SvlmInteractive::")  + string(__func__), SLOG_FUNC_INFO);
  //std::cout << "run program\n";
  //svlm_lang.run_evaluate();
  lang.run_program();

}
Node::OpStatus Interactive::build_program(const std::string &source) {
  MYLOGGER(trace_function , "Interactive::build_program()" , string("SvlmInteractive::")  + string(__func__), SLOG_FUNC_INFO);
  return lang.build_program(source);
}
void Interactive::print() {
  lang.print();
}


/*
void Interactive::interact(const std::string &cline) {
  MYLOGGER(trace_function , "SvlmInteractive::interact(const string&)" , string("SvlmInteractive::")  + string(__func__), SLOG_FUNC_INFO);
  MYLOGGER_MSG(trace_function, string("line: ") + cline, SLOG_FUNC_INFO);

  std::string line = move(reduce(cline));
  std::vector<std::string> tokens= move(split_string(line, " "));
  std::string command = tokens.front();

  //cout << "interact: " << line << "\n";
  if(command_functions[command] != nullptr) {
    std::string args =  move(trim(match(line, command)));
    (command_functions[command])(args);
    //cout << "args: " << args << "\n";
  } else 
    std::cerr << command << " not found!\n";
}

std::vector<std::string> Interactive::get_ui_commands(const std::vector<std::string> &ptk) {
  std::vector<std::string> keys;
  std::vector<std::string> children;
  keys = {rlsvlm_loc};
  //keys = {CONTEXT_UNIV};
  keys.insert(keys.end(), ptk.begin(), ptk.end());
  
// std::cout << "keys: "; for(auto k: keys) { std::cout << k << ","; } std::cout << "\n";

  children = svlm_lang.root[keys]._get_keys();
  children.push_back("");

  // std::cout << "children: "; for(auto k: children) { std::cout << k << ","; } std::cout << "\n";

  return children;
}


void SvlmInteractive::set_ui_commands() {
  std::string command; int list_index=0;
  std::vector<std::string> keys;

  //svlm_lang.root.print_m();

  for(auto const&[command, fun] : SvlmInteractive::command_functions) {
    if(command =="") continue;
    keys = {rlsvlm_loc, command};
    add_readline(command);
  }

}

void SvlmInteractive::add_readline(const string& cmd) {
  MYLOGGER(trace_function , "SvlmInteractive::add_readline()" , string(__func__), SLOG_FUNC_INFO);
  std::vector<std::string> keys;
  keys = {rlsvlm_loc, cmd};

  //cout << "adding to: " <<  cmd << " readline\n";

  if(cmd == "!!print_tree") {
    auto univ_ptr = svlm_lang.root[CONTEXT_UNIV]._vrptr();
    //auto univ_ptr = &svlm_lang.root[CONTEXT_UNIV];
    if(univ_ptr==nullptr) {
      cerr << "uni_ptr is null!\n";
      exit(1);
    }
    svlm_lang.root.add(vec_str_t{rlsvlm_loc, cmd, CONTEXT_UNIV}, univ_ptr, true);
  } else
    svlm_lang.root.add(vec_str_t{rlsvlm_loc, cmd}, nil);
}

                                                                                                            
void SvlmInteractive::convert_buff_to_keys() {
  std::string rlbuff=trim(rl_line_buffer);
  cui_keys.clear();
  if(rl_line_buffer!=NULL)
    cui_keys = split_string(rlbuff, " ");
}


char* SvlmInteractive::command_generator(const char *text, int state) {
  std::vector<std::string> commands = std::move(svlm_it_ptr->get_ui_commands(cui_keys));
  std::string textstr(text), command;
  static int list_index, len; 

  if(!state) {
    list_index = 0;
    len = strlen(text);
  }  
  
  while((command = commands[list_index++]) != "") {
    if( command.compare(0, len, textstr) == 0) {
      return strdup(command.c_str());
    }
  }
  return nullptr;
}

char** SvlmInteractive::command_completion(const char *text, int start, int end) {
  char **matches, *match;
  std::string matchstr, rematch;
  rl_attempted_completion_over = 1;

  if(std::string(rl_line_buffer)  == "") cui_keys.clear();
  if(rl_line_buffer[strlen(rl_line_buffer)-1] == ' ') {convert_buff_to_keys(); }

  matches = rl_completion_matches(text, command_generator);

  if(matches == nullptr && strlen(text) > 0) {     // if stuck from previous command didn't complete properly
    convert_buff_to_keys(); 
    if(!cui_keys.empty()) 
      rematch = cui_keys.back();
    cui_keys.pop_back();
    matches = rl_completion_matches(rematch.c_str(), command_generator);
  }

  return  matches;
}
*/