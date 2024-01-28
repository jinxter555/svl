#include "my_helpers.hh"

using namespace std;
std::vector<std::string> 
split_string(const std::string& istr, const std::string& delimiter)
{
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
