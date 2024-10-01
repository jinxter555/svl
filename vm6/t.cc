
#include <iostream>
#include <variant>
#include <memory>

class MyClass {
public:
    using NestedVariant = std::variant<int, float, std::unique_ptr<MyClass>>;

    void setValue(const NestedVariant& value) {
        data = value;
    }

    void printValue() const {
        std::visit( {
            if constexpr (std::is_same_v<std::decay_t<decltype(arg)>, std::unique_ptr<MyClass>>) {
                if (arg) {
                    std::cout << "MyClass instance" << std::endl;
                } else {
                    std::cout << "nullptr" << std::endl;
                }
            } else {
                std::cout << arg << std::endl;
            }
        }, data);
    }

private:
    NestedVariant data;
};

int main() {
    MyClass obj;
    obj.setValue(10); // Set int value
    obj.printValue(); // Output: 10

    obj.setValue(3.14f); // Set float value
    obj.printValue(); // Output: 3.14

    obj.setValue(std::make_unique<MyClass>()); // Set unique_ptr<MyClass> value
    obj.printValue(); // Output: MyClass instance

    obj.setValue(std::unique_ptr<MyClass>(nullptr)); // Set unique_ptr<MyClass> to nullptr
    obj.printValue(); // Output: nullptr

    return 0;
}

