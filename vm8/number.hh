#ifndef NUMBER_H
#define NUMBER_H

#include <variant>
#include <iostream>
#include "lang.hh"

using namespace std;


using num_d_t = variant<s_integer, s_float>;
class Operand;

class Number {
public:
    //Number(int v) : value_(v) {};
    //Number(float v) : value_(v) {};
    Number(s_integer value);
    Number(s_float value);

    Number operator+(const Number& other) const ;
    Number operator-(const Number& other) const;
    Number operator*(const Number& other) const;
    Number operator/(const Number& other) const;

    bool operator==(const Number& other) const;
    bool operator!=(const Number& other) const;
    bool operator>=(const Number& other) const;
    bool operator<=(const Number& other) const;
    bool operator<(const Number& other) const;
    bool operator>(const Number& other) const;

    bool operator&&(const Number& other) const;
    bool operator||(const Number& other) const;
    bool operator!() const;

    num_d_t get_value() const; // New method to get value_
    std::string getCurrentType() const; // New method to get the current type
    friend std::ostream& operator<<(std::ostream& os, const Number& number);


    //unique_ptr<Number> clone() const {return nullptr;}
    string _to_str() const ;
    string to_str() const ;
    OperandType get_type() const ;
    void print() const ;
    
private:
    num_d_t value_;
    OperandType type_;

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

    struct AndVisitor;
    struct OrVisitor;
    struct NotVisitor;



};

#endif // NUMBER_H

