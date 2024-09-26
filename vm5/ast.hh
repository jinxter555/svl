#include "entity.hh"

class AstNode : public Entity {
public:
  AstNode() {}
  // AstNode(const  Entity &v)  : Entity(v) {}
  //-------------------------------------------
  virtual const Entity& add(const Entity& v)=0;
  virtual const entity_u_ptr& add(entity_u_ptr &vptr) =0;


  virtual entity_u_ptr add(const Entity &k, const Entity& v)=0;

  virtual const Entity& get(const Entity &k) = 0;
  virtual const Entity& set(const Entity &k, const Entity &v) = 0;
  virtual const Entity& set(const Entity &k, entity_u_ptr &vptr) = 0;

//  virtual const AstList& get_list(const Entity &k) = 0;
//  virtual const AstMap& get_map(const Entity &k) = 0;
  //-------------------------------------------
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

class AstMap;
class AstList : public AstExpr{
public:
  AstList();
  const Entity& add(const Entity &v) override ;
  const entity_u_ptr& add(entity_u_ptr &vptr) override;
  const Entity&   get(const Entity &k) override ;

  const Entity& set(const Entity &k, const Entity &v) override;
  const Entity& set(const Entity &k, entity_u_ptr &vptr) override;

  entity_u_ptr add(const Entity &k, const Entity& v) override { return nullptr; }; // this is for map not

  void print() override;


 // const AstMap&   get_map(const Entity &k) override;
 // AstList&  get_list(const Entity &k) override;
 // Entity& get_ref(int i) ;

  //Entity evaluate(Entity *ast_ctxt) override;
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