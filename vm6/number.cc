#include "number.hh"


Number::Number(s_integer value) : type_(OperandType::s_int_t), value_(value) {}
Number::Number(s_float value) : type_(OperandType::s_float_t), value_(value) {}

struct Number::AddVisitor {
  template <typename T, typename U>
    auto operator()(const T& a, const U& b) const -> Number {
    return a + b;
  }
};

struct Number::SubtractVisitor {
  template <typename T, typename U>
  auto operator()(const T& a, const U& b) const -> Number {
    return a - b;
  }
};

struct Number::MultiplyVisitor {
  template <typename T, typename U>
  auto operator()(const T& a, const U& b) const -> Number {
    return a * b;
  }
};

struct Number::DivideVisitor {
  template <typename T, typename U>
  auto operator()(const T& a, const U& b) const -> Number {
    if (b != 0) {
      return a / b;
    } else {
      // Handle division by zero
      std::cerr << "Error: Division by zero!" << std::endl;
      throw std::runtime_error("Division by zero"); 
      return Number(0l);
    }
  }
};

struct Number::EqlVisitor {
  template <typename T, typename U>
  auto operator()(const T& a, const U& b) const -> bool {
    return a == b;
  }
};

struct Number::NeqlVisitor {
  template <typename T, typename U>
  auto operator()(const T& a, const U& b) const -> bool {
    return a != b;
  }
};

struct Number::GtVisitor {
  template <typename T, typename U>
  auto operator()(const T& a, const U& b) const -> bool {
    return a > b;
  }
};

struct Number::LtVisitor {
  template <typename T, typename U>
  auto operator()(const T& a, const U& b) const -> bool {
    return a < b;
  }
};

struct Number::LtEqVisitor {
  template <typename T, typename U>
  auto operator()(const T& a, const U& b) const -> bool {
    return a <= b;
  }
};

struct Number::GtEqVisitor {
  template <typename T, typename U>
  auto operator()(const T& a, const U& b) const -> bool {
    return a >= b;
  }
};

struct Number::AndVisitor {
  template <typename T, typename U>
  auto operator()(const T& a, const U& b) const -> bool {
    return a && b;
  }
};

struct Number::OrVisitor {
  template <typename T, typename U>
  auto operator()(const T& a, const U& b) const -> bool {
    return a || b;
  }
};
struct Number::NotVisitor {
  template <typename T>
  auto operator()(const T& a) const -> bool {
    return !a;
  }
};




Number Number::operator+(const Number& other) const {
  return visit(Number::AddVisitor{}, value_, other.value_);
}

Number Number::operator-(const Number& other) const {
  return visit(Number::SubtractVisitor{}, value_, other.value_);
}

Number Number::operator*(const Number& other) const {
  return visit(Number::MultiplyVisitor{}, value_, other.value_);
}

Number Number::operator/(const Number& other) const {
  return visit(Number::DivideVisitor{}, value_, other.value_);
}

bool Number::operator==(const Number& other) const {
  return visit(Number::EqlVisitor{}, value_, other.value_);
}
bool Number::operator!=(const Number& other) const {
  return visit(Number::NeqlVisitor{}, value_, other.value_);
}
bool Number::operator>=(const Number& other) const {
  return visit(Number::GtEqVisitor{}, value_, other.value_);
}
bool Number::operator<=(const Number& other) const {
  return visit(Number::LtEqVisitor{}, value_, other.value_);
}
bool Number::operator<(const Number& other) const {
  return visit(Number::LtVisitor{}, value_, other.value_);
}
bool Number::operator>(const Number& other) const {
  return visit(Number::GtVisitor{}, value_, other.value_);
}

bool Number::operator&&(const Number& other) const {
  return visit(Number::AndVisitor{}, value_, other.value_);
}
bool Number::operator||(const Number& other) const {
  return visit(Number::OrVisitor{}, value_, other.value_);
}
bool Number::operator!() const {
  return visit(Number::NotVisitor{}, value_);
}

string Number::_to_str() const {
  return visit([](auto val) { return to_string(val);
  }, value_);
}
string Number::to_str() const {
  return _to_str();
}


void Number::print() const {
  cout << _to_str();
}

std::ostream& operator<<(std::ostream& os, const Number& number) {
  //visit([&os](const auto& value) { os << value; }, number.value_);
  cout << number.to_str();
  return os;
}

num_d_t Number::get_value() const {
   return value_;
}
OperandType Number::get_type() const { return type_; }

std::string Number::getCurrentType() const {
  return visit([](auto val) -> std::string {
    if constexpr (std::is_same_v<decltype(val), int>) {
      return "int";
    } else if constexpr (std::is_same_v<decltype(val), float>) {
      return "float";
    } else {
      return "unknown";
    }
  }, value_);
}
