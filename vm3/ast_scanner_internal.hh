#include "ast_parser.hh"
namespace vslast {
class AstScanner : public AstFlexLexer {
public:
  AstScanner(std::istream& arg_yyin, std::ostream& arg_yyout)
    : AstFlexLexer(arg_yyin, arg_yyout) {}
  AstScanner(std::istream* arg_yyin = nullptr, std::ostream* arg_yyout = nullptr)
    : AstFlexLexer(arg_yyin, arg_yyout) {}
  int lex(AstParser::semantic_type *yylval, AstParser::location_type *yylloc); 
};
}

