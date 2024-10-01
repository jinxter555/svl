#include <iostream>
#include <memory>
#include <variant>

// Define a Node class for the binary tree
class Node {
public:
    // Variant to hold either an int or a unique_ptr to another Node
    using NodeType = std::variant<int, std::unique_ptr<Node>>;

    // Constructor for int value
    Node(int value) : data(value) {}

    // Constructor for unique_ptr<Node>
    Node(std::unique_ptr<Node> left, std::unique_ptr<Node> right)
        : data(nullptr), left(std::move(left)), right(std::move(right)) {}

    // Function to print the node's data
    void print() const {
        if (std::holds_alternative<int>(data)) {
            std::cout << "int: " << std::get<int>(data) << std::endl;
        } else {
            std::cout << "Node with children:" << std::endl;
            if (left) left->print();
            if (right) right->print();
        }
    }

    // Left and right children
    NodeType data;
    std::unique_ptr<Node> left;
    std::unique_ptr<Node> right;
};

int main() {
    // Create leaf nodes
    auto leftLeaf = std::make_unique<Node>(42);
    auto rightLeaf = std::make_unique<Node>(99);

    // Create a root node with left and right children
    auto root = std::make_unique<Node>(std::move(leftLeaf), std::move(rightLeaf));

    // Print the tree
    root->print(); // Output: Node with children, int: 42, int: 99

    return 0;
}

