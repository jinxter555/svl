#include "my_helpers.hh"

std::vector<std::string> 
split_string(const std::string& istr, const std::string& delimiter) {
    std::vector<std::string> result;
    std::string str = istr;
    size_t pos = 0;

    while ((pos = str.find(delimiter)) != std::string::npos) {
        result.push_back(str.substr(0, pos));
        str.erase(0, pos + delimiter.length());
    }
    // Add the last remaining substring
    result.push_back(str);

    return result;
}

std::string trim(const std::string& str, const std::string& whitespace ){
    const auto strBegin = str.find_first_not_of(whitespace);
    if (strBegin == std::string::npos)
        return ""; // no content

    const auto strEnd = str.find_last_not_of(whitespace);
    const auto strRange = strEnd - strBegin + 1;

    return str.substr(strBegin, strRange);
}

std::string reduce(const std::string& str, const std::string& fill , const std::string& whitespace ) {
    // trim first
    auto result = trim(str, whitespace);

    // replace sub ranges
    auto beginSpace = result.find_first_of(whitespace);
    while (beginSpace != std::string::npos)
    {
        const auto endSpace = result.find_first_not_of(whitespace, beginSpace);
        const auto range = endSpace - beginSpace;

        result.replace(beginSpace, range, fill);

        const auto newStart = beginSpace + fill.length();
        beginSpace = result.find_first_of(whitespace, newStart);
    }

    return result;
}

std::string match(const std::string& line, const std::string& pattern) {
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

std::string raw_to_escaped_string(const std::string& s) {
    std::string result;
    std::string::const_iterator it = s.begin();

    while (it != s.end()) {
        char c = *it++;
        if (c == '\\' && it != s.end()) {
            switch (*it++) {
                case '\\':
                    result += '\\'; // Backslash
                    break;
                case 'n':
                    result += '\n'; // Newline
                    break;
                case 't':
                    result += '\t'; // Tab
                    break;
                case '\"':
                    result += '\"'; // Double quote
                    break;
                case '\'':
                    result += '\''; // Single quote
                    break;
                case 'r':
                    result += '\r'; // Carriage return
                    break;
                case 'b':
                    result += '\b'; // Backspace
                    break;
                case 'f':
                    result += '\f'; // Form feed
                    break;
                case 'a':
                    result += '\a'; // Alert (bell)
                    break;
                case 'v':
                    result += '\v'; // Vertical tab
                    break;
                case '?':
                    result += '\?'; // Question mark
                    break;
                case '0':
                    result += '\0'; // Null character
                    break;
                // Add other escape sequences as needed
                default:
                    // Invalid escape sequence - keep the character unchanged
                    result += c;
            }
        } else {
            result += c; // No escape sequence, keep the character as is
        }
    }

    return result;
}

string add_vector_string(const vector<string> &vs, const string& delimiter) {
  string result="[";
  int i, s=vs.size();
  for(i=0; i<s-1; i++) {
    result = result  + vs[i] + delimiter ;
  }
  result = result + vs[i]+ "]";
  return result;
}

string concat_vector_string(const vector<string> &vs, const string& delimiter) {
  string result="";
  int i, s=vs.size();
  for(i=0; i<s-1; i++) {
    result = result  + vs[i] + delimiter ;
  }
  result = result + vs[i];
  return result;
}