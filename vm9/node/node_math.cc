#include "node.hh"


//------------------------------------------------------------------------
Node Node::operator+(const Node &other) const {
  return visit([&](auto&& lhs, auto&& rhs) -> Node {
    using L = decay_t<decltype(lhs)>;
    using R = decay_t<decltype(rhs)>;

    if constexpr (is_arithmetic_v<L> && is_arithmetic_v<R>) {
      if constexpr (is_same_v<L, Integer> && is_same_v<R, Integer>)
        return Node(static_cast<Integer>(lhs + rhs));
      else
        return Node(static_cast<Float>(lhs) + static_cast<Float>(rhs));
      } else if constexpr (is_same_v<L, string> && is_same_v<R, string>) {
        return Node(lhs + rhs);
      } else {
        return Node(Error{Error::Type::InvalidOperation, 
            "Unsupported types for addition! " + _to_str(type_) + 
            " : " + _to_str(other.type_)});
      }
  }, value_, other.value_);
}

Node Node::operator*(const Node &other) const {
  return visit([&](auto&& lhs, auto&& rhs) -> Node {
    using L = decay_t<decltype(lhs)>;
    using R = decay_t<decltype(rhs)>;

    if constexpr (is_arithmetic_v<L> &&  is_arithmetic_v<R>) {
      if constexpr (is_same_v<L, Integer> &&  is_same_v<R, Integer>)
        return Node(static_cast<Integer>(lhs + rhs));
      else
        return Node(static_cast<Float>(lhs) * static_cast<Float>(rhs));
    } else {
      return Node(Error{Error::Type::InvalidOperation, "Unsupported types for multiplication"});
    }

  }, value_, other.value_);
}

Node Node::operator/(const Node &other) const {

  return visit([&](auto&& lhs, auto&& rhs) -> Node {
    using L = decay_t<decltype(lhs)>;
    using R = decay_t<decltype(rhs)>;

    if constexpr (is_arithmetic_v<L> &&  is_arithmetic_v<R>) {
      if(static_cast<Float>(rhs) == 0.0)
        return Node(Error{Error::Type::DivideByZero,
          "Divide by zero "});
      return Node(static_cast<Float>(lhs) / static_cast<Float>(rhs));
    } else {
      return Node(Error{Error::Type::InvalidOperation, "Unsupported types for Division"});
    }
  }, value_, other.value_);
}
