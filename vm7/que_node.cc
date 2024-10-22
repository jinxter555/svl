#include "que_node.hh"

QueNode nil_qnode;

astexpr_u_ptr QueNode::clone() {return nullptr;} 


const Operand& QueNode::get_branch(const vector<string> &keys) {
  int i=0, s = keys.size();
  if(s==0) return nil_operand;

  auto k = keys[i];
  auto curr_ptr = AstMap::get_raw_ptr(k);
  auto prev_ptr = curr_ptr;
  auto &curr_operand = AstMap::getv(k);
  if(curr_ptr==nullptr) return nil_operand;

  for(i=1 ; i<s; i++) {
    auto k = keys[i];
    //cout << "keys[" << i<< "]: " << keys[i] << "\n";
    auto next_ptr = curr_ptr->get_raw_ptr(Operand(k));
    auto &curr_operand = curr_ptr->getv(k);
    if(next_ptr==nullptr) {
      //cout << "nullptr keys[" << i<< "]: " << keys[i] << "\n";
      return curr_operand;
    }
    prev_ptr = curr_ptr;
    curr_ptr = next_ptr;
  }
  //cout << "i: " << i << "\n";
  auto &re_operand= prev_ptr->getv(keys[i-1]);
  return re_operand;
}


const Operand& QueNode::add_branch(const vector<string> &keys, astexpr_u_ptr&& e) {
  int i=0, s = keys.size(); 
  auto k = keys[i];
  if(s==0) return nil_operand;

  AstExpr *curr_ptr = (AstMap*) this;
  AstExpr *next_ptr, *prev_ptr = curr_ptr;
  if(s==1) {
    curr_ptr->add(k, move(e));
    return nil_operand;
  }
  //curr_ptr->add(keys[0], MapEntity());
  // skip all the existing keys
  for(i=0 ; i<s; i++) { 
    curr_ptr = curr_ptr->get_raw_ptr(keys[i]);
    if(curr_ptr==nullptr) { curr_ptr=prev_ptr; break; }
    prev_ptr = curr_ptr;
  }
  curr_ptr->add(keys[i], AstMap());

  for(; i<s; i++) {
    AstMap next_map;
    if(i==s-1) {
      curr_ptr->set(keys[i], move(e));
      return nil_operand;
    } 
    next_map.add(keys[i+1], AstMap());
    curr_ptr->set(keys[i], next_map);
    curr_ptr = curr_ptr->get_raw_ptr(keys[i]);
  }
  return nil_operand;
}




//--------------------------------------------------------- 

const Operand& QueNode::add_branch(const vector<string> &keys, const AstExpr& e) {
  Operand ov(e.clone());
  return add_branch(keys, ov);
}

const Operand& QueNode::add_branch(const vector<string> &keys, const Operand& operand) {
  int i=0, s = keys.size(); 
  auto k = keys[i];
  if(s==0) return nil_operand;

  AstExpr*curr_ptr = (AstMap*) this;
  AstExpr *next_ptr, *prev_ptr = curr_ptr;
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
  curr_ptr->add(keys[i], AstMap());
  //curr_ptr = curr_ptr->get_raw_ptr(keys[i]);
  //return nil_operand;


  for(; i<s; i++) {
    AstMap next_map;
    if(i==s-1) {
      curr_ptr->set(keys[i], operand);
      return nil_operand;
    } 
    //cout << "curr_ptr->print(): "; curr_ptr->print(); cout << "\n";
    //cout << "keys[" << i<< "]: " << keys[i] << "\n";

    next_map.add(keys[i+1], AstMap());

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
void QueNode::print_l() const { cout << AstList::to_str() << "\n"; }
void QueNode::print_m() const { cout << AstMap::to_str() << "\n"; }