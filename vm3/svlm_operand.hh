#pragma once
#include <any>
class Operand {
public:
  enum class OperandType{Nobody, Number, Tuple, Atom, String};
    virtual OperandType whoami() { return OperandType::Nobody; }; // New method to print data_

    virtual std::any operator+(const Operand& other) const {return 0;};
    //Number(int value);
    //Number(float value);
    /*

    virtual std::any operator+(const Operand& other)=0;
    virtual std::any operator-(const Operand& other)=0 ;
    virtual std::any operator*(const Operand& other)=0 ;
    virtual std::any operator/(const Operand& other)=0 ;

    virtual bool operator==(const Operand& other)=0 ;
    virtual bool operator!=(const Operand& other)=0;
    virtual bool operator>=(const Operand& other)=0;
    virtual bool operator<=(const Operand& other)=0;
    virtual bool operator<(const Operand& other)=0;
    virtual bool operator>(const Operand& other)=0;
    virtual void print() const; // New method to print data_
    */
    // virtual void print() const {}; // New method to print data_
};