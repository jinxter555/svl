#include "tree.hh"
using namespace std;


int main() {
  Tree* my_tree = new Tree();
  my_tree->add_node({"key1"}, string("workjob"));
  //my_tree->add_node({"key1", "key2"}, 1);
  my_tree->add_node({"key1", "key2"}, 12345);
  my_tree->add_node({"key1", "key3"}, string("hello"));
  my_tree->add_node({"key4", "key5"}, 3.145);

  my_tree->set_node({"key1"}, string("workjob2"));
  my_tree->set_node({"key1"}, string("workjob3"));

  //my_tree->set_node({"key1", "key2"}, 2.1);
  auto node1a = my_tree->get_node({"key1", "key2"});
  node1a->print_data(); cout << "\n";
  auto node1b = my_tree->get_node({"key1", "key2"});
  auto node1c = my_tree->get_node({"key1"});
  cout << "v at key1: " << any_cast<string>(node1c->get_data()) << endl;
  //cout << "v at key1/key2: " << any_cast<double>(node1a->get_data()) << endl;
  cout << "\n";

  return 0;
}
