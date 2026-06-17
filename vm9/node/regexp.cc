#include <iostream>
#include <string>
#include <regex>
#include <vector>
#include <stdexcept>
#include "regexp.hh"
#include "lang.hh"
#include "my_helpers.hh"

#define SLOG_DEBUG_TRACE_FUNC
#include "scope_logger.hh"

vector<Regexp::re_uptr>  Regexp::re_objects={};

Regexp::Regexp(const string& pattern_str, regex_constants::syntax_option_type flags)
      : pattern_string_(pattern_str) { 
    try {
      pattern_ = regex(pattern_str, flags);
    } catch(const regex_error&e) {
      throw runtime_error("Regex Compilation Error: " + 
          string(e.what()) + " on pattern: " + pattern_str);
    }
}

bool Regexp::match_full(const string& text) const {
  return regex_match(text, pattern_);
}
bool Regexp::match_part(const string& text) const {
    return regex_search(text, pattern_);
}

Node::Vector Regexp::extract_full(const string& text) const {
  Node::Vector results;
  auto rvs = extract_full_vs(text);
  for(auto&e : rvs ){
    results.push_back(Node::create(e));
  }
  return results;
}

Node::Vector Regexp::extract_part(const string& text) const {
  Node::Vector results;
  auto rvs = extract_part_vs(text);
  for(auto&e : rvs ){
    results.push_back(Node::create(e));
  }
  return results;
}

vector<string> Regexp::extract_full_vs(const string& text) const {
  smatch matches;
  vector<string> results;
  if(regex_match(text, matches, pattern_)) {
    for(const auto& match : matches) {
      results.push_back(match.str());
    }
  }
  return results;
}

vector<string> Regexp::extract_part_vs(const string& text) const {
  smatch matches;
  vector<string> results;
  if(regex_search(text, matches, pattern_)) {
    for(const auto& match : matches) {
      results.push_back(match.str());
    }
  }
  return results;
}

string Regexp::replace(const string&text, const string&replacement) const {
  return regex_replace(text, pattern_, replacement);
}

string Regexp::get_pattern_string() const {
  return pattern_string_;
}


Node::OpStatus Regexp::apply(Node&process, Node &object_node, const Node::Vector& args) {
  MYLOGGER(trace_function, "Regexp::apply(Node&process, Node& object, const Vector& args)", __func__, SLOG_FUNC_INFO);
  MYLOGGER_MSG(trace_function, "object_node: " + object_node._to_str(), SLOG_FUNC_INFO+30);
  MYLOGGER_MSG(trace_function, "args: " + Node::_to_str(args), SLOG_FUNC_INFO+30);

  try {
    auto &object = object_node._get_map_ref();
    return apply_obj(process, object, args);

  } catch(...) {
    //auto msg = "1File object is not a Node::Map!";
    auto msg = "SocketClient object is not a Node::Map or applying method not successful!";
    cerr << msg << "\n";
    return {false, Node::create_error(Error::Type::Parse, msg)};
  }
}

Node::OpStatus Regexp::apply_obj(Node&process, Node::Map &lisp_object, const Node::Vector& args) {
  MYLOGGER(trace_function, "Regexp::apply_obj(Node&process, Map& lisp_object, const Vector& args)", __func__, SLOG_FUNC_INFO);
  MYLOGGER_MSG(trace_function, "args: " + Node::_to_str(args), SLOG_FUNC_INFO+30);

  Node::Integer id;
  if(args.size() < 1) 
    return {false, Node::create_error(Error::Type::Unknown, "need a RegExp :method, :open, :close etc...")};

  auto &method = args[0];

  if(method->_get_type() != Node::Type::Atom ){
    auto msg = "RegExp apply :method needs to be an atom. :server, :client, :getline, etc!";
    cerr << msg << "\n";
    return {false, Node::create_error(Error::Type::Parse, msg)};
  }
  auto atom_cc_fun_name = method->_get_integer();


  //cout << "SS apply,pass 1!\n";
  //cout << "lisp_object: " <<  Node::_to_str(lisp_object) << "\n";
  if(atom_cc_fun_name  == Lang::Atom::initialize) {
    //id =  Regexp::create_and_register();
    regex_constants::syntax_option_type flags;
    //flags = regex_constants::ECMAScript | regex_constants::icase;
    flags = regex_constants::icase;
    //flags = regex_constants::ECMAScript ;
    Node::Integer atom_match_type=0;


    //cout << "init(): " <<  Node::_to_str(args) << "\n";
    if(args.size() < 2) return {false, Node::create_error(Error::Type::Parse, "need pattern and flag")};
    auto pattern = args[1]->_to_str();

    if(args[2]->_get_type() == Node::Type::Atom) {
      cout << "Atom args2[]: " << args[2]->_to_str() << "\n";
      atom_match_type = args[2]->_get_integer();
    } else if(args[2]->_get_type() == Node::Type::Vector) {
        cout << "Vector args[] " << *args[2] << "\n";
    }
    if(atom_match_type == Lang::Atom::icase)
      flags |= regex_constants::icase;
    
    cout << "pattern: " << pattern;
    cout << "args2[]: " << args[2]->_to_str() << "\n";
    id = create_and_register(pattern, flags);
    lisp_object[CC_OBJ_ID]  = Node::create(id);
    return {true, Node::create(id)};
  }


  try {
    id  = lisp_object[CC_OBJ_ID]->_get_integer(); //cout << "cc_obj_id: " << id << "\n";
  } catch(...) {
    auto msg = "no CC_OBJ_ID or has been deleted or file has been closed!";
    cerr << "error: " <<  msg << "\n";
    return {false, Node::create_error(Error::Type::Unknown, msg)};
  }
  auto &re_obj = re_objects[id];

  if(atom_cc_fun_name  == Lang::Atom::match) {
    if(args.size() < 3) return {false, Node::create_error(Error::Type::Parse, "match [:full|:part] and text")};
    auto match_type = args[1]->_get_integer();
    auto text =  args[2]->_get_str();
    if(match_type == Lang::Atom::full) {
    cout << "match full\n";
      auto b = re_obj->match_full(text);
      return {true, Node::create(b)};

    } else if(match_type == Lang::Atom::part) {
      cout << "match part\n";
      auto b = re_obj->match_part(text);
      return {true, Node::create(b)};

    } else {

    }

  }
  if(atom_cc_fun_name  == Lang::Atom::extract) {
    if(args.size() < 3) return {false, Node::create_error(Error::Type::Parse, "extract [:full|:part] and text")};
    auto match_type = args[1]->_get_integer();
    auto text =  args[2]->_get_str();
    if(match_type == Lang::Atom::full) {
    cout << "match full\n";
      auto group = re_obj->extract_full(text);
      //cout << "found group: " << _to_str_ext(group);
      lisp_object["FOUND"] =  Node::create(move(group));
      return {true, Node::create(Lang::Atom::ok, Node::Type::Atom)};

    } else if(match_type == Lang::Atom::part) {
      cout << "extract part\n";
      auto group = re_obj->extract_part(text);
      lisp_object["FOUND"] =  Node::create(move(group));
      //cout << "found group: " << _to_str_ext(group);
      return {true, Node::create(Lang::Atom::ok, Node::Type::Atom)};

    } else {

    }


  }




}
Node::Integer  Regexp::create_and_register(
  const string& pattern_str, 
  regex_constants::syntax_option_type flags) {

  auto uptr = make_unique<Regexp>(pattern_str, flags);

  Node::Integer id =re_objects.size();
  re_objects.push_back(move(uptr));
  return id;
}