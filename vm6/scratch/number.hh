#ifndef NUMBER_H
#define NUMBER_H

#include <variant>
#include <iostream>
#include "lang.hh"
#include "boost/variant.hpp"



using s_integer = long;
using s_float = double;
using num_d_t= boost::variant<s_integer, s_float> ;

class Number {
public:
    //Number(int v) : data_(v) {};
    //Number(float v) : data_(v) {};
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

    void print() const; // New method to print data_
    //std::variant<int, float> get_data() const; // New method to get data_
    num_d_t get_data() const; // New method to get data_
    std::string getCurrentType() const; // New method to get the current type
    friend std::ostream& operator<<(std::ostream& os, const Number& number);

    std::string to_str() const;
    
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

    struct AndVisitor;
    struct OrVisitor;
    struct NotVisitor;



};

#endif // NUMBER_H

