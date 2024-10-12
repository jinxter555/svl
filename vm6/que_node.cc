#include "ast.hh"

QueNode nil_qnode;

/*
Operand& QueNode::get_child(const vector<string>& keys) {
  int i=0, s = keys.size();
  if(s==0)  return  nil_operand;
  auto &curr = MapEntity::get(keys[i++]);
  if(curr == nil_operand) return nil_operand;

  for(; i<s; i++) {
    if(has_key(curr.get(keys[i])) {
      auto &node = MapEntity::get(keys[i]);
    } else {}
  }
}
*/
entity_u_ptr QueNode::clone() {return nullptr;} 


const Operand& QueNode::get_branch(const vector<string> &keys) {
  int i=0, s = keys.size();
  if(s==0) return nil_operand;

  auto k = keys[i];
  auto curr_ptr = MapEntity::get_raw_ptr(k);
  auto &curr_operand = MapEntity::get(k);
  if(curr_ptr==nullptr) return nil_operand;

  for(i=1 ; i<s; i++) {
    auto k = keys[i];
    auto next_ptr = curr_ptr->get_raw_ptr(Operand(k));
    if(next_ptr==nullptr) {
      return curr_operand;
    }
    curr_ptr = next_ptr;
    auto &curr_operand = curr_ptr->get(k);
  }
  return curr_operand;
}



const Operand& QueNode::add_branch(const vector<string> &keys) {
  int i=0, s = keys.size();
  if(s==0) return nil_operand;

  Entity* curr_ptr = (MapEntity*) this;
  Entity *next_ptr;


  curr_ptr->add(keys[0], MapEntity());


  for(i=0 ; i<s; i++) {
    MapEntity next_map;
    if(i<s-2) { 
      next_map.add(keys[i+1], MapEntity());
      cout << "curr map" << curr_ptr->to_str() << "\n";
      cout << "next map: " << next_map << "\n";
    } else {
      next_map.add(keys[i+1], Operand());
      curr_ptr->set(keys[i], next_map);
      cout << "curr map 2" << curr_ptr->to_str() << "\n";
      cout << "next map 2: " << next_map << "\n";
      break;
    }
    auto k = keys[i];
    auto next_ptr = curr_ptr->get_raw_ptr(k);
    curr_ptr->set(k, next_map);
    curr_ptr->print();
    curr_ptr = next_ptr;
    cout << "k : " << k << "\n";
  }
  return curr_ptr->get(keys[i-1]);
}




//--------------------------------------------------------- 
void QueNode::print_l() const { cout << ListEntity::to_str() << "\n"; }
void QueNode::print_m() const { cout << MapEntity::to_str() << "\n"; }