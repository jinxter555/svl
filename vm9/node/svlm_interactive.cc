#include <iostream>
#include "svlm_interactive.hh"
#include "my_helpers.hh"
#include "operand_vars.hh"

#include "lang.hh"

#define SLOG_DEBUG_TRACE_FUNC
#include "scope_logger.hh"

//SvlmInteractive svlm_it(".svlm_history", "svlm> ");
SvlmInteractive *svlm_it_ptr;

SvlmInteractive::SvlmInteractive(const std::string& hf , const std::string&ps) 
: LangPrompt(hf, ps) , svlm_lang(OperandType::svlm_lang_t) 
{
  MYLOGGER(trace_function , string("SvlmInteractive::SvlmInteractive()") , __func__, SLOG_FUNC_INFO);

  init_command_functions();
  svlm_lang.svlm_scanner_ptr = &svlm_scanner; // set up scanner for self/recursive eval in ast
  svlm_lang.svlm_parser_ptr = &svlm_parser;  // set up parser for self/recursive eval in ast


  vector<string> keys0 = {CONTEXT_UNIV, "bigbang"};
  //vector<string> keys1 = {"hello", "one", "two1", "three"};
  //vector<string> keys1b = {"hello", "one", "two1"};

  vector<string> keys1 = {CONTEXT_UNIV,"hello", "one", "two"};
  vector<string> keys2 = {CONTEXT_UNIV,"hello", "one", "two", "three", "four", "Five"};

  //vector<string> keys2b = {CONTEXT_UNIV,"hello", "one", "two"};
  vector<string> keys3 = {CONTEXT_UNIV,"hello", "one-one", "two", "three", "four", "Five"};
  vector<string> keys3b  = {CONTEXT_UNIV,"hello", "one-one", "two"};

  svlm_lang.root.add(keys0, 55555l, true);
  svlm_lang.root.add(keys1,  123l, true);
  svlm_lang.root.add(keys2,  456l, true);
  svlm_lang.root.add(keys3,  "somestrval", true);

  shared_ptr<MathModule> math = make_shared<MathModule>(svlm_lang);
  math->bind_sthis(math);
  svlm_lang.bind_module(math);

  shared_ptr<KernelModule> kernel= make_shared<KernelModule>(svlm_lang);
  kernel->bind_sthis(kernel);
  svlm_lang.bind_module(kernel);

  shared_ptr<FileModule> file = make_shared<FileModule>(svlm_lang);
  file->bind_sthis(file);
  svlm_lang.bind_module(file);
  
};

void SvlmInteractive::print_tree(const std::string& line) {
  MYLOGGER(trace_function , string("SvlmInteractive::print_tree(") + line + string(")") , __func__, SLOG_FUNC_INFO);
  std::vector<std::string> vstr = split_string(line, " ");
  if(vstr.size() == 1 && vstr.back() == ""){ 
    cout << "Universe: " << CONTEXT_UNIV << "\n";
    vstr = {CONTEXT_UNIV}; 
  }

  auto children = svlm_lang.root[vstr]._get_keys();
  if(children.empty()) {
    auto &value= svlm_lang.root[vstr];
    cout << value << "\n";;

/*
    auto vptr = value._vrptr();
    if(vptr->_get_type() == OperandType::list_t) {
      auto &l = vptr->get_list()._get_list();
      for(auto &e: l)  {
        auto evptr = e._vrptr();
        cout << "e.gettype: " << e.get_type() << "\n";
        cout << "evptr.gettype: " << evptr->get_type() << "\n";
      }
    }
*/
    return;
  }

  for(auto c : children) { std::cout << "child: " << c << "\n"; }
  //svlm_lang.root.print();


}

void SvlmInteractive::print_ast(const std::string& line) {
  
  std::vector<std::string> vstr = split_string(line, " ");
  /*
  std::shared_ptr<TreeNode> cc  = 
    svlm_lang.context_tree->get_node({SVLM_AST_TREE});
  std::shared_ptr<ListExprAst> program = 
    std::dynamic_pointer_cast<ListExprAst>(cc->get_child("code"));
  program->print();
*/
}

void SvlmInteractive::print_stack(const std::string& message) {
  int i=0;
  std::cout << "stack: " <<  message << std::endl;

  /*
  for ( std::vector<std::shared_ptr<TMA>>::iterator it = svlm_lang.svlm_stack.begin() ; 
    it != svlm_lang.svlm_stack.end(); ++it) {
    if((*it)==nullptr) { std::cerr << "nullptr in stack!\n"; break;}
    std::cout << i++ << ": " << (*it) << "\n";

  //for (const auto& sharedMap : svlm_lang.svlm_stack) {
  for (const auto& frame : svlm_lang.svlm_stack) {
    auto sharedMap  = frame.lvars;
    std::cout << i++ << ":";
    for (const auto& keyValue : *sharedMap) {
      std::any second  = keyValue.second;
      std::cout << keyValue.first << ": " << second << std::endl;
    }
    std::cout << std::endl;
  }
  }*/

  std::cout << '\n';

}

void SvlmInteractive::printGoodbye(const std::string& message) {
  std::cout << "goodbye: " << message << std::endl;
}

void SvlmInteractive::init_command_functions() {
  command_functions =  {
    {"!!print_tree", std::bind(&SvlmInteractive::print_tree, this,  std::placeholders::_1)},
    {"!!print_stack", std::bind(&SvlmInteractive::print_stack, this,  std::placeholders::_1)},
    {"!!print_goodbye", std::bind(&SvlmInteractive::printGoodbye, this,  std::placeholders::_1)},
    {"!!print_ast", std::bind(&SvlmInteractive::print_ast, this,  std::placeholders::_1)},
    {"!!reload", std::bind(&SvlmInteractive::reload, this,  std::placeholders::_1)},
    {"!!run_program", std::bind(&SvlmInteractive::run_program, this,  std::placeholders::_1)},
  };
}

std::vector<std::string> SvlmInteractive::cui_keys = {                                                                         
};

void SvlmInteractive::accept_prompt(const std::string &line) {
  parse_prompt(line);
}

void SvlmInteractive::parse_prompt(const std::string &line) {
    svlm_lang.interactive = true;
    if(line[0] == '!' && line[1] == '!') 
      interact(line);
    else {
      parse(line);
    }
}

void SvlmInteractive::parse(const std::string &line) {
  std::istringstream input_buffer(line+"\n");
  svlm_scanner.switch_streams(&input_buffer, &std::cerr);
  svlm_parser.parse();
  evaluate_line();

  // evaluate ast_current_context pop back members
}
void SvlmInteractive::evaluate_line() {
  MYLOGGER(trace_function , "SvlmInteractive::evaluate_line()" , string("SvlmInteractive::")  + string(__func__), SLOG_FUNC_INFO);
  auto result = svlm_lang.evaluate_prompt_line();
  //std::cout << "evaluate line" << "\n";

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
}

void SvlmInteractive::load(const std::string &cfn) {
  MYLOGGER(trace_function , "SvlmInteractive::load()" , string("SvlmInteractive::")  + string(__func__), SLOG_FUNC_INFO);
  std::vector<std::string> filenames = split_string(cfn, " ");

  for(auto filename : filenames) {
    std::ifstream infile(filename);
    if(infile.is_open()) {
      svlm_scanner.switch_streams(&infile, &std::cerr);
      svlm_parser.parse();
    } else {
      std::cerr << "Error opening vslm file: " <<  filename << "\n";
    }
    infile.close();
  }
}
void SvlmInteractive::reload(const std::string &cfn) {
  MYLOGGER(trace_function , string("SvlmInteractive::reload(") + cfn + string(")") , string("SvlmInteractive::")  + string(__func__), SLOG_FUNC_INFO);
  load(cfn);
}

void SvlmInteractive::run_program(const std::string &l) {
  MYLOGGER(trace_function , "SvlmInteractive::run_program()" , string("SvlmInteractive::")  + string(__func__), SLOG_FUNC_INFO);
  //std::cout << "run program\n";
  svlm_lang.run_evaluate();

}

void SvlmInteractive::interact(const std::string &cline) {
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

std::vector<std::string> SvlmInteractive::get_ui_commands(const std::vector<std::string> &ptk) {
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
