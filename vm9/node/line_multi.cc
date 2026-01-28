#include <iostream>
#include <cstring>
#include <string>
#include "my_helpers.hh"

using namespace std;


string inputstr =  
string("This is a line\n") 
+ string("This is the next line\n")
+ string("(This is a line3)\n") 
+ string("what is up \\\n")
+ string("world , hello \\\n")
+ string("hola mundo\n")
+ string("halo welt\n") ;


string tokenize_preprocess_multiline(const string& input) {

  istringstream stream(input); // Wrap the string in an input string stream
  string line_current, line_result;
  bool multi_line = false;

  while (getline(stream, line_current)) {
    if(multi_line) { // multi line begins

      if(line_current.back() == '\\') { 
        line_current.pop_back(); // get rid multi line character
        multi_line = true;
      } else {
        multi_line = false;
        line_current += "\n";
      }
      line_result += line_current;
      continue;
    }

    if(line_current.back() == '\\') {
      line_current.pop_back();
      multi_line = true;
    } else {
      multi_line = false;
      line_current += "\n";

    }

    line_result += line_current;
  }

  return line_result;
}

string tokenize_preprocess_multiline_parenthesis(const string& input) {
  istringstream stream(input); // Wrap the string in an input string stream

  string line_current, line_result;

  while (getline(stream, line_current)) {
    auto line = trim(line_current);
    if(line.front() == '(' && line.back() ==')'){
      line_result += line + "\n";
    } else {
      line_result += "(" + line + ")" + "\n";
    }
  }
  return line_result;
}


int main() {
  cout << inputstr << "\n\n";
  auto ml = tokenize_preprocess_multiline(inputstr) ;
  cout <<  ml  <<"\n\n";
  cout <<  tokenize_preprocess_multiline_parenthesis(ml) <<"\n\n";
  return 0;
}