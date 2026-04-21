#include <map>
#include <iostream>
#include  "safe_deque.hh"


SafeDeque::SafeDeque() {}

template <typename Fun>
auto SafeDeque::access(Fun fun) {
  lock_guard<mutex> lock(mtx);
  return fun(dq);
}

template <typename Fun>
auto SafeDeque::access(Fun fun) const {
  lock_guard<mutex> lock(mtx);
  return fun(dq);
}

void  SafeDeque::push_front(Node::ptr_U ptr) {
  lock_guard<mutex> lock(mtx);
  dq.push_front(move(ptr));
}

Node::ptr_U  SafeDeque::pop_front() {
  lock_guard<mutex> lock(mtx);
  auto &ptr = dq.front();
  dq.pop_front();
  return move(ptr);
}

void  SafeDeque::push_back(Node::ptr_U ptr) {
  lock_guard<mutex> lock(mtx);
  dq.push_back(move(ptr));
}

Node::ptr_U  SafeDeque::pop_back() {
  lock_guard<mutex> lock(mtx);
  auto &ptr = dq.front();
  dq.pop_back();
  return move(ptr);
}

void  SafeDeque::noop() { }
void  SafeDeque::printq() { 
  access([](Node::DeQue& dq) {
    for(auto const& e : dq) { 
      cout << e->_to_str() << "\n"; 
    }
});

}

map<int, SafeDeque> a1() {
   map<int, SafeDeque> ipc;
   ipc[0].push_back(Node::create(123));
   ipc[1].push_back(Node::create(123));
   return ipc;


}