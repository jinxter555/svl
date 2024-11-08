#include "que_node.hh"

QueNode nil_qnode;

std::ostream& operator << (std::ostream& out, vector<string> vs) {
  std::cout << "keys: "; for(auto k: vs) { std::cout << k << ","; } std::cout << "\n\n";
  return out;
}


astexpr_u_ptr QueNode::clone() {
  list_u_ptr nl = make_unique<AstList>();
  nl->add(AstList::clone());
  nl->add(AstMap::clone());
  return nl;
}

QueNode::QueNode() {
  AstList::type_ = OperandType::quenode_t;
  AstMap::type_ = OperandType::quenode_t;
}


Operand& QueNode::get_branch2(const vector<string> &keys) {
  string k;
  int i=0, s = keys.size();
  if(s==0) return nil_operand;
  AstExpr *curr_ptr, *prev_ptr;

  k = keys[i++]; curr_ptr = AstMap::get_raw_ptr(k);
  if(curr_ptr==nullptr) return nil_operand;

return nil_operand;

}

Operand& QueNode::get_branch(const vector<string> &keys) {
  int i=0, s = keys.size();
  if(s==0) return nil_operand;

  auto k = keys[i];
  auto curr_ptr = AstMap::get_raw_ptr(k);

  if(curr_ptr==nullptr) return nil_operand;
  if(s==1) return AstMap::getv(k);

  auto prev_ptr = curr_ptr;
  AstExpr* next_ptr;


  for(i=1 ; i<s; i++) {
    auto k = keys[i];
    next_ptr = curr_ptr->get_raw_ptr(k);
    cout << "keys[" << i<< "]: " << keys[i] << " addr " << next_ptr << "\n\n" ;

    if(next_ptr==nullptr) {
      cout << "curr_ptr: "; curr_ptr->print(); cout << "\n";
      return  curr_ptr->getv(k);
    }

    next_ptr->print();
    cout <<"\n\n";
    if(k=="one") {
      cout << "1one is here!\n";
      next_ptr->print();
      cout <<"\n\n";
    }

    prev_ptr = curr_ptr;
    curr_ptr = next_ptr;
  }
  cout << "s: " << s << " i: " << i << "\n";
/*
  cout << "curr_ptr->print: "; curr_ptr->print(); cout << "\n\n";
  cout << "next_ptr->print: "; next_ptr->print(); cout << "\n\n";
  cout << "prev_ptr->print: "; prev_ptr->print(); cout << "\n\n";

  auto k2  = prev_ptr->_get_keys();
  auto k3  = curr_ptr->_get_keys();
  auto k4  = next_ptr->_get_keys();
  std::cout << "one k2 keys: "; for(auto k: k2) { std::cout << k << ","; } std::cout << "\n\n";
  std::cout << "one k3 keys: "; for(auto k: k3) { std::cout << k << ","; } std::cout << "\n\n";
  std::cout << "one k4 keys: "; for(auto k: k3) { std::cout << k << ","; } std::cout << "\n\n";
*/

  //auto &re_operand= prev_ptr->getv(keys[i-1]);
  return  prev_ptr->getv(keys[i-1]);
}


bool QueNode::add_branch(const vector<string> &keys, astexpr_u_ptr&& e, bool overwrite) {
  int i=0, s = keys.size(); 
  auto k = keys[i];
  if(s==0) return false;

  AstExpr *curr_ptr = (AstMap*) this;
  AstExpr *next_ptr, *prev_ptr = curr_ptr;
  if(s==1) {
    curr_ptr->add(k, move(e));
    return true;
  }
  //curr_ptr->add(keys[0], MapEntity());
  // skip all the existing keys
  for(i=0 ; i<s; i++) { 
    curr_ptr = curr_ptr->get_raw_ptr(keys[i]);
    if(curr_ptr==nullptr) { curr_ptr=prev_ptr; break; }
    if(curr_ptr->type_ != OperandType::map_t && overwrite==true) { 
      cout << "overwrite keys[" << i<< "]: " << keys[i] << " is leaf-node!\n";
      curr_ptr = prev_ptr;
      break;
    }
    prev_ptr = curr_ptr;
    prev_ptr = curr_ptr;
  }
  curr_ptr->add(keys[i], AstMap());

  for(; i<s; i++) {
    AstMap next_map;
    cout << "keys[" << i<< "]: " << keys[i] << "\n";
    if(i==s-1) {
      curr_ptr->set(keys[i], move(e));
      return true;
    } 
    next_map.add(keys[i+1], AstMap());
    curr_ptr->set(keys[i], next_map);
    curr_ptr = curr_ptr->get_raw_ptr(keys[i]);
    if(curr_ptr==nullptr)  return false;
  }
  return true;
}




//--------------------------------------------------------- 

bool QueNode::add_branch(const vector<string> &keys, const AstExpr& e, bool overwrite) {
  Operand ov(e.clone());
  return add_branch(keys, ov);
}

bool QueNode::add_branch(const vector<string> &keys, const Operand& operand, bool overwrite) {
  int i=0, s = keys.size(); 
  auto k = keys[i];
  if(s==0) return false;

  AstExpr*curr_ptr = (AstMap*) this;
  AstExpr *next_ptr, *prev_ptr = curr_ptr;
  if(s==1) {
    curr_ptr->add(k, operand);
    return true;
  }


  //curr_ptr->add(keys[0], MapEntity());

  // skip all the existing keys
  for(i=0 ; i<s; i++) { 
    curr_ptr = curr_ptr->get_raw_ptr(keys[i]);
    if(curr_ptr == nullptr) { curr_ptr = prev_ptr; break; }
    if(curr_ptr->type_ != OperandType::map_t && overwrite==true) { 
      cout << "overwrite keys[" << i<< "]: " << keys[i] << " is leaf-node!\n";
      curr_ptr = prev_ptr;
      break;
    }
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
      return true;
    } 
    //cout << "curr_ptr->print(): "; curr_ptr->print(); cout << "\n";
    //cout << "keys[" << i<< "]: " << keys[i] << "\n";

    next_map.add(keys[i+1], AstMap());

    //cout <<"nextmap: "; next_map.print();  cout << "\n";
    curr_ptr->set(keys[i], next_map);

    //cout << "curr_ptr->print(): "; curr_ptr->print(); cout << "\n";
    curr_ptr = curr_ptr->get_raw_ptr(keys[i]);
    if(curr_ptr==nullptr) { 
      cerr << "trying to overwrite node !\n";
      return false;
    }

    //cout << "curr_ptr->print(): "; curr_ptr->print(); cout << "\n";
    //cout << "\n\n";
  }
  //MapEntity::print();
  //return curr_ptr->get(keys[s-1]);
  return true;
}




//--------------------------------------------------------- 
void QueNode::print_l() const { cout << AstList::to_str() << "\n"; }
void QueNode::print_m() const { cout << AstMap::to_str() << "\n"; }