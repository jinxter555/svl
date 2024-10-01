#include <iostream>
#include <variant>
#include <memory>

class Expr {
public:
    using NestedVariant = std::variant<int, float, std::unique_ptr<Expr>>;

    Expr(const NestedVariant& left, const NestedVariant& right)
        : leftExpr(left), rightExpr(right) {}

    void print() const {
        std::cout << "Left: ";
        printVariant(leftExpr);
        std::cout << "Right: ";
        printVariant(rightExpr);
    }

private:
    NestedVariant leftExpr;
    NestedVariant rightExpr;

    void printVariant(const NestedVariant& var) const {
        std::visit( {
            if constexpr (std::is_same_v<std::decay_t<decltype(arg)>, std::unique_ptr<Expr>>) {
                if (arg) {
                    std::cout << "Expr instance" << std::endl;
                    arg->print();
                } else {
                    std::cout << "nullptr" << std::endl;
                }
            } else {
                std::cout << arg << std::endl;
            }
        }, var);
    }
};

int main() {
    auto leftExpr = std::make_unique<Expr>(10, 3.14f);
    auto rightExpr = std::make_unique<Expr>(20, std::make_unique<Expr>(30, 40.0f));

    Expr expr(leftExpr, rightExpr);
    expr.print();

    return 0;
}

