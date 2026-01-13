#pragma once
#include "lisp.hh"
#include "error.hh"
#include <unordered_map>                                                                        
#include <variant>                                                                    
#include <memory>                                                                     
#include <string>                                                                     
#include <vector>                                                                     
#include <list>
#include <deque>
#include <stdexcept>                                                                  
#include <algorithm>                                                                  
#include <type_traits> // For std::decay_t            

using namespace std;


string  _to_str_ext(const vector<string>& keys) ;

class Node {
  friend class Tree;
  friend class LispExpr;
  friend class LispReader;
  friend class Kernel;
  friend class ostream;
public:

  
  enum class ProcState { init, run, sleep, suspend, stop, wait };
  enum class ControlFlow { cf_run, cf_break, cf_continue, cf_return, cf_return_val};

  enum class Type { Null, Bool, Error, Integer, Float, String, Identifier, List, Map, Vector, DeQue, LispOp, ProcState, ControlFlow, Atom, Shared, Raw, Unique };
  using Integer = long; using Float = double;
  //using List = vector<unique_ptr<Node>>;
  using List = list<unique_ptr<Node>>;
  using Vector = vector<unique_ptr<Node>>;
  using DeQue = deque<unique_ptr<Node>>;
  using ptr_R = Node *;
  using ptr_S = shared_ptr<Node>;
  using ptr_U = unique_ptr<Node>;
  //
  using ProgramList = List; // program build list type
  //
  using Map = unordered_map<string, unique_ptr<Node>>;
  using Value = variant<monostate, bool, Error, Integer, Float, string, List, Vector, DeQue, Map, Lisp::Op, ProcState, ControlFlow, ptr_S, ptr_R, ptr_U>;
  using ValueSimple = variant<monostate, bool,  Error, Lisp::Op, ProcState, ControlFlow, Integer, Float, string>;

  using OpStatus = pair<bool, unique_ptr<Node>>;
  using OpStatusRef = pair<bool, Node&>;
  using SExpr= pair<unique_ptr<Node>, unique_ptr<Node>>;



  Node();
  Node(Value v);
  Node(ptr_S ptr);
  Node(ptr_R ptr);
  Node(ptr_U ptr);
  Node(Type t);
  //Node(vector<Value> v);
  Node(vector<ValueSimple> v);

  static unique_ptr<Node> create();
  static unique_ptr<Node> create(Value v);
  static unique_ptr<Node> create(Type t);

  static unique_ptr<Node> create_error(Error::Type type, const string& msg);

  unique_ptr<Node> clone() const;
  static unique_ptr<Node> clone(const List& list) ;
  static unique_ptr<Node> clone(const Vector& list) ;
  static unique_ptr<Node> clone(const DeQue& list) ;
  static unique_ptr<Node> clone(const Map& map) ;

  void set(Integer v);
  void set(Float v);
  void set(Lisp::Op v);
  void set(ProcState v);
  void set(ControlFlow v);
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

  //---  map
  OpStatus set(const string& key, Integer v);                                          
  OpStatus set(const string& key, Float v);                                          
  OpStatus set(const string& key, Lisp::Op v);                                          
  OpStatus set(const string& key, ProcState v);                                          
  OpStatus set(const string& key, ControlFlow);
  OpStatus set(const string& key, const string& v);                           
  //OpStatus set_null(const string& key);

  OpStatus set(const vector<string>&path, unique_ptr<Node>child, bool override=false);

  OpStatusRef get_node(const string&key);
  OpStatusRef get_node(const vector<string>&path);
  OpStatusRef get_node(size_t i);

  OpStatus merge(unique_ptr<Node> n, bool override=false);
  OpStatus merge(Map &m, bool override=false);
  OpStatus has_key(const string&key);
  bool extend(const vector<string>&path, bool override=false);

  //----
  static unique_ptr<Node> ptr_US(unique_ptr<Node> node); // convert to  unique pointer -> unique pointer(shared pointer)
  static unique_ptr<Node> ptr_USU(const unique_ptr<Node> &node); // make a clone of unique shared without recursive cloning.
  static unique_ptr<Node> ptr_USU(const Node& node); // make a clone of unique shared without recursive cloning.
  static unique_ptr<Node>  container_obj_to_US(unique_ptr<Node>); // convert container objects map, list, vector, deque to unqiue_ptr(shared_ptr);
  
  //----


  Type _get_type() const;

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
  OpStatusRef back();
  OpStatusRef front();

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
  OpStatusRef operator[](size_t index) ;

    /**
     * @brief Accesses an element in a Map node by key. Returns a clone of the Node via OpStatus.
     * @param key The key to access.
     * @return OpStatus containing a clone of the Node or an Error Node.
     */
  OpStatusRef operator[](const std::string& key) ;

  // _get
  Integer _get_integer() const;
  Float _get_float() const;
  bool _get_bool() const;
  string _get_str() const;
  Map& _get_map_ref() ;
  Vector& _get_vector_ref() ;

  // for list and map
  Integer size_container() const;
  OpStatus size() const;
  OpStatus empty() const;
  bool empty_container() const;
  //
  string _to_str() const;


  static string _to_str(const Map&m) ;
  static string _to_str(const Vector&l) ;
  static string _to_str(const List&l) ;
  static string _to_str(const DeQue&l) ;
  static string _to_str(Type type);
  static string _to_str(ProcState ps);
  static string _to_str(ControlFlow ps);
  //Node to_str() const;


  //
  Node operator +(const Node& other) const;
  //Node operator -(const Node& other) const;
  Node operator *(const Node& other) const;
  Node operator /(const Node& other) const;

  OpStatus list_add() const;
  //OpStatus list_mul(size_t start=0) const;
  
  virtual OpStatus eval(Node& env);

  void print(int depth=0) const;
  static void print_value_recursive(const Node& node, int depth=0);
  static void print_value(const Value& node, int depth=0);

  // map
  static Node* extend_node_by_key(Map& map, const string&key, bool create=true); // for map
  // list
  static vector<string> list_to_vector_string(const List &list); // for map

protected:



  Value value_;
  Type type_;
private:
  bool m_has_key(const string&key);
};


ostream& operator<<(ostream& os, const Node& v) ;
ostream& operator<<(ostream& os, const Node::OpStatus& s) ;
ostream& operator<<(ostream& os, const Node::OpStatusRef& s) ;

extern Node null_node;