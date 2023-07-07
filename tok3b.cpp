#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <any>


using namespace std;

class Token {
public:
  enum Type {
    Integer,
    Float,
    Alphanumeric,
    QString,
    Invalid
  };
  Token(istream& iss) : infile(iss) {}

  void getTokens() {
    string input;
    while (getline(infile, input)) {
      if (input == "EOF") break;
      validToken(input);
      printValue();
    }
  }

  bool validToken(string input) {
    if (isInteger(input)) return true;
    if (isFloat(input)) return true;
    if (isAlphanumeric(input)) return true;
    if (isQString(input)) return true;
    return false;
  }
  bool isInteger(string input) {
    int v;
    stringstream ss(input);
    ss >> v;
    if(ss.eof() && !ss.fail()) {
      value = any_cast<int>(v);
      type = Integer;
      return true;
    } else {
      type = Invalid;
      return false;
    }
  }
  bool isFloat(string input) {
    float v;
    stringstream ss(input);
    ss >> v;
    if(ss.eof() && !ss.fail()) {
      value = any_cast<float>(v);
      type = Float;
      return true;
    } else {
      type = Invalid;
      return false;
    }
  }

  bool isAlphanumeric(string input) {
    type = Invalid;
    // cout << "is Alphanumeric? " << input << "\n";
    if(input.empty()) return false;
    for(char c : input) 
      if (!isalnum(c)) return false;
    type = Alphanumeric;
    value = any_cast<string>(input);
    return true;
  }

  bool isQString(string input) {
    if(input.front() != '\"' || input.back() != '\"') {
      type = Invalid;
      return false;
    }
    string output = "";
    for(int i=1; i< input.size() - 1; i++) {
      if(input[i] == '\\') {
        i++;
        output += evaluateCharacter(input[i]);
      } else {
        output += input[i];
      }
    }
    cout << "qstring: " << output << "\n";
    type = QString;
    value = any_cast<string>(output);
    return true;
  }
  bool isQString2(string input) {
    string v;
    stringstream ss(input);
    getline(ss, v,  '\"');
    cout << "before quoted: " << v << "\n";
    getline(ss, v,  '\"');
    cout << "inbetween quoted: " << v << "\n";
    getline(ss, v,  '\"');
    cout << "after quoted: " << v << "\n";
    value = any_cast<string>(v);
    type = QString;
    cout << "\n";
    return true;
    /*
    if(ss.eof() && !ss.fail()) {
      value = any_cast<string>(v);
      type = QString;
      return true;
    } else {
      type = Invalid;
      return false;
    }
    */
  }
  void printValue() {
    switch (getType()) {
      case Token::Integer:
        cout << "The input is an integer: " << any_cast<int>(getValue()) << endl;
        break;
      case Token::Float:
        cout << "The input is a float: " << any_cast<float>(getValue()) << endl;
        break;
      case Token::Alphanumeric:
        cout << "The input is an alphanumeric string: " 
            << any_cast<string>(getValue()) << endl;
        break;
      case Token::QString:
        cout << "The input is a quoted string: " 
            << any_cast<string>(getValue()) << endl;
        break;
      case Token::Invalid:
        cout << "The input is not a valid integer, float, or alphanumeric string." << endl;
        break;
    }
  }

  Type getType() const { return type; }
  any getValue() const { return value; }
private:
  any value;
  Type type;
  istream& infile;

  char evaluateCharacter(char c) {
    switch (c) {
        case '\"':
            return '\"';
        case '\'':
            return '\'';
        case '\\':
            return '\\';
        case 'n':
            return '\n';
        case 't':
            return '\t';
        default:
            throw invalid_argument("Invalid escape sequence.");
    }
  }
};


int main() {
  string input;
  ifstream infile;
  infile.open("input.txt");
  // Token token(std::cin);
  Token token(infile);
  token.getTokens();
  //token.printValue();
  return 0;
}


