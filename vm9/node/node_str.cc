#include <iostream>
#include <sstream>
#include <iomanip>
#include <cmath>
#include <type_traits>
#include "node.hh"
#include "lisp.hh"
#include "defs.hh"
#include "lang.hh"

#define SLOG_DEBUG_TRACE_FUNC
#include "scope_logger.hh"




string Node::_to_str(Type type) {
  switch (type) {
    case Type::Null: return "Null";
    case Type::Bool: return "Bool";
    case Type::Error: return "Error";
    case Type::Integer: return "Integer";
    case Type::Float: return "Float";
    case Type::String: return "String";
    case Type::List: return "List";
    case Type::Vector: return "Vector";
    case Type::DeQue: return "DeQue";
    case Type::Map: return "Map";
    case Type::IMap: return "IMap";
    case Type::Atom: return "Atom";
    case Type::LispOp: return "LispOp";
    case Type::ProcState: return "ProcessState";
    case Type::ControlFlow: return "ControlFlow";
    case Type::Identifier: return "Identifier";
    case Type::Shared: return "SharedPtr";
    case Type::Raw: return "RawPtr";
    case Type::Unique: return "UniquePtr";
    case Type::Fun: return "Function";
  }
  return "Unknown Type";
}

string Node::_to_str(ProcState ps) {
  switch (ps) {
  case ProcState::init: return "init";
  case ProcState::run: return "Run";
  case ProcState::sleep: return "sleep";
  case ProcState::suspend: return "suspend";
  case ProcState::stop: return "stop";
  case ProcState::wait: return "wait";
  }
  return "Unknown Process State";
}

string Node::_to_str(ControlFlow cf) {
  switch (cf) {
  case ControlFlow::cf_run: return "Run";
  case ControlFlow::cf_break: return "break";
  case ControlFlow::cf_continue: return "continue";
  case ControlFlow::cf_return: return "return";
  case ControlFlow::cf_return_val: return "return value";
  }
  return "Unknown Control Flow State";
}


string Node::_to_str() const {
  MYLOGGER(trace_function, "Node::_to_str()", __func__, SLOG_TO_STR);
  if(this==nullptr) { MYLOGGER_MSG(trace_function, string("this==nullptr")  , SLOG_TO_STR); return "Null"; }

  MYLOGGER_MSG(trace_function, string("type: ") + _to_str(type_), SLOG_TO_STR+30);

  switch(type_) {
    case Type::Null: return "nil";
    case Type::Bool: {
      bool b = get<bool>(value_);
      if(b== true) return "true";
      return "false";
    }
    case Type::Error: {
      Error  err = get<Error>(value_);
      return "[Error: " + Error::_to_str(err.type_) + "] " + err.message_;}
    case Type::Atom: { // { //extern Node::OpStatus Lang::atom_to_str(Node::Integer v) ; }
      Integer num = get<Integer>(value_);
      return ":" + Lang::atom_to_str(num); 
    }

    case Type::Integer: {
      Integer num = get<Integer>(value_);
      return to_string(num); }
    case Type::Float:  {
      ostringstream oss;
      Float num = get<Float>(value_);
      oss << fixed << setprecision(2) << num;
      return oss.str(); }
    case Type::Identifier: 
    case Type::String: {
      string str = get<string>(value_);
      return str; }

    case Type::LispOp: {
      Lisp::Op op = get<Lisp::Op>(value_);
      return Lisp::_to_str(op);}

    case Type::ProcState: {
      ProcState ps = get<ProcState>(value_);
      return _to_str(ps);}
    
    case Type::ControlFlow: {
      ControlFlow cf = get<ControlFlow>(value_);
      return _to_str(cf);}
    
    case Type::List: {
      //cout << "_to_str() List\n";
      auto& list = get<List>(value_);
      return _to_str(list);}
    case Type::DeQue: {
      auto& list = get<DeQue>(value_);
      return _to_str(list);}
    case Type::Vector: {
      //cout << "_to_str() vector\n";
      auto& list = get<Vector>(value_);
      return _to_str(list);}
    case Type::Map: {
      auto& map = get<Map>(value_);
      return _to_str(map);}
    case Type::IMap: {
      auto& map = get<IMap>(value_);
      return _to_str(map);}
    case Type::Shared: {
      auto& ptr_s = get<ptr_S>(value_);
      //cout << "shared to_str()";
      return ptr_s->_to_str();}
    case Type::Raw: {
      //cout << "raw to_str()";
      auto& ptr_r = get<ptr_R>(value_);
      return ptr_r->_to_str();}
    case Type::Unique: {
      //cout << "raw to_str()";
      auto& ptr_r = get<ptr_U>(value_);
      return ptr_r->_to_str();}
    default: { return "_to_str() unknown type " + _to_str(type_); }
  }
  return "_to_str() unknwon type " + _to_str(type_); 
}

string Node::_to_str(const Map&map) {
  MYLOGGER(trace_function, "Node::_to_str(const Map&map)", __func__, SLOG_TO_STR);

  if(map.empty()) return "{}";

  vector<string> kv_paires ;
  string colon(":");
  string q("\"");
  string outstr;

  for (auto const& [key, val] : map) {
    if(key == MODULE_PTR || key == CLASS_PTR) {
      outstr = q + key + q  + colon + "--*ptr--";
    } else 
      outstr = q + key + q  + colon + " " + val->_to_str();
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

string Node::_to_str(const IMap&map) {
  MYLOGGER(trace_function, "Node::_to_str(const Map&map)", __func__, SLOG_TO_STR);

  if(map.empty()) return "{}";

  vector<string> kv_paires ;
  string colon(":");
  string q("\"");
  string outstr;

  for (auto const& [key, val] : map) {
      //outstr = q + Lang::atom_to_str( key) + q  + colon + " " + val->_to_str();
      auto atom_key_str = Lang::atom_to_str_imap(key);
      if(atom_key_str.back() == 'i')
        outstr =  atom_key_str  + " " + val->_to_str();
      else
        outstr =  ":" + atom_key_str   + "  " + val->_to_str();

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




string Node::_to_str(const Vector&list) {
  MYLOGGER(trace_function, "Node::_to_str(const Vector&list)", __func__, SLOG_TO_STR);
  size_t s = list.size(), i;
  if(s==0) {return "Vector[]";}
  string outstr("Vector[");

  for(i=0; i<s-1; i++) {
    auto &e = list[i];
    if(e==nullptr) continue;
    outstr = outstr + e->_to_str() + ", ";
  }
  outstr = outstr + list[i]->_to_str() + "]";
  return outstr;
}

string Node::_to_str(const List&list) {
  MYLOGGER(trace_function, "Node::_to_str(const List&list)", __func__, SLOG_TO_STR);
  size_t s = list.size(), i=0;
  MYLOGGER_MSG(trace_function, string("size: ") + to_string(s), SLOG_TO_STR+30);
  if(s==0) {return "List[]";}

  string outstr("List[");

  for(auto &e : list) {
    if(i==s-1) break;
    if(e==nullptr) {
      cerr << "list::_to_str() is null!\n";
      continue;
    }
    outstr = outstr + e->_to_str() + ", ";
    i++;
  }
  if(list.empty()) return outstr + "]";
  auto& e = list.back(); 
  // to prevent last back() node_ptr is null 
  if(e==nullptr)  return outstr + "]"; 
  //outstr = outstr + e->_to_str() +" ]";
  return outstr + e->_to_str() +" ]";
  //return outstr;
}
/*
string Node::_to_str(const List&list) {
  MYLOGGER(trace_function, "Node::_to_str(const List&list)", __func__, SLOG_FUNC_INFO);
  size_t s = list.size(), i=0;
  MYLOGGER_MSG(trace_function, string("size: ") + to_string(s), SLOG_FUNC_INFO+30);
  if(s==0) {return "[]";}

  string outstr("[");
  for(auto &e : list) {
    outstr = outstr + e->_to_str() + ", ";
  }

  return outstr;
}
*/

string Node::_to_str(const DeQue&list) {
  MYLOGGER(trace_function, "Node::_to_str(const DeQue&list)", __func__, SLOG_TO_STR);
  size_t s = list.size();
  if(s==0) {return "DeQue[]";}
  string outstr("DeQue[");

  for(auto &e : list) {
    if(e==nullptr) continue;
    outstr = outstr + e->_to_str() + ", ";
  }
  outstr = outstr + " ]";
  return outstr;
}

