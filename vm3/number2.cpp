#include <iostream>
#include <variant>

class Number {
public:
    Number(int value) : data_(value) {}
    Number(float value) : data_(value) {}

    // Overload the addition operator
    Number operator+(const Number& other) const {
        return std::visit(AddVisitor{}, data_, other.data_);
    }

    // Overload the subtraction operator
    Number operator-(const Number& other) const {
        return std::visit(SubtractVisitor{}, data_, other.data_);
    }

    // Overload the multiplication operator
    Number operator*(const Number& other) const {
        return std::visit(MultiplyVisitor{}, data_, other.data_);
    }

    // Overload the division operator
    Number operator/(const Number& other) const {
        return std::visit(DivideVisitor{}, data_, other.data_);
    }

    std::variant<int, float> data_;
private:

    struct AddVisitor {
        template <typename T, typename U>
        auto operator()(const T& a, const U& b) const -> Number {
            return a + b;
        }
    };

    struct SubtractVisitor {
        template <typename T, typename U>
        auto operator()(const T& a, const U& b) const -> Number {
            return a - b;
        }
    };

    struct MultiplyVisitor {
        template <typename T, typename U>
        auto operator()(const T& a, const U& b) const -> Number {
            return a * b;
        }
    };

    struct DivideVisitor {
        template <typename T, typename U>
        auto operator()(const T& a, const U& b) const -> Number {
            if (b != 0) {
                return a / b;
            } else {
                // Handle division by zero
                std::cerr << "Error: Division by zero!" << std::endl;
                return Number(0);
            }
        }
    };
};

int main() {
    Number intNum(42);
    Number floatNum(3.14f);

    // Example usage
    Number result = intNum * floatNum;
    std::cout << "Result: " << std::get<float>(result.data_) << std::endl;

    return 0;
}

