#include "node.hh"
#include <fstream>
#include <vector>
using namespace std;
class File  : public std::enable_shared_from_this<File> {
public:
  using file_sptr = shared_ptr<File>;
  File();
  size_t open(string fn);
  string getline();
  void close();

  static Node::OpStatus apply(Node&process, Node &node, const Node::Vector& args) ;
  static void init();
  //Node::OpStatus attach(Node &class_node, const Node::Vector& args) ;
private:
  string file_name="";
  fstream fss;
  static vector<file_sptr> objects;
  static   Node::Integer atom_open, atom_close, atom_getline;

};