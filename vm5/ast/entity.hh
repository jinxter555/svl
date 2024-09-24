#include "../lang.hh"
#include "../operand.hh"


class Entity;
using entity_ptr = shared_ptr<Entity>;
class Entity : public Operand {
protected:
  vector<Entity> members;

  map<string, entity_ptr> children;
  entity_ptr  parent;
public:
  Entity() {}
  Entity(OperandType t)  { type_ = t; }
  Entity(Operand v) : Operand(v) {}

  //Operand get_operand() { return *this; }
  const Operand get_operand() const { return *this; }

  const Entity &operator[](string i) const;
  Entity &operator[](string i) ;


  const Entity &operator[](int i) const;
  Entity &operator[](int i) ;

  //-------------------------------------------
  // void add_node(string k, entity_ptr vptr){ children[k] = vptr; }
  //-------------------------------------------

  void list_add(Entity e);
  void list_print() const;

  //-------------------------------------------
  friend ostream& operator<<(ostream& os, const Entity& e);

  //-------------------------------------------
  using Operand::type_print;
  using Operand::type_get;

  using Operand::type_str;
  using Operand::err_str;
  using Operand::ast_op_str;
  using Operand::whatami;

  //-------------------------------------------



  using Operand::operator+;
  using Operand::operator-;
  using Operand::operator*;
  using Operand::operator/;

  using Operand::operator==;
  using Operand::operator!=;
  using Operand::operator>=;
  using Operand::operator<=;
  using Operand::operator<;
  using Operand::operator>;

  using Operand::operator&&;
  using Operand::operator||;
  using Operand::operator!;
};
