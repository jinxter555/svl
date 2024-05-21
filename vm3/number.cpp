#include "number.hh"

Number::Number(int value) : data_(value) {}
Number::Number(float value) : data_(value) {}

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
      return Number(0);
    }
  }
};

struct Number::EqlVisitor {
  template <typename T, typename U>
  auto operator()(const T& a, const U& b) const -> bool {
    return a == b;
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




Number Number::operator+(const Number& other) const {
  return std::visit(Number::AddVisitor{}, data_, other.data_);
}

Number Number::operator-(const Number& other) const {
  return std::visit(Number::SubtractVisitor{}, data_, other.data_);
}

Number Number::operator*(const Number& other) const {
  return std::visit(Number::MultiplyVisitor{}, data_, other.data_);
}

Number Number::operator/(const Number& other) const {
  return std::visit(Number::DivideVisitor{}, data_, other.data_);
}

bool Number::operator==(const Number& other) const {
  return std::visit(Number::EqlVisitor{}, data_, other.data_);
}
bool Number::operator>=(const Number& other) const {
  return std::visit(Number::GtEqVisitor{}, data_, other.data_);
}
bool Number::operator<=(const Number& other) const {
  return std::visit(Number::LtEqVisitor{}, data_, other.data_);
}
bool Number::operator<(const Number& other) const {
  return std::visit(Number::LtVisitor{}, data_, other.data_);
}
bool Number::operator>(const Number& other) const {
  return std::visit(Number::GtVisitor{}, data_, other.data_);
}

void Number::printData() const {
  std::visit([](auto val) {
    std::cout << val;
  }, data_);
}

num_d_t Number::getData() const {
   return data_;
}

std::string Number::getCurrentType() const {
  return std::visit([](auto val) -> std::string {
    if constexpr (std::is_same_v<decltype(val), int>) {
      return "int";
    } else if constexpr (std::is_same_v<decltype(val), float>) {
      return "float";
    } else {
      return "unknown";
    }
  }, data_);
}
