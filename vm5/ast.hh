#include "entity.hh"


class AstExpr : public Entity {
public:
  AstExpr();
  AstExpr(const Operand &v) : Entity(v) {}
  AstExpr(const Entity &v) : Entity(v) {}
  virtual ~AstExpr();
  //virtual AstType whoami() = 0;
  virtual Entity evaluate(Entity *ast_ctxt) = 0;
  //virtual void codegen(std::vector<std::string>& code) const = 0;
  virtual void print() = 0 ;
};

class AstList : public AstExpr {
public:
  AstList();
  void add(const Entity &v) ;
  Entity get(int i) const ;
  Entity set(int i, const Entity &v);
  Entity& get_ref(int i) ;
  void print() override;
  Entity evaluate(Entity *ast_ctxt) override;
};

class AstMap : public AstExpr {
public:
  AstMap();
  void add_ptr(const string &k, entity_ptr vptr) ;
  void add(const string &k, const Entity &v) ;
  Entity get(const string &k);
  Entity set(const string &k, const Entity &v);
  entity_ptr get_node_ptr(const string &k) ;
  Entity evaluate(Entity *ast_ctxt) override;
  void print() override;
  using Entity::whatami;
};