#pragma once
namespace vslasm {
class Scanner : public yyFlexLexer {
public:
  Scanner(
    std::istream& arg_yyin,
    std::ostream& arg_yyout)
    : yyFlexLexer(arg_yyin, arg_yyout) {}
  Scanner(
    std::istream* arg_yyin=nullptr,
    std::ostream* arg_yyout=nullptr)
    : yyFlexLexer(arg_yyin, arg_yyout) {}
  int lex(Parser::semantic_type *yylval);

  //int lex(Parser::semantic_type *yylval, Parser::location_type* loc);

  //  int value;

}; 
}
