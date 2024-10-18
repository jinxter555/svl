#include "ast.hh"
#include "operand.hh"

AstMap::AstMap() : AstExpr(OperandType::map_t) {}

astexpr_u_ptr AstMap::clone() const {
  map_u_ptr new_map = make_unique<AstMap>();

  for (auto const& [key, val] : map_) {
    new_map->map_[key] = val->clone();
  }
  return new_map;
}

astexpr_u_ptr AstMap::evaluate(astexpr_u_ptr& ast_ctxt) {
  return nullptr;
}

