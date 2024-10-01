#include <iostream>
#include <memory>
#include <variant>

class Node {
public:
    using ValueType = std::variant<int, std::unique_ptr<Node>>;

    Node(int value) : value_(value) {}
    Node(std::unique_ptr<Node> value) : value_(std::move(value)) {}

    void setLeft(std::unique_ptr<Node> left) {
        left_ = std::move(left);
    }

    void setRight(std::unique_ptr<Node> right) {
        right_ = std::move(right);
    }

    ValueType getValue() const {
        return std::visit(GetValueVisitor(), value_);
    }

    void print() const {
        std::visit(PrintVisitor(), value_);
        if (left_) {
            std::cout << " Left: ";
            left_->print();
        }
        if (right_) {
            std::cout << " Right: ";
            right_->print();
        }
    }

private:
    ValueType value_;
    std::unique_ptr<Node> left_;
    std::unique_ptr<Node> right_;

    struct PrintVisitor {
        void operator()(int value) const {
            std::cout << value << std::endl;
        }
        void operator()(const std::unique_ptr<Node>& node) const {
            if (node) {
                node->print();
            }
        }
    };

    struct GetValueVisitor {
        ValueType operator()(int value) const {
            return value;
        }
        ValueType operator()(const std::unique_ptr<Node>& node) const {
            if (node) {
                return std::make_unique<Node>(*node);
            }
            return 0; // Return a default value if node is null
        }
    };
};

int main() {
    auto root = std::make_unique<Node>(10);
    auto leftChild = std::make_unique<Node>(5);
    auto rightChild = std::make_unique<Node>(15);
    auto nestedNode = std::make_unique<Node>(std::make_unique<Node>(20));

    root->setLeft(std::move(leftChild));
    root->setRight(std::move(rightChild));
    root->setRight(std::move(nestedNode));

    root->print(); // Output: 10 Left: 5 Right: 20

    // Example of using getValue
    auto value = root->getValue();
    /*
    std::visit( { 
        if constexpr (std::is_same_v<std::decay_t<decltype(arg)>, int>) {
            std::cout << "Value: " << arg << std::endl;
        } else {
            std::cout << "Nested Node Value: ";
            arg.print();
        }
    }, value);
    */

    return 0;
}

