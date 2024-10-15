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
  auto prev_ptr = curr_ptr;
  auto &curr_operand = MapEntity::get(k);
  if(curr_ptr==nullptr) return nil_operand;

  for(i=1 ; i<s; i++) {
    auto k = keys[i];
    //cout << "keys[" << i<< "]: " << keys[i] << "\n";
    auto next_ptr = curr_ptr->get_raw_ptr(Operand(k));
    auto &curr_operand = curr_ptr->get(k);
    if(next_ptr==nullptr) {
      //cout << "nullptr keys[" << i<< "]: " << keys[i] << "\n";
      return curr_operand;
    }
    prev_ptr = curr_ptr;
    curr_ptr = next_ptr;
    //auto &curr_operand = curr_ptr->get(k);
  }
  //cout << "i: " << i << "\n";
  auto &re_operand= prev_ptr->get(keys[i-1]);
  return re_operand;
}


const Operand& QueNode::add_branch(const vector<string> &keys, entity_u_ptr&& e) {
  int i=0, s = keys.size(); 
  auto k = keys[i];
  if(s==0) return nil_operand;

  Entity *curr_ptr = (MapEntity*) this;
  Entity *next_ptr, *prev_ptr = curr_ptr;
  if(s==1) {
    curr_ptr->add(k, e);
    return nil_operand;
  }
  //curr_ptr->add(keys[0], MapEntity());
  // skip all the existing keys
  for(i=0 ; i<s; i++) { 
    curr_ptr = curr_ptr->get_raw_ptr(keys[i]);
    if(curr_ptr==nullptr) { curr_ptr=prev_ptr; break; }
    prev_ptr = curr_ptr;
  }
  curr_ptr->add(keys[i], MapEntity());

  for(; i<s; i++) {
    MapEntity next_map;
    if(i==s-1) {
      curr_ptr->set(keys[i], e);
      return nil_operand;
    } 
    next_map.add(keys[i+1], MapEntity());
    curr_ptr->set(keys[i], next_map);
    curr_ptr = curr_ptr->get_raw_ptr(keys[i]);
  }
  return nil_operand;
}




//--------------------------------------------------------- 

const Operand& QueNode::add_branch(const vector<string> &keys, const Entity& e) {
  Operand ov(e.clone());
  return add_branch(keys, ov);
}

const Operand& QueNode::add_branch(const vector<string> &keys, const Operand& operand) {
  int i=0, s = keys.size(); 
  auto k = keys[i];
  if(s==0) return nil_operand;

  Entity *curr_ptr = (MapEntity*) this;
  Entity *next_ptr, *prev_ptr = curr_ptr;
  if(s==1) {
    curr_ptr->add(k, operand);
    return operand;
  }


  //curr_ptr->add(keys[0], MapEntity());

  // skip all the existing keys
  for(i=0 ; i<s; i++) { 
    curr_ptr = curr_ptr->get_raw_ptr(keys[i]);
    if(curr_ptr==nullptr) { curr_ptr=prev_ptr; break; }
    prev_ptr = curr_ptr;
  }
  //cout << "i: " << i << "\n";
  //if(curr_ptr==nullptr) { cout << "curr_ptr is null bomb!\n";}
  curr_ptr->add(keys[i], MapEntity());
  //curr_ptr = curr_ptr->get_raw_ptr(keys[i]);
  //return nil_operand;


  for(; i<s; i++) {
    MapEntity next_map;
    if(i==s-1) {
      curr_ptr->set(keys[i], operand);
      return nil_operand;
    } 
    //cout << "curr_ptr->print(): "; curr_ptr->print(); cout << "\n";
    //cout << "keys[" << i<< "]: " << keys[i] << "\n";

    next_map.add(keys[i+1], MapEntity());

    //cout <<"nextmap: "; next_map.print();  cout << "\n";
    curr_ptr->set(keys[i], next_map);

    //cout << "curr_ptr->print(): "; curr_ptr->print(); cout << "\n";
    curr_ptr = curr_ptr->get_raw_ptr(keys[i]);

    //cout << "curr_ptr->print(): "; curr_ptr->print(); cout << "\n";
    //cout << "\n\n";
  }
  //MapEntity::print();
  //return curr_ptr->get(keys[s-1]);
  return nil_operand;
}




//--------------------------------------------------------- 
void QueNode::print_l() const { cout << ListEntity::to_str() << "\n"; }
void QueNode::print_m() const { cout << MapEntity::to_str() << "\n"; }