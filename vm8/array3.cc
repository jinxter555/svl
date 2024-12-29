#include <iostream>
#include <memory>
#include <vector>

using namespace std;

template <typename T>
class List {
private:
    unique_ptr<vector<T>> ptr_;
public:
    List(unique_ptr<vector<T>> ptr) 
      : ptr_(move(ptr)) {}

    T& operator[](size_t index) {
        return (*ptr_)[index];
    }

    const T& operator[](size_t index) const {
        return (*ptr_)[index];
    }

};

int main() {
    auto vec = make_unique<vector<int>>();
    vec->push_back(1);
    vec->push_back(2);
    vec->push_back(3);

    List<int> l1(move(vec));

    cout << l1[0] << endl; // Outputs 1
    cout << l1[1] << endl; // Outputs 2

    l1[2] = 10;
    cout << l1[2] << endl; // Outputs 10

    return 0;
}
