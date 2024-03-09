#include <iostream>
#include <string>
#include <vector>



typedef union {
  int i;
  float f;
  int adr;
} reg_t;


using namespace std;
int main() {
  vector<reg_t> data_seg;
  vector<reg_t> *dsd = &data_seg;

  reg_t t1;
  reg_t t2;
  reg_t t3;
  t1.f = 123.1f;
  t2.f = 456.2f; 
  t3.f = 123.45f;

  //data_seg.push_back(t1);
  //data_seg.push_back(t2);

  dsd->resize(1);
  cout <<  dsd->size() << "\n";
  cout <<  dsd->capacity() << "\n";
  //dsd->resize(10);
   (*dsd)[1] = t1;
  cout <<  dsd->size() << "\n";
  dsd->resize(2);
   (*dsd)[3] = t3;
  cout <<  dsd->size() << "\n";

   auto f1 = t1.f;

  reg_t o = data_seg.back();
  cout <<  data_seg[1].f << "\n";
  cout <<  data_seg[3].f << "\n";
  //cout <<  d1.f << "\n";


  return 0;
}
