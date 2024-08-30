#include "number.hh"
int main() {
    Number intNum(42);
    Number floatNum(3.14f);

    // Example usage
    Number result = intNum * floatNum;
    std::cout << "Result: " << std::get<float>(result.getData()) << std::endl;
    std::cout << "Result: ";  result.printData() ;
    std::cout << "type: " << result.getCurrentType() << std::endl;
    std::cout << "type: " << intNum.getCurrentType() << std::endl;
    return 0;
}
