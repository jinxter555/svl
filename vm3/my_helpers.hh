#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <regex>

//using namespace std;
std::vector<std::string> split_string(const std::string& istr, const std::string& delimiter);
std::string trim(const std::string& str, const std::string& whitespace = " \t") ;
std::string reduce(const std::string& str, const std::string& fill = " ", const std::string& whitespace = " \t");
std::string match(const std::string& line, const std::string& pattern) ;
std::string raw_to_escaped_string(const std::string& s);
