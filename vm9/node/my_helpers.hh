#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <deque>
#include <regex>

using namespace std;
std::vector<std::string> split_string(const std::string& istr, const std::string& delimiter);
std::list<std::string> split_string_list(const std::string& istr, const std::string& delimiter);
std::deque<std::string> split_string_deque(const std::string& istr, const std::string& delimiter);
std::string trim(const std::string& str, const std::string& whitespace = " \t") ;
std::string reduce(const std::string& str, const std::string& fill = " ", const std::string& whitespace = " \t");
std::string match(const std::string& line, const std::string& pattern) ;
std::string raw_to_escaped_string(const std::string& s);
char escaped_char(const char& c);

string add_vector_string(const vector<string> &vs, const string& delimiter=" ");
string concat_vector_string(const vector<string> &vs, const string& delimiter=" ");

std::string extractClassName(const std::string& prettyFunction);

string  _to_str_ext(const vector<string>& keys) ;
string  _to_str_ext(const list<string>& keys) ;
string  _to_str_ext(const deque<string>& keys) ;

string join_str(const vector<std::string>& elements, const string& delimiter=" ");

#define __CLASS_NAME__ extractClassName(__PRETTY_FUNCTION__)
