#pragma once

//#include "node.hh"
#include <vector>
#include <string>
#include <memory>

using namespace std;

class Node;

class Error {
  friend class Node;
public:
  enum class Type {
    DivideByZero, // e.g., divide by zero error
    InvalidOperation, // e.g., calling 'add' on an Integer node
    KeyAlreadyExists, // e.g., calling 'add' with a duplicate map key
    KeyNotFound, // e.g., calling 'add' with a duplicate map key
    IndexOutOfBounds,  // e.g., calling 'set' with an invalid list index
    IndexWrongType,  // e.g., calling 'set' with an invalid list index
    EmptyContainer,  // get front() or back() when list,queu,vector is empty
    ModuleNotFound,  //  module
    FunctionNotFound,  // function not found
    SymbolNotFound,  // var, immute, arg not found
    Incomplete,
    System,
    Parse,
    User,
    NotEqual,
    Eval,
    Unknown,
  };

  //Error();
  Error(Type t, const string msg="");
  static Node& ref(Type t); 
  static Node& ref(Type t, const string& msg); 
  static string _to_str(Type t) ;
  static void init() ;

  static vector<unique_ptr<Node>> list;
private: 
  Type type_;
  string message_;
};