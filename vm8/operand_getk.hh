#ifndef GETK_CC
#define GETK_CC

#pragma once
#include "operand.hh"
#include <stdexcept>
#include "operand.hh"
#include "operand_vars.hh"

//#define TO_STR(m) ((Operand::ToString *) this)->Operand::ToString::operator()(m);

#define SLOG_DEBUG_TRACE_FUNC
#include "scope_logger.hh"



//------------------------------------ GetK
template <typename T, typename U> 
const Operand& Operand::GetK::operator()(const T& v, const U& k ) const {
  MYLOGGER(trace_function, "Operand::GetK::()(<T>, <U>)", __func__, SLOG_FUNC_INFO);
  return nil_operand; }
//------------------------- GetK - list_t
template <typename T> 
const Operand& Operand::GetK::operator()(const list_t& l, const T&k ) const {
  MYLOGGER(trace_function, "Operand::GetK::()(list_t&, <T>k)", __func__, SLOG_FUNC_INFO);
  return nil_operand; 
}

const Operand& Operand::GetK::operator()(const list_t& l, const Nil) const {
  MYLOGGER(trace_function, "Operand::GetK::()(list_t&, Nil)", __func__, SLOG_FUNC_INFO);
  return nil_operand;}

const Operand& Operand::GetK::operator()(const list_t& l, const Number&n) const {
  MYLOGGER(trace_function, "Operand::GetK::()(list_t&, Number)", __func__, SLOG_FUNC_INFO);
  auto i = n.get_int();
  return l[i]; }

const Operand& Operand::GetK::operator()(const list_t& l, const operand_ptr& k) const  {
  MYLOGGER(trace_function, "Operand::GetK::()(list_t&, ptr)", __func__, SLOG_FUNC_INFO);
  //auto &kv = k->get_value(); if(kv.is_nil()) return nil_operand; return l[kv._get_number().get_int()]; 
  return l[k->_get_number().get_int()]; 
  }

const Operand& Operand::GetK::operator()(const list_t& l, const operand_s_ptr& k) const {
  MYLOGGER(trace_function, "Operand::GetK::()(list_t&, ptr)", __func__, SLOG_FUNC_INFO);
   return Operand::GetK::operator()(l, k.get()); }

const Operand& Operand::GetK::operator()(const list_t& l, const operand_u_ptr& k)  const {
  MYLOGGER(trace_function, "Operand::GetK::()(list_t&, uptr)", __func__, SLOG_FUNC_INFO);
   return Operand::GetK::operator()(l, k.get()); }

const Operand& Operand::GetK::operator()(const list_t& l, const list_t& k) const  {
  MYLOGGER(trace_function, "Operand::GetK::()(list_t&, list_t&)", __func__, SLOG_FUNC_INFO);
  //cout <<  "Operand::GetK::()(list_t&, list_t&)\n";
  s_integer s=k.size();

  if(s <=0) {
    cerr << "multi-dimensional array lookup error index " << k << " out of bound!";
    return nil_operand;
  }

  auto &first_i  = k[0];
  auto &first_v = l[first_i._get_int()];
  auto current_list_ptr = first_v.get_raw_ptr();

  for(s_integer i=1; i<s; i++) {
    auto &index = k[i];

    if(index >= current_list_ptr->_get_list_size()) {
      cerr << "multi-dimensional array lookup error index " << index << " out of bound!";
      return nil_operand;
    }

    auto &value = (*current_list_ptr)[index];
    if(value.is_nil()) return nil_operand;

    //cout << "index: " << index << "\n"; cout << "value: " << value << "\n";

    current_list_ptr = value.get_raw_ptr();
  }
  return *current_list_ptr;
} // maybe for with get_branch

//------------------------- GetK - map_t
template <typename T> 
const Operand& Operand::GetK::operator()(const map_t& m, const T&k )const  {
  MYLOGGER(trace_function, "Operand::GetK::()(map_t, <T>&k)", __func__, SLOG_FUNC_INFO);
  return nil_operand; 
}

const Operand& Operand::GetK::operator()(const map_t& m, const Nil)const  {
  MYLOGGER(trace_function, "Operand::GetK::()(map_t, Nil)", __func__, SLOG_FUNC_INFO);
  cout << "m. Nil\n";
  return nil_operand;
}
const Operand& Operand::GetK::operator()(const map_t& m, const list_t&k)const  {
  cout <<  "Operand::GetK::()(map_t&, list_t&)\n";
  s_integer i=0,s = k.size(); 
  operand_ptr current_map_ptr;

  if(s <=0) {
    cerr << "multi-dimensional map lookup error index " << k << " out of bound!";
    return nil_operand;
  }
  auto &first_i  = k[0];

  try {
    auto &first_v = m.at(first_i._to_str());
    current_map_ptr = first_v.get_raw_ptr();
  }catch(const out_of_range &e) {
    cerr << "multi-dimensional map lookup error index '" << first_i << "' out of bound!";
    return nil_operand;
  }



  for(s_integer i=1; i<s; i++) {
    auto &index = k[i];

    auto &value = (*current_map_ptr)[index];
    if(value.is_nil()) return nil_operand;

    cout << "index: " << index << "\n"; 
    cout << "value: " << value << "\n";

    current_map_ptr = value.get_raw_ptr();
  }
  return *current_map_ptr;

  return nil_operand;

}

const Operand& Operand::GetK::operator()(const map_t& m, const string&k)const  {
  MYLOGGER(trace_function, "Operand::GetK::()(map_t, string&)", __func__, SLOG_FUNC_INFO);
  //cout <<  "Operand::GetK::()(map_t, string&)\n";
  if (m.find(k) != m.end())  return m.at(k);  

  //cout << "key " << k << " not found \n";
  MYLOGGER_MSG(trace_function, k + string(", key not found!"), SLOG_FUNC_INFO + 1);
  MYLOGGER_MSG(trace_function, "return nil_operand", SLOG_FUNC_INFO + 1);
  return nil_operand;
}

const Operand& Operand::GetK::operator()(const map_t& m, const operand_ptr& k) const  {
  MYLOGGER(trace_function, "Operand::GetK::()(map_t, operand_ptr&)", __func__, SLOG_FUNC_INFO);
  auto ms = TO_STR(m);
  MYLOGGER_MSG(trace_function, string("map_t: ") + ms._to_str(), SLOG_FUNC_INFO);
  //cout << "Operand::()(map_t, operand_u_ptr&)\n";


/*
  auto &kv = k->get_value();

  if(kv.is_nil()) return nil_operand;
  if(k->_get_type() == OperandType::str_t) return m.at(kv._to_str());

  return operator()(m, kv.value_);
*/
  return operator()(m, k->_to_str());


}

const Operand& Operand::GetK::operator()(const map_t& m, const operand_s_ptr& k)const  { 
  MYLOGGER(trace_function, "Operand::GetK::()(map_t, operand_s_ptr&)", __func__, SLOG_FUNC_INFO);
  return Operand::GetK::operator()(m, k.get()); 
}
const Operand& Operand::GetK::operator()(const map_t& m, const operand_u_ptr& k) const  { 
  MYLOGGER(trace_function, "Operand::GetK::()(map_t, operand_u_ptr&)", __func__, SLOG_FUNC_INFO);
  //cout << "Operand::()(map_t, operand_u_ptr&)\n";
  return  Operand::GetK::operator()(m, k.get()); 
}
const Operand& Operand::GetK::operator()(const map_t& m, const map_t& v) const  {
  MYLOGGER(trace_function, "Operand::GetK::()(map_t, map_t&)", __func__, SLOG_FUNC_INFO);
  return nil_operand;
} // maybe for with get_branch

//------------------------- GetK - map_t ptr
template <typename T> 
const Operand& Operand::GetK::operator()(const operand_ptr& vptr, const T&k )const  {
  MYLOGGER(trace_function, "Operand::GetK::()(const operand_ptr&, <T>k)", __func__, SLOG_FUNC_INFO);
/*
  cout << "Operand::()(const operand_ptr&, <T>k)\n";
  cout << "k: " << k<< ", <vptr>m: " << *vptr << "\n";
  cout << "vptr->gettype() " << vptr->get_type() << "\n";
*/
  if(vptr==nullptr) return nil_operand;
  //return operator()(vptr->value_, k);
  if(vptr->_get_type() == OperandType::list_t) return operator()(vptr->_get_list(), k);
  if(vptr->_get_type() == OperandType::map_t) return operator()(vptr->_get_map(), k);
  cerr  << "Can't find GetK key " << k << " for type: " << vptr->get_type() << "\n";
  return nil_operand;
  //return operator()(vptr->value_, k);
}
template <typename T> 
const Operand& Operand::GetK::operator()(const operand_s_ptr& vptr, const T&k )const  {
  MYLOGGER(trace_function, "Operand::GetK::()(const operand_s_ptr&, <T>k)", __func__, SLOG_FUNC_INFO);
  return operator()(vptr.get(), k);
}
template <typename T> 
const Operand& Operand::GetK::operator()(const operand_u_ptr& vptr, const T&k )const  {
  MYLOGGER(trace_function, "Operand::GetK::()(const operand_u_ptr&, <T>k)", __func__, SLOG_FUNC_INFO);
  return operator()(vptr.get(), k);
}

#endif