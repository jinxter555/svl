#pragma once
#include "ast_node.hh"
#include "operand.hh"
#include "ast_map.hh"
#include "ast_list.hh"

class AstCase : public AstExpr{
  AstCase();
  //AstCase(astnode_u_ptr top, astnode_u_ptr body) ; 
  AstCase(astnode_u_ptr top, astnode_u_ptr body) ; 
  Operand evaluate(astnode_u_ptr &) override;
  Operand to_str() const override;
  Operand get_type() const override ;
  OperandType _get_type() const override;

};
