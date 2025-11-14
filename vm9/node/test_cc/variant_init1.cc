#include <iostream>
#include <variant>
#include <vector>
#include <memory>

// Define a variant type that can hold either an int or a unique_ptr to int
using IntVariant = std::variant<int, std::unique_ptr<int>>;

int main() {
    // Initialize the vector with plain ints
    std::vector<IntVariant> values = {1, 2, 3};

    // Add a unique_ptr<int> to the vector
    values.emplace_back(std::make_unique<int>(42));

    // Print the contents of the vector
    for (const auto& val : values) {
        std::visit([](const auto& v) {
            if constexpr (std::is_same_v<decltype(v), int>) {
                std::cout << "int: " << v << "\n";
            } else {
                std::cout << "unique_ptr<int>: " << *v << "\n";
            }
        }, val);
    }

    return 0;
}

