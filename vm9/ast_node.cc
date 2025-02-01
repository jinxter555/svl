
#include <iostream>
#include <variant>
#include <unordered_map>
#include <vector>
#include "ast_node.hh"

#include "operand_vars.hh"
#include "ast_list.hh"

#define SLOG_DEBUG_TRACE_FUNC
#include "scope_logger.hh"

/*
Operand& AstNode::operator[] (const AstList& index_keys) {
  MYLOGGER(trace_function, "AstNode::operator[](const AstList&) const", __func__, SLOG_FUNC_INFO);
  cout << "AstNode::operator[" <<  index_keys << "] \n" ;

  auto Lptr= _vrptr();
  s_integer i, s = index_keys.size();
  for(i=0; i<s; i++) {
    //auto &k= index_keys.list_[i];
    auto &k= index_keys[i];
    auto &v = (*Lptr)[k];

    if(v.is_nil()) { return nil_operand_nc; }
    if(i==s-1) { return const_cast<Operand&>(as_const(*Lptr)[k]); //return v;
    }

    Lptr = v._vrptr();
  }
  return nil_operand_nc;
}
*/

//--------------------------------------------------------- 
ostream& operator<<(ostream& os, const AstNode& e) {
  /*
  if(e.is_nil() ) cerr << "<< AstNode is nil\n"; 
  else e.print();
 */ 
  if(!e.is_nil() ) e.print();
  return os;
}

ostream& operator<<(ostream& os, const astnode_u_ptr& ptr) {
  /*
  if(ptr==nullptr) { cout << "<< astnode_u_ptr is null\n"; } 
  else ptr->print();
 */ 
  if(ptr!=nullptr) ptr->print();
  return os;
}


#include "operand.hh"
string AstNode::AstPtr2Str(const astnode_u_ptr&ptr) const{
 if(ptr==nullptr) return "nil";
 return ptr->to_str()._to_str();
};
string AstNode::AstPtr2Str(const astnode_ptr&ptr) const{
 if(ptr==nullptr) return "nil";
 return ptr->to_str()._to_str();
};