#include <iostream>
#include "interactive.hh"
#include "my_helpers.hh"

#include "kernel.hh"

#define SLOG_DEBUG_TRACE_FUNC
#include "scope_logger.hh"

extern Interactive *it_ptr;
std::vector<std::string> Interactive::cui_keys={};
Node *Interactive::proc_shell=nullptr;

// Interactive svlm_it(".svlm_history", "svlm> ");
// histoery_file , prompt string

Interactive::Interactive(const std::string& hf , const std::string&ps) 
: LangPrompt(hf, ps) 
{
  MYLOGGER(trace_function , string("LispExprInteractive::LispExprInteractive()") , __func__, SLOG_FUNC_INFO);
  lang.set_interface(this);

  
};


void Interactive::accept_prompt(const std::string &line) {
  MYLOGGER(trace_function, "Interactive::accept_prompt(const string& line)", __func__, SLOG_FUNC_INFO);
  cout << " in interactive:: accept prompt!\n";
  cout << "you have entered: " << line <<"\n";

  auto token_list = lang.reader.tokenize( lang.reader.tokenize_preprocess( line)); // list<Token> 
  auto parsed_tokens_status =  lang.reader.parse(token_list); // parse 
  if(!parsed_tokens_status.first) {
    cerr << "error parsing string token: !"  << parsed_tokens_status.second->_to_str() <<" \n";
    //return parsed_tokens_status;
  }

  auto tokens = Node::create(move(parsed_tokens_status.second->_get_list_ref())); // this extra step maybe uncessary in future
  auto input_code_status = lang.parse_build(*tokens);
  if(input_code_status.first) {
    //lang. kernel eval?
  }

//  parse_prompt(line);
}

PromptSwitch Interactive::ready() { 
  return LangPrompt::ready();
}
string Interactive::read(Node*process_ptr) { 
  proc_shell = process_ptr;
  return LangPrompt::read();
}

void Interactive::parse_prompt(const std::string &line) {
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
  lang.run_program(0, nullptr);
}
void Interactive::run_program(int argc, char *argv[]){
  MYLOGGER(trace_function , "Interactive::run_program(int argc, char *argv[])" , __func__, SLOG_FUNC_INFO);
  lang.run_program(argc, argv);
}



Node::OpStatus Interactive::build_program() {
  MYLOGGER(trace_function , "Interactive::build_program()" , __func__, SLOG_FUNC_INFO);
  return lang.build_program();
}

Node::OpStatus Interactive::build_file_str(const std::string &source) {
  MYLOGGER(trace_function , "Interactive::build_program()" , __func__, SLOG_FUNC_INFO);
  auto op_status = lang.build_file_str(source);
  return op_status;
}


void Interactive::print() {
  MYLOGGER(trace_function , "Interactive::print()" ,  __CLASS_NAME__ + "::" +  __func__, SLOG_FUNC_INFO);
  lang.print();
}

LispReader& Interactive::get_reader() {
  return lang.get_reader();
}


// ptk current prompt line list of strings
vector<std::string> Interactive::get_ui_commands(const vector<string> &ptk) {
  //it_ptr->lang.frame_current();
  //cout << "ptk: " << _to_str_ext( ptk) << "\n";
  //vector<string> l1= {"hello", "world", "help", "word"};
  auto lvs = it_ptr->lang.get_local_vars(*proc_shell);

  //lvs.insert(lvs.end(), l1.begin(), l1.end());

  return lvs;
}


// -------------------command completion
void Interactive::convert_buff_to_keys() {
  std::string rlbuff=trim(rl_line_buffer);
  cui_keys.clear();
  if(rl_line_buffer!=NULL)
    cui_keys = split_string(rlbuff, " ");
}


char* Interactive::command_generator(const char *text, int state) {
  std::vector<std::string> commands = std::move(get_ui_commands(cui_keys));
  int  commands_size = commands.size();
  std::string textstr(text), command;
  static int list_index, len; 

  if(!state) {
    list_index = 0;
    len = strlen(text);
  }  
  
  while(list_index < commands_size && (command = commands[list_index++]) != "") {
    if( command.compare(0, len, textstr) == 0) {
      return strdup(command.c_str());
    }
  }
  return nullptr;
}

char** Interactive::command_completion(const char *text, int start, int end) {
  char **matches;
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
