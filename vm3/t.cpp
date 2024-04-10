#include <iostream>
#include <map>
#include <string>
#include <functional>

// Define some example functions that take a string argument
void printHello(const std::string& message) {
  std::cout << message << std::endl;
}

void printGoodbye(const std::string& message) {
  std::cout << message << std::endl;
}

int main() {
  // Create a map of strings to function pointers
  std::map<std::string, std::function<void(const std::string&)>> functionMap;

  // Add functions to the map
  functionMap["hello"] = printHello;
  functionMap["goodbye"] = printGoodbye;

  // Get user input
  std::string input, message;
  std::cout << "Enter a command (hello or goodbye): ";
  std::getline(std::cin, input);

  std::cout << "Enter a message: ";
  std::getline(std::cin, message);

  // Find the function pointer in the map
  auto it = functionMap.find(input);

  // Check if the command exists
  if (it != functionMap.end()) {
    // Call the function using the function pointer, passing the message
    it->second(message);
  } else {
    std::cout << "Invalid command." << std::endl;
  }

  return 0;
}
