#include "scope_logger.hh"
fstream log_output;
fstream trace_function;

ScopeLogger::ScopeLogger( fstream &o,  string const & mi, string const& mo )
  : out(o), msg_in(mi), msg_out(mo) {   
    if(!out.is_open()) return;
    current_level = level++;
    char s[25]; sprintf(s, "%05d", current_level);
    out << s << " Enter: " << msg_in << endl; 
  }

ScopeLogger::~ScopeLogger() {   
    if(!out.is_open()) return;
    char s[25]; sprintf(s, "%05d", current_level);
    out << s << " Exit: " << msg_out << endl; 
  }
void ScopeLogger::msg(const string& msg) {   
    if(!out.is_open()) return;
    char s[25]; sprintf(s, "%05d", current_level);
    out << s << " " << msg << "\n";
  }

