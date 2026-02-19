#include "io_file.hh"
#include "lang.hh"
#define SLOG_DEBUG_TRACE_FUNC
#include "scope_logger.hh"

vector<File::file_sptr> File::file_objects={};


Node::Integer File::atom_open, File::atom_close, File::atom_getline, File::atom_eof;

File::File() {}

//------------------------------------------------------------------------
void File::init() {
  atom_open = Lang::str_to_atom("open");
  atom_close = Lang::str_to_atom("close");
  atom_getline = Lang::str_to_atom("getline");
  atom_eof = Lang::str_to_atom("eof");
}

void File::open(string fn) { 
  filename=fn ;
  fss.open(fn,  std::fstream::in );
  if(!fss) {
    cerr << "Can't open file!\n";
  }
}

string File::getline() { 
  string line;
  std::getline(fss, line);
  return line;
}
void File::close() {
  fss.close();
}
bool File::eof() {
  return fss.eof();
}
    
//------------------------------------------------------------------------
Node::OpStatus File::apply(Node&process, Node &object_node, const Node::Vector& args) {
  MYLOGGER(trace_function, "File::apply(Node&process, Node& object, const Vector& args)", __func__, SLOG_FUNC_INFO);
  MYLOGGER_MSG(trace_function, "object_node: " + object_node._to_str(), SLOG_FUNC_INFO+30);
  MYLOGGER_MSG(trace_function, "args: " + Node::_to_str(args), SLOG_FUNC_INFO+30);

  try {
    auto &object =object_node._get_map_ref();
    return apply(process, object, args);
  } catch(...) {
    //auto msg = "1File object is not a Node::Map!";
    auto msg = "File object is not a Node::Map or applying method not successful!";
    cerr << msg << "\n";
    return {false, Node::create_error(Error::Type::Parse, msg)};
  }

}
Node::OpStatus File::apply(Node&process, Node::Map &lisp_object, const Node::Vector& args) {
  MYLOGGER(trace_function, "File::apply(Node&process, Node& object, const Vector& args)", __func__, SLOG_FUNC_INFO);
  MYLOGGER_MSG(trace_function, "args: " + Node::_to_str(args), SLOG_FUNC_INFO+30);

  cout << "args: " << Node::_to_str(args) << "\n";
  //return {true, Node::create()};
  Node::Integer  id;

  if(args.size() < 1) 
      return {false, Node::create_error(Error::Type::Unknown, "need a file :method, :open,:close etc...")};


  auto &method = args[0];
  if(method->_get_type() != Node::Type::Atom ){
    auto msg = "File apply :method needs to be an atom. :open, :close, :getline, etc!";
    cerr << msg << "\n";
    return {false, Node::create_error(Error::Type::Parse, msg)};
  }

  if(method->_get_integer() == atom_open) {
    if(args.size() < 2) return {false, Node::create_error(Error::Type::Parse, "need filename")};
    auto filename = args[1]->_to_str();

    cout << "opening " << filename << "\n";
    auto file_obj = make_shared<File>();
    file_objects.push_back(file_obj);

    Node::Integer id = file_objects.size() -1;
    file_obj->open(filename);
    lisp_object[CC_OBJ_ID] = Node::create(id);
    return {true, Node::create(true)};

  }

  // make sure cc obj id exist
  if (lisp_object.find(CC_OBJ_ID) == lisp_object.end()) {
    auto msg = "no CC_OBJ_ID or has been deleted or file has been closed!";
    return {false, Node::create_error(Error::Type::Unknown, msg)};
  }

  try {
    id  = lisp_object[CC_OBJ_ID]->_get_integer();
  } catch(...) {
    auto msg = "no CC_OBJ_ID or has been deleted or file has been closed!";
    return {false, Node::create_error(Error::Type::Unknown, msg)};
  }

  if(method->_get_integer() == atom_close) {
    auto file_obj = file_objects[id];
    file_obj->close();
    file_objects[id] = nullptr;
    lisp_object.erase(CC_OBJ_ID);
    return {true, Node::create(true)};
  }

  if(method->_get_integer() == atom_getline) {
    auto file_obj = file_objects[id];
    if(file_obj->eof()) {
      cerr << "end of file!\n";
      return {true, Node::create()};
    }
    return {true, Node::create( file_obj->getline())};
  }
  if(method->_get_integer() == atom_eof) {
    auto file_obj = file_objects[id];
    if(file_obj->eof()) {
      return {true, Node::create(true)};
    }
    return {true, Node::create(false)};
    //return {true, Node::create(eof())};
  }

  return {true, Node::create()};
}