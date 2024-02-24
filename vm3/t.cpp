#include <iostream>
#include <string>
#include <regex>

std::string match_and_return_rest(const std::string& line, const std::string& pattern) {
  std::smatch match;
  std::regex regex(pattern);

  if (std::regex_search(line, match, regex)) {
    // Match found, return the rest of the line after the match
    return line.substr(match.position() + match.str(0).size());
  } else {
    // No match found, return an empty string
    return "";
  }
}

int main() {
  std::string line1 = "\\print line world";
  std::string line2 = "\\print program information";
  std::string pattern = "\\print";

  std::string rest_of_line1 = match_and_return_rest(line1, pattern);
  std::string rest_of_line2 = match_and_return_rest(line2, pattern);

  std::cout << "Line 1: " << rest_of_line1 << std::endl;  // Output: This is a line with
  std::cout << "Line 2: " << rest_of_line2 << std::endl;  // Output: 
  return 0;
}
