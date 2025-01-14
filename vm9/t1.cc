#include <iostream>
#include <vector>
#include <utility>

class MyVector {
public:
    MyVector(size_t size) : data_(size) {}

    // Overloaded [] operator for read-only access
    const int& operator[](size_t index) const {
        return data_[index]; 
    }

    // Overloaded [] operator for read-write access
    int& operator[](size_t index) {
        return const_cast<int&>(std::as_const((*this)[index])); 
    }
    int size() { return data_.size(); }

private:
    std::vector<int> data_;
};

int main() {
    MyVector vec(5);

    // Read-only access
    for (size_t i = 0; i < vec.size(); ++i) {
        std::cout << vec[i] << " "; 
    }
    std::cout << std::endl;

    // Read-write access
    vec[2] = 10; 
    std::cout << vec[2] << std::endl; 

    return 0;
}
