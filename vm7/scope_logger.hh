#include <iostream>
#include <fstream>
#include <string>

#define DEBUG

using namespace std;

extern std::fstream log_output;
extern std::fstream trace_function;

class ScopeLogger {
private:
  int current_level;
  fstream &out;
  string msg_in, msg_out;
public:
  ScopeLogger( fstream &,  const string & , const string & );
  ~ScopeLogger() ;
  void msg(const string&);
  inline static int level = 0 ;
};


#ifdef DEBUG_TRACE_FUNC
#define MYLOGGER(x, y, z) ScopeLogger l_##x##_scope(x, y, z);
#define MYLOGGER_MSG(x, y) l_##x##_scope.msg(y);
#else
#define MYLOGGER(x, y, z)
#define MYLOGGER_MSG(x, y)
#endif