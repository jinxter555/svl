#pragma once
namespace vslasm {
class AsmScanner : public yyFlexLexer {
public:
  AsmScanner(
    std::istream& arg_yyin,
    std::ostream& arg_yyout)
    : yyFlexLexer(arg_yyin, arg_yyout) {}
  AsmScanner(
    std::istream* arg_yyin=nullptr,
    std::ostream* arg_yyout=nullptr)
    : yyFlexLexer(arg_yyin, arg_yyout) {}
  int lex(AsmParser::semantic_type *yylval);

  //int lex(Parser::semantic_type *yylval, Parser::location_type* loc);

  //  int value;

}; 
}
