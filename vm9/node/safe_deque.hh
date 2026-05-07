#include <mutex>
#include "node.hh"

class SafeDeque {
private:
  Node::DeQue dq;
  mutable mutex mtx;
public:
  SafeDeque();
  template <typename Fun> auto access(Fun fun);
  template <typename Fun> auto access(Fun fun) const;

  Node::ptr_U pop_front();
  void push_front(Node::ptr_U);
  
  Node::ptr_U pop_back();
  void push_back(Node::ptr_U);
  void swap(Node::DeQue &dq);

  void printq();
  Node::Integer size() ;

  void noop();
};