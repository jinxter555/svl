#pragma
#include <iostream>
#include "error.hh"
#include "node.hh"

#define SLOG_DEBUG_TRACE_FUNC
#include "scope_logger.hh"

Node::Vector Error::list = {};
//vector<unique_ptr<Node>> Error::list;

Error::Error() {}
void Error::init() {
  list.resize(size_t(Type::Unknown)+1);

  list[size_t(Error::Type::DivideByZero)] =  Node::create_error(Type::DivideByZero, "");
  list[size_t(Type::InvalidOperation)] =  Node::create_error(Type::InvalidOperation, "");
  list[size_t(Type::KeyAlreadyExists)] = Node::create_error(Type::KeyAlreadyExists, "");
  list[size_t(Type::KeyNotFound)] = Node::create_error(Type::KeyNotFound, "");
  list[size_t(Type::IndexOutOfBounds)] = Node::create_error(Type::IndexOutOfBounds, "");
  list[size_t(Type::Incomplete)] = Node::create_error(Type::Incomplete, "");
  list[size_t(Type::System)] = Node::create_error(Type::System, "");
  list[size_t(Type::Parse)] = Node::create_error(Type::Parse, "");
  list[size_t(Type::User)] = Node::create_error(Type::User, "");
  list[size_t(Type::Unknown)] = Node::create_error(Type::Unknown, "");
}

Error::Error(Type t, string msg) : type_(t), message_(msg) {}

/*
Node::OpStatusRef Error::operator[](Type t) {
}*/

Node& Error::ref(Error::Type t) { return *list[size_t(t)]; } 
Node& Error::ref(Error::Type t, const string& msg) { 
  MYLOGGER(trace_function, "Error::ref(Type::" + _to_str(t)  + ")", __func__, SLOG_FUNC_INFO);
  MYLOGGER_MSG(trace_function, "errmsg: " + msg, SLOG_FUNC_INFO);

  return *list[size_t(t)]; 
} 
string Error::_to_str(Type type) {
  switch(type) {
    case Type::DivideByZero:     return "DivideByZero";
    case Type::InvalidOperation: return "InvalidOperation";
    case Type::KeyAlreadyExists: return "KeyAlreadyExists";
    case Type::KeyNotFound: return "KeyNotFound";
    case Type::IndexOutOfBounds: return "IndexOutOfBounds";
    case Type::IndexWrongType: return "IndexWrongType";
    case Type::Incomplete:       return "Incomplete";
    case Type::System:       return "System";
    case Type::Parse:       return "Parse";
    case Type::User:       return "User";
    case Type::Unknown:       return "Unknown";
  }
  return "Unknown Error";
}