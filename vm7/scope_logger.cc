#include <map>
#include <vector>
#include "scope_logger.hh"
//fstream log_output;
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
  id_ = id_log++;

  set_current_level();
  
  auto color_code = colors[id_ % color_size].code;
  auto color = string("\033[") + to_string(color_code) + "m";


  char s[25]; sprintf(s, "%05d", id_);

  //out << color << s << ":" << current_level << " Enter: " << spacing()  << msg_in << endl; 
  out << color << s << " Enter: " << spacing()  << msg_in << endl; 
}

ScopeLogger::~ScopeLogger() {   
  if(!out.is_open()) return;
  char s[25]; sprintf(s, "%05d", id_);

  auto color_code = colors[id_ % color_size].code;
  auto color = string("\033[") + to_string(color_code) + "m";
  //auto color = string("\033[") + to_string(color_code) + "m" + to_string(color_code) + " ";


  out << color << s << " Exit:  " << spacing() << msg_out << endl; 
  const std::string reset("\033[0m");
  cout << reset;

  levels.pop_back();
}
void ScopeLogger::msg(const string& msg) {   
  if(!out.is_open()) return;
  char s[25]; sprintf(s, "%05d", id_);

  auto color_code = colors[id_ % color_size].code;
  auto color = string("\033[") + to_string(color_code) + "m";
  //auto color = string("\033[") + to_string(color_code) + "m" + to_string(color_code) + " ";


  out << color << s << " -msg-  " << spacing() << " " << msg << "\n";

  const std::string reset("\033[0m");
  cout << reset;
}


void ScopeLogger::set_current_level() {

  if(levels.size() == 0 )  {
    current_level = 0;
    levels.push_back(1);
  } else {
    current_level = levels.back();
    levels.push_back(current_level+1);
  }
}
string  ScopeLogger::spacing() {
  return string(current_level % color_size * 4 , ' ');
}