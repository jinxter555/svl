#include "io_file.hh"
#include "lang.hh"
#define SLOG_DEBUG_TRACE_FUNC
#include "scope_logger.hh"

vector<File::file_sptr> File::objects={};


Node::Integer File::atom_open, File::atom_close, File::atom_getline;

File::File() {}

void File::init() {
File::atom_open = Lang::str_to_atom("open");
File::atom_close = Lang::str_to_atom("close");
File::atom_getline = Lang::str_to_atom("getline");

}

size_t File::open(string fn) { 
  file_name=fn ;
  fss.open(fn,  std::fstream::in | std::fstream::out | std::fstream::app);
  objects.push_back(shared_from_this());
  return objects.size()-1;
}

string File::getline() { 
  string line;
  std::getline(fss, line);
  return line;
}
void File::close() {
  fss.close();
}
    
Node::OpStatus File::apply(Node&process, Node &node, const Node::Vector& args) {
  MYLOGGER(trace_function, "File::op(Node&process, const Node& node, const Vector& args)", __func__, SLOG_FUNC_INFO);
  MYLOGGER_MSG(trace_function, "node: " + node._to_str(), SLOG_FUNC_INFO+30);
  MYLOGGER_MSG(trace_function, "args: " + Node::_to_str(args), SLOG_FUNC_INFO+30);

  cout << "args: " << Node::_to_str(args) << "\n";

  auto &method = args[0];

  if(method->_get_type() != Node::Type::Atom ){
    auto msg = "File apply :method needs to be an atom. :open, :close, :getline, etc!";
    cerr << msg << "\n";
    return {false, Node::create_error(Error::Type::Parse, msg)};
  }

  if(method->_get_integer() == atom_open) {
    cout << "file open " << atom_open << "\n";
  }
  if(method->_get_integer() == atom_close) {
    cout << "file close!\n";
  }
  if(method->_get_integer() == atom_getline) {
    cout << "file getline!\n";
  }

  return {true, Node::create()};
}