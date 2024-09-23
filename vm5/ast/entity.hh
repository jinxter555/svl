#include "../lang.hh"
#include "../operand.hh"

class Entity : public Operand {
protected:
  OperandType e_type_;

  vector<Entity> members;
  map<string, Entity> children;
  shared_ptr<Entity>  parent;
public:
  Entity() {}
  Entity(OperandType t) : e_type_(t) {
    type_ = t;
  }

  Entity(Operand v) : Operand(v) {e_type_ = v.type_;}
  //Operand get_operand() { return *this; }
  const Operand get_operand() const { return *this; }

  const Entity &operator[](string i) const;
  Entity &operator[](string i) ;


  const Entity &operator[](int i) const;
  Entity &operator[](int i) ;

  void list_add(Entity e) {
    //e_type_ = OperandType::list_t;
    members.push_back(e);
  };

  void list_print() const {
    int i, s = members.size();

    cout << "[";
    for(i=0; i<s-1; i++) { cout << members[i] << ","; }
    cout << members[i] << "]";
  }

  //friend ostream& operator<<(ostream& os, const Entity& e);
  friend ostream& operator<<(ostream& os, const Entity& e);

  using Operand::print_type;
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
