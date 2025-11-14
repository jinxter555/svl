#pragma once
#include "lisp.hh"
#include <map>                                                                        
#include <variant>                                                                    
#include <memory>                                                                     
#include <string>                                                                     
#include <vector>                                                                     
#include <list>
#include <deque>
#include <stdexcept>                                                                  
#include <algorithm>                                                                  
#include <type_traits> // For std::decay_t            

class Node;
using namespace std;


//class Lisp;

class Node {
  friend class Tree;
  friend class LispExpr;
  friend class LispReader;
public:

  struct Error{
    enum class Type {
      DivideByZero, // e.g., divide by zero error
      InvalidOperation, // e.g., calling 'add' on an Integer node
      KeyAlreadyExists, // e.g., calling 'add' with a duplicate map key
      KeyNotFound, // e.g., calling 'add' with a duplicate map key
      IndexOutOfBounds,  // e.g., calling 'set' with an invalid list index
      Incomplete,
    };
    Type type_;
    string message_;
    static string type_to_string(Type t);
  };
  
  //enum class LispOp {kernel, system, root, error, noop, list, deque, vector, add, sub, div, mul, mod, def, call, send, ret, cond, print};
  enum class Type { Null, Error, Integer, Float, String, Identifier, List, Map, Vector, DeQue, LispOp, Atom, Mvar, Lvar };
  using Integer = long; using Float = double;
  //using List = vector<unique_ptr<Node>>;
  using List = list<unique_ptr<Node>>;
  using Vector = vector<unique_ptr<Node>>;
  using DeQue = deque<unique_ptr<Node>>;
  //
  using ProgramList = List; // program build list type
  //
  using Map = map<string, unique_ptr<Node>>;
  using Value = variant<monostate, Error, Integer, Float, string, List, Vector, DeQue, Map, Lisp::Op>;
  using ValueSimple = variant<monostate, Lisp::Op, Integer, Float, string>;

  using OpStatus = pair<bool, unique_ptr<Node>>;
  using SExpr= pair<unique_ptr<Node>, unique_ptr<Node>>;



  Node();
  Node(Value v);
  Node(Type t);
  //Node(vector<Value> v);
  Node(vector<ValueSimple> v);
  static string type_to_string(Type type);

  static unique_ptr<Node> create(Value v) {
    return make_unique<Node>(move(v));
  }

  static unique_ptr<Node> create_error(Error::Type type, const string& msg);

  unique_ptr<Node> clone() const;
  static unique_ptr<Node> clone(const List& list) ;
  static unique_ptr<Node> clone(const Vector& list) ;
  static unique_ptr<Node> clone(const DeQue& list) ;
  static unique_ptr<Node> clone(const Map& map) ;

  void set(Integer v);
  void set(Float v);
  void set(Lisp::Op v);
  void set(const string& v);
  void set(List v);
  void set(Map v);
  void set(unique_ptr<Node> new_node);
  void set_atom(Integer v);
  void set_atom();
  void set_identifier(const string& v);
  void set_identifier();
  void set_null();

  // --- Overloaded Set Methods (Container Element Modification/Replacement) ---    
  OpStatus set(size_t index, unique_ptr<Node> child);                              
  OpStatus set(const string& key, unique_ptr<Node> child);                    
 
  // Convenience Overloads for Atomic Types (Delegates)                             
  OpStatus set(size_t index, Integer v);                                                    
  OpStatus set(size_t index, Float v);                                                    
  OpStatus set(size_t index, const string& v);                                     

  OpStatus set(const string& key, Integer v);                                          
  OpStatus set(const string& key, Float v);                                          
  OpStatus set(const string& key, Lisp::Op v);                                          
  OpStatus set(const string& key, const string& v);                           

  OpStatus add(unique_ptr<Node> child);
  OpStatus add(const string&key, unique_ptr<Node> child);

  OpStatus delete_key(const string &key);

  /**
   * @brief Removes the last element from a List node (equivalent to std::vector::pop_back).
   * @return OpStatus containing the popped Node on success, or an Error Node on failure.
   */
  OpStatus pop_back();
  OpStatus pop_front();
  OpStatus push_front(unique_ptr<Node>node);
  OpStatus push_back(unique_ptr<Node>node);

  /**
    * @brief Clears all elements from a List node (equivalent to std::vector::clear).
    * @return OpStatus indicating success/failure.
  */
  OpStatus clear();

  // --- Overloaded Square Bracket Operators (Read-only access) ---
  /**
     * @brief Accesses an element in a List node by index. Returns a clone of the Node via OpStatus.
     * @param index The index to access.
     * @return OpStatus containing a clone of the Node or an Error Node.
     */
  OpStatus operator[](size_t index) const;

    /**
     * @brief Accesses an element in a Map node by key. Returns a clone of the Node via OpStatus.
     * @param key The key to access.
     * @return OpStatus containing a clone of the Node or an Error Node.
     */
  OpStatus operator[](const std::string& key) const;


  //
  string _to_str() const;
  string _to_str(const Map&m) const;
  string _to_str(const Vector&l) const;
  string _to_str(const List&l) const;
  string _to_str(const DeQue&l) const;
  //Node to_str() const;


  //
  Node operator +(const Node& other) const;
  //Node operator -(const Node& other) const;
  Node operator *(const Node& other) const;
  Node operator /(const Node& other) const;

  OpStatus list_add() const;
  //OpStatus list_mul(size_t start=0) const;
  
  virtual OpStatus eval(Node& env);

  void print(int depth=0);
  static void print_value_recursive(const Node& node, int depth=0);
  static void print_value(const Value& node, int depth=0);
protected:
  Value value_;
  Type type_;
};

ostream& operator<<(ostream& os, const Node& v) ;
