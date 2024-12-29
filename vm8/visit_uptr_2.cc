#include <iostream>
#include <string>
#include <variant>

int main() {
    std::variant<int, double, std::string> v = 10;

    std::visit(
        [](auto&& arg) { 
            std::cout << "Generic handler: " << arg << std::endl; 
        },
        v
    );

    v = 3.14;
    struct overload {
      void operator()(int i) { std::cout << "Int handler: " << i << std::endl; };
      void operator()(double d) { std::cout << "Double handler: " << d << std::endl; };
      //void oeprator()(string& s) { std::cout << "String handler: " << s << std::endl; };
    };

    std::visit(overload{}, v);

    return 0;
}