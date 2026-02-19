#include "node.hh"
#include <fstream>
#include <vector>
using namespace std;

class File  {
public:
  using file_sptr = shared_ptr<File>;
  File();
  void open(string fn);
  string getline();
  void close();
  bool eof();

  static Node::OpStatus apply(Node&process, Node &node, const Node::Vector& args) ;
  static Node::OpStatus apply(Node&process, Node::Map &object, const Node::Vector& args) ;
  static void init();
  //Node::OpStatus attach(Node &class_node, const Node::Vector& args) ;
private:
  string filename;
  fstream fss;
  static vector<file_sptr> file_objects;
  static   Node::Integer atom_open, atom_close, atom_getline, atom_eof;

};