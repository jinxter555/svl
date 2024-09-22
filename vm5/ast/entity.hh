#include "../lang.hh"
#include "../operand.hh"

class Entity : public Operand {
private:
  vector<Entity> members;
  map<string, Entity> children;
  shared_ptr<Entity>  parent;
public:
  OperandType e_type_;
  Entity() {}
  Entity(Operand v) : Operand(v) {e_type_ = v.type_;}
  Operand get_operand() { return *this; }

  const Entity &operator[](string i) const;
  Entity &operator[](string i) ;
  const Entity &operator[](int i) const;
  Entity &operator[](int i) ;

  //Entity &operator=(Operand v) ; 

  using Operand::operator+;
  using Operand::operator-;
  using Operand::operator*;
  using Operand::operator/;

/*
  using operator==(const Operand& other) const;
  using operator!=(const Operand& other) const;
  using operator>=(const Operand& other) const;
  using operator<=(const Operand& other) const;
  using operator<(const Operand& other) const;
  using operator>(const Operand& other) const;
*/

  Operand operator&&(const Operand& other) const;
  Operand operator||(const Operand& other) const;
  Operand operator!() const;
};
