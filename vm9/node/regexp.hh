#include <iostream>
#include <string>
#include <regex>
#include <vector>
#include <stdexcept>
#include "node.hh"

using namespace std;
class Regexp {
private:
  regex pattern_;
  string pattern_string_;
  vector<string> matched;
public:
  explicit 
  Regexp(const string& pattern_str, regex_constants::syntax_option_type flags = regex_constants::ECMAScript) ;
  bool match_full(const string& text) const ;
  bool match_part(const string& text) const ;

  vector<string> extract_full_vs(const string& text) const ;
  vector<string> extract_part_vs(const string& text) const ;

  Node::Vector extract_full(const string& text) const ;
  Node::Vector extract_part(const string& text) const ;

  string replace(const string&text, const string&replacement) const ;
  string get_pattern_string() const ;

  static Node::OpStatus apply(Node&process, Node &node, const Node::Vector& args) ;
  static Node::OpStatus apply_obj(Node&process, Node::Map &object, const Node::Vector& args) ;

  static Node::Integer create_and_register(
    const string& pattern_str, 
    regex_constants::syntax_option_type flags );
   // regex_constants::syntax_option_type flags = regex_constants::ECMAScript);

  using re_uptr = unique_ptr<Regexp>;
  static vector<re_uptr>  re_objects;
};