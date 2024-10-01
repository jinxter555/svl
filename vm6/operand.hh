#pragma once
#include "lang.hh"


class Operand; 
class Entity;
using entity_u_ptr = unique_ptr<Entity>;

using OperandVariant=variant_user 
< bool, s_integer, s_float, AstOp
, string, OperandErrorCode
, OperandStatusCode, OperandType
//, entity_u_ptr
>;

using o_u_ptr=unique_ptr<Operand>;

class Operand {
  friend class Entity;
  friend class OperandEntity;
  friend class ListEntity;
  friend class MapEntity;
protected:
  OperandType type_;
  OperandVariant value_;
public:
  const static string nil_str;
  // Constructors for each supported type
  // Operand(int value) ; //Operand(float value) 
  //--------
  Operand();
  Operand(bool) ;
  Operand(s_integer);
  Operand(s_float);
  Operand(const string&);
  Operand(const char* value);
  Operand(OperandType);
  Operand(AstOp);
  Operand(OperandErrorCode);
  Operand(OperandStatusCode);
  //Operand(const entity_u_ptr&);
  //--------------------------------------------------------- Overload primative operator
  s_integer _get_int() const ;
  s_float _get_float() const ;

  const string _get_str() const ;
  const string _to_str() const ;

  void set_type(const OperandType &t) { type_= t; };
  OperandType _get_type() const { return type_;};

  //--------------------------------------------------------- Overload math operator
  Operand get_str() const;
  Operand to_str() const; 
  Operand whatami() const;  // introspection type + value
  //--------------------------------------------------------- Overload math operator
  friend ostream& operator<<(ostream& os, const Operand& operand);

};