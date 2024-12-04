#include <iostream>
#include <fstream>
#include <string>

#define DEBUG

using namespace std;

extern fstream LogOutput;

class ScopeLogger {
private:
  fstream &out;
  string msg;
public:
  ScopeLogger( fstream &o,  string const & msg );
  ~ScopeLogger() ;
};


#ifdef DEBUG_TRACE_FUNC
#define MYLOGGER(x, y) ScopeLogger l_##x##_scope(x, y);
#else
#define MYLOGGER(x, y)
#endif