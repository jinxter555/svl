#include "token.hh"
#include "parser.hh"

using namespace std;
void Parser::run(ReadInputLine& ril) {
  cout << "in parser:\n";
  for(int i=0; i<ril.infix_tokens.size(); i++) {
    Token token = ril.infix_tokens[i];
    Token next_token = ril.infix_tokens[i+1];

    token.print();
  }
  cout << "\n";

}