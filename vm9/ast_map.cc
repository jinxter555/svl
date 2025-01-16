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
  MYLOGGER_MSG(trace_function, string("k: ") + k._to_str(), SLOG_FUNC_INFO);
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
  MYLOGGER_MSG(trace_function, string("k: ") + index_keys.to_str()._to_str(), SLOG_FUNC_INFO);

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
  MYLOGGER(trace_function, "AstMap::_vptr()", __func__, SLOG_FUNC_INFO);
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

bool AstMap::operator==(const AstMap& other ) const {
  MYLOGGER(trace_function, "AstMap::==(const AstMap&)", __func__, SLOG_FUNC_INFO);
  MYLOGGER_MSG(trace_function, string("this : ") + to_str()._to_str(), SLOG_FUNC_INFO);
  MYLOGGER_MSG(trace_function, string("other: ") + other.to_str()._to_str(), SLOG_FUNC_INFO);


  //cout << "AstMap::==(const AstMap&)\n";
  //cout << "this: " <<  to_str() << ", other: " <<  other << "\n";
  return cmp_eql(other.get_map_ptr());
}

bool AstMap::operator==(const astnode_ptr& vptr) const {
  MYLOGGER(trace_function, "AstMap::==(const astnode_ptr)", __func__, SLOG_FUNC_INFO);
  cout << "AstMap::==(const astnode_ptr*)\n";
  return cmp_eql(vptr->get_map_ptr());
}

bool AstMap::operator!=(const AstMap &other) const { 
  MYLOGGER(trace_function, "AstMap::!=(const AstMap&)", __func__, SLOG_FUNC_INFO);
  //cout << "AstMap::!=(const AstMap&)\n";
  return !cmp_eql(other);
}


bool AstMap::cmp_eql(const AstNode &other) const { 
  return cmp_eql(other.get_map_ptr());
}
bool AstMap::cmp_eql(const AstMap *other_ptr) const { 
  MYLOGGER(trace_function, "AstMap::cmp_eql(const AstMap*)", __func__, SLOG_FUNC_INFO+9);
  //cout << "AstMap::cmp_eql(const AstMap*)\n";

  //cout << "*this: " << *this <<  " type: " << get_type() << "\n";
  s_integer s=size();

  if(other_ptr==nullptr ){
    if(s==0) return true;
    cout << "other_ptr is null!\n";
    return false;
  }
  //cout << "*other: " << *other_ptr << " other type: " << other_ptr->get_type() << "\n\n";

  if(other_ptr->_get_type()!= OperandType::map_t) return false;
  if(s != other_ptr->size()) return false;

  for (auto const& [key, val] : map_) {
    //auto& other_val = (*other_ptr)[key];
    auto &other_map_ = other_ptr->map_;
    //auto &other_val = other_map_[key];
    try {
      auto& other_val = other_ptr->map_.at(key);
      if(val != other_val) { //cout << key << ":" << val << " != " << key << ":" << other_val << "\n";
        return false; }
    } catch(const out_of_range &e) { return false; }
  }
  return true; 
}
Operand AstMap::opfunc(const AstNode& other, AstOpCode op) {
  MYLOGGER(trace_function , "AstMap::opfunc()" ,__func__, SLOG_FUNC_INFO);
  cout << "AstMap::opfunc()!\n";

  print(); cout << " " << Operand(op) << " " <<  other <<"\n";
  //return make_unique<Operand>( eql_cmp(move(other)));
  switch(op) {
  //case AstOpCode::eql:    return make_unique<Operand>( *this == move(other));
  case AstOpCode::eql:    return  cmp_eql(other);
  case AstOpCode::neql:   return  !cmp_eql(other);
  default:
    cerr << "AstMap::opfunc, default error!\n";
    return Operand();
  }
  return nil;


};