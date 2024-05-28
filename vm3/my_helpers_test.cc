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

int main() {
  auto vs1=split_string("Module1function", ".");
  auto vs2=split_string("Module2.function", ".");
  cout << vs1.size() << "\n";
  cout << vs2.size() << "\n";
}
