#include "scope_logger.hh"
extern std::fstream LogOutput;
ScopeLogger::ScopeLogger( fstream &o,  string const & msg ) : out(o), msg(msg) {   
    out << "Enter: " << msg << endl; 
  }
ScopeLogger::~ScopeLogger() {   
    out << "Exit:  " << msg << endl; 
  }

