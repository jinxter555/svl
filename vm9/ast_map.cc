#include "ast_map.hh"
#include "operand_vars.hh"
#include "ast_list.hh"


#define SLOG_DEBUG_TRACE_FUNC
#include "scope_logger.hh"

//--------------------------------------
AstMap::AstMap() : AstNode(OperandType::map_t) {}
AstMap::AstMap(const map_t& m) : AstNode(OperandType::map_t) {
   for (auto const& [key, val] : m) {                                                                                                                                        
    map_[key] = val.clone();                                                                                                                                          
   }                                                                                                                                                                            
}

//--------------------------------------
astnode_u_ptr AstMap::clone() const {
  MYLOGGER(trace_function, "AstMap::clone()", __func__, SLOG_FUNC_INFO);
    astnode_u_ptr new_map = make_unique<AstMap>();                                                                                                                                   
   for (auto const& [key, val] : map_) {                                                                                                                                        
    (*new_map)[key] = val.clone();                                                                                                                                          
   }                                                                                                                                                                            
   return new_map;                       
}
Operand AstMap::evaluate(astnode_u_ptr& ctxt) { 
  MYLOGGER(trace_function, "AstMap::evalaute(astnode_u_ptr &ctxt)", __func__, SLOG_FUNC_INFO);
  return clone(); }

//------------------------------------------------------------------------------------------------------------------ 

Operand& AstMap::operator[] (const Operand& k) {
  MYLOGGER(trace_function, "AstMap::operator[](Operand&)", __func__, SLOG_FUNC_INFO);
  auto vrptr = k._vrptr();

  switch (vrptr->_get_type()) {
  case OperandType::str_t: {
    auto kstr = k.to_str()._to_str();
    return map_[kstr]; } //return const_cast<Operand&>(as_const(*this)[kstr]); }
  case OperandType::list_t: {
    auto &l= vrptr->get_list();
    return (*this)[l]; //return const_cast<Operand&>(as_const(*this)[l]); 
  }}
  return nil_operand_nc;
}

/*
const Operand& AstMap::operator[] (const string &k) const {
  MYLOGGER(trace_function, "AstMap::operator[](Operand&) const", __func__, SLOG_FUNC_INFO);
  if(!has_key(k)) return nil_operand;
  return map_.at(k); 
}
*/

//--------------------------------------
Operand& AstMap::operator[] (const list_t& index_keys) {
  MYLOGGER(trace_function, "AstMap::operator[](const list_t&) ", __func__, SLOG_FUNC_INFO);
  return (*this)[AstList(index_keys)];
}
Operand& AstMap::operator[] (const vec_str_t& index_keys) {
  MYLOGGER(trace_function, "AstMap::operator[](const vec_str_t&) ", __func__, SLOG_FUNC_INFO);
  return (*this)[AstList(index_keys)];
}

Operand& AstMap::operator[] (const AstList& index_keys) {
  MYLOGGER(trace_function, "AstMap::operator[](const AstList&) ", __func__, SLOG_FUNC_INFO);
  cout << "AstMap::operator[" <<  index_keys << "] \n" ;

  auto Mptr= _vrptr();
  s_integer i, s = index_keys.size();
  for(i=0; i<s; i++) {
    //auto &k= index_keys.list_[i];
    auto &k= index_keys[i];
    //cout << "i: " << i << " k: "<< k << "\n";
    auto &v = (*Mptr)[k];

    if(v.is_nil()) { 
      //cout << "v is nil!\n";
      return nil_operand_nc; 
    }
    //if(i==s-1)  return const_cast<Operand&>(as_const(*Mptr)[k]); 
    if(i==s-1) { 
      //cout << "Mptr: " << *Mptr << "\n";
      //cout << "returing v: " << v << "\n";
      return v; 
    }

    Mptr = v._vrptr();
  }
  return nil_operand_nc;
}

const Operand& AstMap::back() const {return nil_operand;}
Operand& AstMap::back_nc()  {return nil_operand_nc;}

//------------------------------------------------------------------------------------------------------------------ 



bool AstMap::add(const vec_str_t&k, astnode_u_ptr &&vptr, bool overwrite)  {
  return add(AstList(k), move(vptr), overwrite );
}

bool AstMap::add(const Operand &k, astnode_u_ptr &&vptr, bool overwrite)  {
  MYLOGGER(trace_function, "AstMap::add(Operand&k, astnode_u_ptr&&, bool) ", __func__, SLOG_FUNC_INFO)
  auto kptr = k._vrptr();
  switch (kptr->_get_type()) {
  case OperandType::list_t :
    add(kptr->get_list(), move(vptr), overwrite) ;
    return true;
  case OperandType::str_t:
    add(kptr->get_operand()._to_str(), move(vptr), overwrite) ;
    return true;
  }
  return false;

}
bool AstMap::add(const string &k, const AstNode &v, bool overwrite)  {
  MYLOGGER(trace_function, "AstMap::add(string &k, const AstNode&, bool) ", __func__, SLOG_FUNC_INFO);
  if(has_key(k)) {
    if(!overwrite) return false;
  }
  map_[k] = v.clone();
  return true;
}
bool AstMap::add(const string &k, const operand_variant_t&v, bool overwrite)  {
  MYLOGGER(trace_function, "AstMap::add(string &k, const operand_variant_t, bool) ", __func__, SLOG_FUNC_INFO);
  if(has_key(k)) {
    if(!overwrite) return false;
  }
  map_[k] = v;
  return true;
}
bool AstMap::add(const vec_str_t&k, const operand_variant_t&v, bool overwrite)  {
  return add(AstList(k), v, overwrite );
}

bool AstMap::add(const string &k, astnode_u_ptr &&vptr, bool overwrite)  {
  MYLOGGER(trace_function, "AstMap::add(string &k, astnode_u_ptr&&, bool) ", __func__, SLOG_FUNC_INFO);
  if(has_key(k)) {
    if(!overwrite) return false;
  }
  map_[k] = move(vptr);
  return true;
}
//------------------------------------- 
bool AstMap::add(const AstList &index_keys, astnode_u_ptr &&vptr, bool overwrite)  {
  MYLOGGER(trace_function, "AstMap::add(AstList&, astnode_u_ptr&&, bool) ", __func__, SLOG_FUNC_INFO);
  //cout << "AstList::add[" <<  index_keys << "] \n" ;

  auto Mptr= _vrptr();
  s_integer i, s = index_keys.size();
  for(i=0; i<s; i++) {
    auto &k= index_keys[i];
    auto &v = (*Mptr)[k];
    if(!v.is_nil() && !overwrite) return false;
    if(v.is_nil()) {
      //if(!overwrite) return false;


      if(i==s-1) { //cout << "v is nil, map add setting final:" << *vptr << "\n";
        (*Mptr)[k] = move(vptr);
        return true;
      } else {
        astnode_u_ptr new_map = make_unique<AstMap>();
        (*Mptr)[k] = move(new_map);
        Mptr = (*Mptr)[k]._vrptr();
      }

      continue;
    }
    if(i==s-1) { //cout << "v is not nil, map add setting final:" << *vptr << "\n";
      (*Mptr)[k] = move(vptr);
      return true;
    }
    Mptr = v._vrptr();
  }
  return true;
}

//------------------------------------- 
bool AstMap::add(const AstList &index_keys, const operand_variant_t& ovv, bool overwrite)  {
  MYLOGGER(trace_function, "AstMap::add(AstList&, operand_variant&, bool) ", __func__, SLOG_FUNC_INFO);
  //cout << "AstList::add[" <<  index_keys << "] \n" ;

  auto Mptr= _vrptr();
  s_integer i, s = index_keys.size();
  for(i=0; i<s; i++) {
    auto &k= index_keys[i];
    auto &v = (*Mptr)[k];
    if(!v.is_nil() && !overwrite) return false;
    if(v.is_nil()) {
      //if(!overwrite) return false;


      if(i==s-1) { //cout << "v is nil, map add setting final:" << *vptr << "\n";
        (*Mptr)[k] = ovv;
        return true;
      } else {
        astnode_u_ptr new_map = make_unique<AstMap>();
        (*Mptr)[k] = move(new_map);
        Mptr = (*Mptr)[k]._vrptr();
      }

      continue;
    }
    if(i==s-1) { //cout << "v is not nil, map add setting final:" << *vptr << "\n";
      (*Mptr)[k] = ovv;
      return true;
    }
    Mptr = v._vrptr();
  }
  return true;
}



//------------------------------------- 
astnode_ptr AstMap::_vrptr() const {
  MYLOGGER(trace_function, "AstList::_vptr()", __func__, SLOG_FUNC_INFO);
  return (AstNode*) this; 
}

const astnode_u_ptr& AstMap::get_u_ptr() const { return nil_ast_ptr; }
astnode_u_ptr& AstMap::get_u_ptr_nc() { return nil_ast_ptr_nc; }
//------------------------------------- 
bool AstMap::has_key(const Operand &k)  const {
  string k_str = k._to_str();
  return has_key(k_str);
}
bool AstMap::has_key(const string  &k)  const {
 // if(this==nullptr || type_ != OperandType::map_t) return false;
  if(type_ != OperandType::map_t) return false;
  if (map_.find(k) != map_.end())  {
    return true;
  }
  return false;
}

//------------------------------------- 
Operand AstMap::to_str() const {

  if(map_.empty()) return "{}";

  vector<string> kv_paires ;
  string colon(":");
  string q("\"");
  string outstr;

  for (auto const& [key, val] : map_) {
    outstr = q + key + q  + colon + " " + val.to_str()._to_str();
    kv_paires.push_back(outstr);
  }

  outstr="{";
  int i, s = kv_paires.size();
  for(i=0; i<s-1; i++) {
    outstr = outstr + kv_paires[i] + ", ";
  }
  outstr = outstr + kv_paires[i] + "}";
  return (outstr);
}

//------------------------------------- 
vector<string> AstMap::_get_keys() const {
  vector<string> key_list;
  for (auto const& [key, val] : map_) {
    key_list.push_back(key);
  }
  return key_list;
}

//------------------------------------- 
Operand AstMap::get_type() const { return Operand(OperandType::map_t); }
OperandType AstMap::_get_type() const { return OperandType::map_t; }

operand_variant_t AstMap::_get_variant() const { return nil; }
//------------------------------------- 
s_integer  AstMap::size() const { return map_.size(); }
void AstMap::print() const { cout << to_str(); }

//------------------------------------- 
const AstNode& AstMap::get_node() const { return *this; }
const AstList& AstMap::get_list() const { return nil_list; }
const Operand& AstMap::get_operand() const { return nil_operand; }
const AstMap& AstMap::get_map() const { return *this; }
bool AstMap::is_nil() const {
  if(size()<=0) return true;
  return false;
}

//------------------------------------------------------------------------------------------------------------------ 
const Operand* AstMap::get_operand_ptr() const {
  MYLOGGER(trace_function, "AstMap::get_operand_ptr()", __func__, SLOG_FUNC_INFO);
  return (Operand*)this;
}
const AstList* AstMap::get_list_ptr() const {
  MYLOGGER(trace_function, "AstMap::get_list_ptr()", __func__, SLOG_FUNC_INFO);
  return nullptr;
}

const AstMap* AstMap::get_map_ptr() const {
  MYLOGGER(trace_function, "AstMap::get_map_ptr()", __func__, SLOG_FUNC_INFO);
  return this;
}

//------------------------------------- 
Operand* AstMap::get_operand_ptr_nc() {
  MYLOGGER(trace_function, "AstMap::get_operand_ptr_nc()", __func__, SLOG_FUNC_INFO);
  return (Operand*)this;
}
AstList* AstMap::get_list_ptr_nc() {
  MYLOGGER(trace_function, "AstMap::get_list_ptr_nc()", __func__, SLOG_FUNC_INFO);
  return nullptr;
}

AstMap* AstMap::get_map_ptr_nc() {
  MYLOGGER(trace_function, "AstMap::get_map_ptr_nc()", __func__, SLOG_FUNC_INFO);
  return this;
}




/*
AstMap::AstMap() : AstNode(OperandType::map_t) {
  map_ = {};
}
void AstMap::accept_nc(Visitor& visitor) {
  visitor.visit(*this);
}

void AstMap::accept(Visitor& visitor) const {
  visitor.visit(*const_cast<AstMap*>(this));
}

bool AstMap::isEqual(const AstNode &other) const {
  CompareVisitor compare_visitor(*this);
  other.accept(compare_visitor);
  return compare_visitor.isEqualResult();
}
*/

bool AstMap::operator==(const AstNode& ) const {};
bool AstMap::operator==(const astnode_ptr& ) const {};