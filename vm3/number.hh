#ifndef NUMBER_H
#define NUMBER_H

#include <variant>
#include <iostream>
#include "lang.hh"
#include "svlm_operand.hh"

class Number : Operand {
public:
    Number(int value);
    Number(float value);

    Number operator+(const Number& other) const;
    Number operator-(const Number& other) const;
    Number operator*(const Number& other) const;
    Number operator/(const Number& other) const;

    bool operator==(const Number& other) const;
    bool operator!=(const Number& other) const;
    bool operator>=(const Number& other) const;
    bool operator<=(const Number& other) const;
    bool operator<(const Number& other) const;
    bool operator>(const Number& other) const;

    void print() const; // New method to print data_
    std::variant<int, float> get_data() const; // New method to get data_
    std::string getCurrentType() const; // New method to get the current type
    OperandType whoami() override {return OperandType::Number; } ;

    
private:
    num_d_t data_;
    struct AddVisitor;
    struct SubtractVisitor;
    struct MultiplyVisitor;
    struct DivideVisitor;

    struct EqlVisitor;
    struct NeqlVisitor;
    struct GtVisitor;
    struct LtVisitor;
    struct GtEqVisitor;
    struct LtEqVisitor;
};

#endif // NUMBER_H

