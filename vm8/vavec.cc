#include <iostream>
#include <variant>
#include <vector>

int main() {
  // Declare a variant that can hold either an int or a vector<int>
  std::variant<int, std::vector<int>> my_variant;

  // Assign an integer value to the variant
  my_variant = 10;

  // Check the type of the value held by the variant
  if (std::holds_alternative<int>(my_variant)) {
    std::cout << "my_variant holds an int: " << std::get<int>(my_variant) << std::endl;
  }

  // Assign a vector of integers to the variant
  auto l = std::vector<int>{1, 2, 5};
  my_variant = std::vector<int>{1, 2, 3};
  my_variant = move(l);
  

  // Check the type of the value held by the variant and access it
  if (std::holds_alternative<std::vector<int>>(my_variant)) {
    std::cout << "my_variant holds a vector: ";
    for (int i : std::get<std::vector<int>>(my_variant)) {
      std::cout << i << " ";
    }
    std::cout << std::endl;
  }

  return 0;
}