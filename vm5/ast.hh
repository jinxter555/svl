#include "entity.hh"

class AstNode : public Entity {
public:
  AstNode() {}
  // AstNode(const  Entity &v)  : Entity(v) {}
  //-------------------------------------------
  const Entity& get_entity() {return *this; }
};


class AstExpr : public AstNode {
public:
  AstExpr() {};
//  AstExpr(const Entity &v) : AstNode(v) {}
  //virtual AstType whoami() = 0;
  //virtual Entity evaluate(Entity *ast_ctxt) = 0;
  //virtual void codegen(std::vector<std::string>& code) const = 0;
  virtual void print() = 0 ;
};

/*
class AstMap : public AstNode{
public:
  AstMap();
  entity_ptr add_ptr(const string &k, entity_ptr vptr) ;
  Entity add(const string &k, const Entity &v) ;
  Entity add(const vector<string> &ks, const Entity &v) ;
  Entity get(const string &k);
  Entity set(const string &k, const Entity &v);
  entity_ptr get_ptr(const string &k) ;
  entity_ptr get_new_ptr(const string &k) ;
  Entity evaluate(Entity *ast_ctxt) override;
  void print() override;
  using Entity::whatami;
};

class AstRoot : public AstMap {
protected:
  entity_ptr root=nullptr;
public:
  AstRoot();
  AstRoot(AstMap m);
  Entity add(const vector<string> &ks, const Entity &v) ;


};
*/