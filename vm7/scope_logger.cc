#include <map>
#include <vector>
#include "scope_logger.hh"
fstream log_output;
fstream trace_function;

typedef struct {
  string name;
  int code;
} color_t;

const vector<color_t> colors {
 { "Default", 39 },
// { "Black", 30 },
 { "Red", 31 },
 { "Green", 32 },
 { "Yellow", 33 },
 { "Blue", 34 },
 { "Magenta", 35 },
 { "Cyan", 36 },
 { "Light Gray", 38 },
 { "Dark Gray",90 },
 { "Light Red", 91 },
 { "Light Green", 92 },
 { "Light Yellow", 93 },
 { "Light Blue", 94 },
 { "Light Magenta", 95 },
 { "Light Cyan", 96 },
// { "White", 97 }
};
const int color_size = colors.size();

ScopeLogger::ScopeLogger( fstream &o,  string const & mi, string const& mo )
  : out(o), msg_in(mi), msg_out(mo) {   
  if(!out.is_open()) return;
  current_level = level++;
  
  auto color_code = colors[current_level % color_size].code;
  auto color = string("\033[") + to_string(color_code) + "m";
  //auto color = string("\033[") + to_string(color_code) + "m" + to_string(color_code) + " ";

  char s[25]; sprintf(s, "%05d", current_level);

  out << color  << s << " Enter: " << msg_in << endl; 
}

ScopeLogger::~ScopeLogger() {   
  if(!out.is_open()) return;
  char s[25]; sprintf(s, "%05d", current_level);

  auto color_code = colors[current_level % color_size].code;
  auto color = string("\033[") + to_string(color_code) + "m";
  //auto color = string("\033[") + to_string(color_code) + "m" + to_string(color_code) + " ";

  out << color << s << " Exit: " << msg_out << endl; 
  const std::string reset("\033[0m");
  cout << reset;


}
void ScopeLogger::msg(const string& msg) {   
  if(!out.is_open()) return;
  char s[25]; sprintf(s, "%05d", current_level);

  auto color_code = colors[current_level % color_size].code;
  auto color = string("\033[") + to_string(color_code) + "m";
  //auto color = string("\033[") + to_string(color_code) + "m" + to_string(color_code) + " ";

  out << color << s << " " << msg << "\n";

  const std::string reset("\033[0m");
  cout << reset;
}

