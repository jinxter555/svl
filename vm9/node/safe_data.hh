#ifndef SAFE_DATA_HH
#define  SAFE_DATA_HH

#include <mutex>

using namespace std;

template <typename T>
class SafeData {
private:
  mutable mutex mtx;
  T data;
public:
  template <typename... Args>
  SafeData(Args&&... args) : data(forward<Args>...) {}

  template <typename Func>
  auto access(Func fun) {
    lock_guard<mutex> lock(mtx);
    return func(data);
  }

  template <typename Func>
  auto access(Func fun) const {
    lock_guard<mutex> lock(mtx);
    return func(data);
  }


};

#endif