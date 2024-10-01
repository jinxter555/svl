#include "number.hh"

Number::Number(s_integer value) : data_(value) {}
Number::Number(s_float value) : data_(value) {}

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
  return visit(Number::AddVisitor{}, data_, other.data_);
}

Number Number::operator-(const Number& other) const {
  return visit(Number::SubtractVisitor{}, data_, other.data_);
}

Number Number::operator*(const Number& other) const {
  return visit(Number::MultiplyVisitor{}, data_, other.data_);
}

Number Number::operator/(const Number& other) const {
  return visit(Number::DivideVisitor{}, data_, other.data_);
}

bool Number::operator==(const Number& other) const {
  return visit(Number::EqlVisitor{}, data_, other.data_);
}
bool Number::operator!=(const Number& other) const {
  return visit(Number::NeqlVisitor{}, data_, other.data_);
}
bool Number::operator>=(const Number& other) const {
  return visit(Number::GtEqVisitor{}, data_, other.data_);
}
bool Number::operator<=(const Number& other) const {
  return visit(Number::LtEqVisitor{}, data_, other.data_);
}
bool Number::operator<(const Number& other) const {
  return visit(Number::LtVisitor{}, data_, other.data_);
}
bool Number::operator>(const Number& other) const {
  return visit(Number::GtVisitor{}, data_, other.data_);
}

bool Number::operator&&(const Number& other) const {
  return visit(Number::AndVisitor{}, data_, other.data_);
}
bool Number::operator||(const Number& other) const {
  return visit(Number::OrVisitor{}, data_, other.data_);
}
bool Number::operator!() const {
  return visit(Number::NotVisitor{}, data_);
}

void Number::print() const {
  visit([](auto val) {
    std::cout << val;
  }, data_);
}
string Number::to_str() const {
  return visit([](auto val) {
    return to_string(val);
  }, data_);
}

std::ostream& operator<<(std::ostream& os, const Number& number) {
  visit([&os](const auto& value) { os << value; }, number.data_);
  return os;
}

num_d_t Number::get_data() const {
   return data_;
}

std::string Number::getCurrentType() const {
  return visit([](auto val) -> std::string {
    if constexpr (std::is_same_v<decltype(val), int>) {
      return "int";
    } else if constexpr (std::is_same_v<decltype(val), float>) {
      return "float";
    } else {
      return "unknown";
    }
  }, data_);
}
