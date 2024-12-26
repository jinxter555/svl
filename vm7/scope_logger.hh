#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#define DEBUG

using namespace std;

extern std::fstream log_output;
extern std::fstream trace_function;

class ScopeLogger {
private:
  int id_, current_level;

  fstream &out;
  string msg_in, msg_out;
  int num_spaces=0;
  inline static vector <int> levels;
public:
  ScopeLogger( fstream &,  const string & , const string & );
  ~ScopeLogger() ;
  void msg(const string&);
  inline static int id_log = 0 ;
  void set_current_level();
  string spacing();
};


#ifdef DEBUG_TRACE_FUNC
#define MYLOGGER(x, y, z) ScopeLogger l_##x##_scope(x, y, z);
#define MYLOGGER_MSG(x, y) l_##x##_scope.msg(y);
#else
#define MYLOGGER(x, y, z)
#define MYLOGGER_MSG(x, y)
#endif