#pragma once
#include <iostream>
#include <string>
#include <vector>

//using namespace std;
std::vector<std::string> split_string(const std::string& istr, const std::string& delimiter);
std::string trim(const std::string& str, const std::string& whitespace = " \t") ;
std::string reduce(const std::string& str, const std::string& fill = " ", const std::string& whitespace = " \t");