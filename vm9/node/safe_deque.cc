#include <map>
#include <iostream>
#include  "safe_deque.hh"
#include <thread>

#define SLOG_DEBUG_TRACE_FUNC
#include "scope_logger.hh"


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
//  std::cout << "pushback(). Current thread ID: " << std::this_thread::get_id() << std::endl;
  dq.push_back(move(ptr));
  cv.notify_one();
}

Node::ptr_U  SafeDeque::pop_back() {
  lock_guard<mutex> lock(mtx);
  auto &ptr = dq.front();
  dq.pop_back();
  return move(ptr);
}

void  SafeDeque::noop() { }

void  SafeDeque::printq() { 
  MYLOGGER(trace_function, "SafeDeque::printq()", __func__, SLOG_FUNC_INFO);
  access([](Node::DeQue& dq) {
    cout << "dq size: " <<  dq.size() << "\n";
    for(auto const& e : dq) { 
      //e->print();
      cout << e->_to_str() << "\n"; 
    }
  });
}
void  SafeDeque::swap(Node::DeQue &dq_in) { 
  //lock_guard<mutex> lock(mtx);
  unique_lock<mutex> lock(mtx);
  dq.swap(dq_in);
}
Node::Integer  SafeDeque::size() {
  return access([](Node::DeQue& dq) {
    return dq.size();
  });

}

void SafeDeque::wait() {
  unique_lock<mutex> lock(mtx);
 // std::cout << "wait(). Current thread ID: " << std::this_thread::get_id() << std::endl;
  cv.wait(lock, [this]{ return !dq.empty(); });
}
